cmake_minimum_required(VERSION 3.29)
project(data_structure)

set(CMAKE_CXX_STANDARD 20)

add_executable(data_structure main.cpp
        LinkedList.cpp
        Array.cpp
        common.h
        DoubleLinkedList.cpp
        Polynomial.cpp
)
