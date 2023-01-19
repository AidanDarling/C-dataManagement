cmake_minimum_required(VERSION 3.20)
project(Lab04Materials C)

set(CMAKE_C_STANDARD 11)

include_directories(.)

add_executable(Lab04Materials
        avl.c
        avl.h
        bintree.c
        bintree.h
        bst.c
        bst.h
        LAB4_AVL.c
        main.c
        main_B.c
        MakeRandom.c)
