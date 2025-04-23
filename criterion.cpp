/*
** EPITECH PROJECT, 2024
** B-OOP-400-MAR-4-1-raytracer-selim.bouasker
** File description:
** criterion.cpp
*/

#include <criterion/criterion.h>
#include <string>

bool is_valid_cfg(const std::string &f);

Test(extension, valid_cfg) {
    cr_assert(is_valid_cfg("scene.cfg"), "scene.cfg should be valid");
}

Test(extension, invalid_cfg) {
    cr_assert_not(is_valid_cfg("scene.txt"), "scene.txt should be invalid");
}
