/*
** EPITECH PROJECT, 2024
** Raytracer
** File description:
** OOP
*/
#pragma once
#include <stdexcept>

class RayTracerException : public std::runtime_error {
public:
    explicit RayTracerException(const std::string &msg)
        : std::runtime_error(msg) {}
};
