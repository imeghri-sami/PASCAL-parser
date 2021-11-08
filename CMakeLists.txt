cmake_minimum_required(VERSION 3.17)
project(pascal_parser C)

set(CMAKE_C_STANDARD 99)

add_executable(pascal_parser main.c core/grammar_rules.c headers/tokens.h headers/global.h headers/helpers.h helpers/helpers.c headers/errors.h headers/includes.h headers/core.h)