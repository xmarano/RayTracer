/*
** EPITECH PROJECT, 2024
** B-OOP-400-MAR-4-1-raytracer-selim.bouasker
** File description:
** Utils.cpp
*/

#include "iostream"
#include "../include/Utils.hpp"

bool is_valid_cfg(const std::string &f) {
    return f.size() > 4 && f.substr(f.size() - 4) == ".cfg";
}
