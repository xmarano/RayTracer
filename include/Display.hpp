/*
** EPITECH PROJECT, 2025
** B-OOP-400-MAR-4-1-raytracer-selim.bouasker
** File description:
** Display.hpp
*/
#include <queue>
#include <mutex>
#include <condition_variable>
#include <SFML/Graphics.hpp>
#include "Exception.hpp"
#include "Utils.hpp"

#pragma once

class Display {
    public:
        Display(int width, int height);
        ~Display() {};

        class Pixel {
            public:
                int r, g, b;
                Pixel(): r(0), g(0), b(0) {}
                Pixel(int rr, int gg, int bb): r(rr), g(gg), b(bb) {}
        };

        void init();
        void run();

        void pushPixel(int x, int y, const Pixel& px);
        void notifyDone();

    private:
        int _width;
        int _height;

        struct PixelEntry {
            int x, y;
            Pixel color;
        };
        std::queue<PixelEntry> _pixelQueue;
        std::mutex _queueMtx;
        std::condition_variable _queueCv;
        bool _done = false;

        sf::RenderWindow _window;
        sf::Texture _texture;
        sf::Sprite _sprite;
};
