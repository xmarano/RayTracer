/*
** EPITECH PROJECT, 2024
** Raytracer
** File description:
** OOP
*/
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <SFML/Graphics.hpp>
#include "../include/Exception.hpp"
#include "../include/Utils.hpp"

#pragma once

class Display {
    public:
        Display();
        ~Display() {};

        class Pixel {
            public:
                int r, g, b;
                Pixel(): r(0), g(0), b(0) {}
                Pixel(int rr, int gg, int bb): r(rr), g(gg), b(bb) {}
        };

        void parseFile(const std::string& filename);
        void init();
        void run();

        int getWidth()  const { return _width; }
        int getHeight() const { return _height; }

    private:
        int _width;
        int _height;
        int _maxval;
        std::vector<Pixel> _pixels;
        sf::RenderWindow _window;
        sf::Texture _texture;
        sf::Sprite _sprite;
};
