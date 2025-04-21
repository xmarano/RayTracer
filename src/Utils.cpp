/*
** EPITECH PROJECT, 2024
** Raytracer
** File description:
** OOP
*/
#include "iostream"
#include "../include/Utils.hpp"

bool is_valid_cfg(const std::string &f) {
    return f.size() > 4 && f.substr(f.size() - 4) == ".cfg";
}
