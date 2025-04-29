/*
** EPITECH PROJECT, 2025
** B-OOP-400-MAR-4-1-raytracer-selim.bouasker
** File description:
** Display.cpp
*/
#include "../include/Display.hpp"

Display::Display(int width, int height) : _width(width), _height(height)
{}

void Display::init()
{
    _window.create(sf::VideoMode((unsigned)_width, (unsigned)_height), "Raytracer");
    _texture.create(_width, _height);
    _sprite.setTexture(_texture, true);
}

void Display::pushPixel(int x, int y, const Pixel &px)
{
    std::lock_guard<std::mutex> lock(_queueMtx);
    _pixelQueue.push(PixelEntry{x, y, px});
    _queueCv.notify_one();
}

void Display::notifyDone()
{
    std::lock_guard<std::mutex> lock(_queueMtx);
    _done = true;
    _queueCv.notify_one();
}

void Display::run()
{
    sf::Image image;
    image.create(_width, _height, sf::Color::Black);

    while (_window.isOpen()) {
        sf::Event ev;
        while (_window.pollEvent(ev)) {
            if (ev.type == sf::Event::Closed)
                _window.close();
            else if (ev.type == sf::Event::KeyPressed) {
                if (ev.key.code == sf::Keyboard::Enter)
                    _window.close();
            }
        }

        {
            std::unique_lock<std::mutex> lock(_queueMtx);
            _queueCv.wait(lock, [&]{ return !_pixelQueue.empty() || _done; });

            while (!_pixelQueue.empty()) {
                auto entry = _pixelQueue.front();
                _pixelQueue.pop();
                image.setPixel(entry.x, entry.y, sf::Color(entry.color.r, entry.color.g, entry.color.b));
            }
        }

        _texture.update(image);
        _window.clear();
        _window.draw(_sprite);
        _window.display();
    }
}
