/*
** EPITECH PROJECT, 2025
** B-OOP-400-MAR-4-1-raytracer-selim.bouasker
** File description:
** Exception.hpp
*/
#include <iostream>

#pragma once

class RayTracerException : public std::runtime_error {
    public:
        explicit RayTracerException(const std::string &msg) : std::runtime_error(msg) {}
};
