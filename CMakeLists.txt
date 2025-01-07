cmake_minimum_required(VERSION 3.30)
project(Coffee_Shop_App)

set(CMAKE_CXX_STANDARD 20)

add_executable(Coffee_Shop_App main.cpp
        angajati.h
        menu.cpp
        menu.h
)
