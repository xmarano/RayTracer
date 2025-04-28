/*
** EPITECH PROJECT, 2025
** B-OOP-400-MAR-4-1-raytracer-selim.bouasker
** File description:
** criterion.cpp
*/
#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include <stdio.h>
#include <stdlib.h>
#include <string>

bool is_valid_cfg(const std::string &f);
void redirect_all_stdout(void)
{
    cr_redirect_stdout();
    cr_redirect_stderr();
}

Test(extension, valid_cfg) {
    cr_assert(is_valid_cfg("scene.cfg"), "scene.cfg should be valid");
}

Test(extension, invalid_cfg) {
    cr_assert_not(is_valid_cfg("scene.txt"), "scene.txt should be invalid");
}

Test(raytracer, invalid_args, .init = redirect_all_stdout)
{
    int ret = system("./raytracer test.txt");
    cr_assert_eq(WEXITSTATUS(ret), 84);
    cr_assert_stderr_eq_str("Error: SCENE_FILE must have .cfg extension\n");
}

Test(raytracer, too_many_args, .init = redirect_all_stdout)
{
    int ret = system("./raytracer toto toto");
    cr_assert_eq(WEXITSTATUS(ret), 84);
    cr_assert_stderr_eq_str("USAGE: ./raytracer <SCENE_FILE>\n");
}

Test(raytracer, help_message, .init = redirect_all_stdout)
{
    int ret = system("./raytracer -help");
    cr_assert_eq(WEXITSTATUS(ret), 0);
    cr_assert_stdout_eq_str("USAGE: ./raytracer <SCENE_FILE>\n  SCENE_FILE: scene configuration\n");
}

Test(ppm, valid_ppm)
{
    int ret = system("./raytracer scenes/demo.ppm > /dev/null 2>&1");
    cr_assert_eq(WEXITSTATUS(ret), 0, "Le programme doit retourner 0 sur un .ppm valide");
}

Test(cfg, valid_cfg)
{
    int ret = system("./raytracer scenes/demo.cfg > /dev/null 2>&1");
    cr_assert_eq(WEXITSTATUS(ret), 0, "Le programme doit retourner 0 sur un .cfg valide");
}

Test(unitest, test_unitest)
{
    int ret = system("./raytracer unitest");
    cr_assert_eq(WEXITSTATUS(ret), 0, "Le programme doit retourner 0");
}
