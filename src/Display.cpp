/*
** EPITECH PROJECT, 2024
** B-OOP-400-MAR-4-1-raytracer-selim.bouasker
** File description:
** Display.cpp
*/

#include "../include/Display.hpp"

Display::Display() : _width(0), _height(0), _maxval(255)
{
}

void Display::parseFile(const std::string& filename)
{
    std::ifstream in(filename);
    if (!in)
        throw RayTracerException("Error: cannot open file");

    std::string magic;
    in >> magic;
    if (magic != "P3")
        throw RayTracerException("Error: not a P3 PPM file");

    in >> _width >> _height >> _maxval;
    if (!in || _width <= 0 || _height <= 0 || _maxval <= 0)
        throw RayTracerException("Error: invalid PPM header");

    // buffer
    _pixels.clear();
    _pixels.reserve(_width * _height);

    for (int i = 0, total = _width * _height; i < total; ++i) {
        int r, g, b;
        in >> r >> g >> b;
        if (!in)
            throw RayTracerException("Error: unexpected end of pixel data");
        _pixels.emplace_back(r, g, b);
    }
}

void Display::init()
{
    sf::Image image;
    image.create(_width, _height, sf::Color::Black);

    for (int y = 0; y < _height; ++y) {
        for (int x = 0; x < _width; ++x) {
            const Pixel& p = _pixels[y * _width + x];
            image.setPixel(x, y, sf::Color(p.r, p.g, p.b));
        }
    }

    sf::Texture texture;
    sf::Sprite sprite(texture);
    sf::RenderWindow window(sf::VideoMode((unsigned)_width, (unsigned)_height), "Raytracer");

    if (!_texture.loadFromImage(image))
        throw RayTracerException("Error: texture load failed");

    _sprite.setTexture(_texture, true);
    _window.create(sf::VideoMode((unsigned)_width, (unsigned)_height), "Raytracer");
}

void Display::run()
{
    while (_window.isOpen()) {
        sf::Event ev;
        while (_window.pollEvent(ev))
            if (ev.type == sf::Event::Closed)
                _window.close();

        _window.clear();
        _window.draw(_sprite);
        _window.display();
    }
}
