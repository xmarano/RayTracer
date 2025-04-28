/*
** EPITECH PROJECT, 2025
** B-OOP-400-MAR-4-1-raytracer-selim.bouasker
** File description:
** Color.hpp
*/
#include <string>

#pragma once

class Color {
    public:
        int r, g, b;
        Color() : r(0), g(0), b(0) {}
        Color(int r_, int g_, int b_) : r(r_), g(g_), b(b_) {}

        std::string toPPM() const {
            return std::to_string(r) + " " + std::to_string(g) + " " + std::to_string(b);
        }
};
