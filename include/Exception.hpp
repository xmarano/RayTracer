/*
** EPITECH PROJECT, 2024
** B-OOP-400-MAR-4-1-raytracer-selim.bouasker
** File description:
** Exception.hpp
*/

#pragma once

class RayTracerException : public std::runtime_error {
public:
    explicit RayTracerException(const std::string &msg)
        : std::runtime_error(msg) {}
};
