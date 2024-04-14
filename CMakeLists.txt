cmake_minimum_required(VERSION 3.27)
project(LFA)

set(CMAKE_CXX_STANDARD 14)


add_executable(Main main.cpp)

add_executable(DFA Tema_1/DFA.cpp)
add_executable(Lambda_NFA Tema_1/Lambda_NFA.cpp)
add_executable(NFA_Path Tema_1/NFA_path.cpp)
add_executable(NFA Tema_1/NFA.cpp)
add_executable(Test Tema_2/test.cpp
                    Tema_2/test.h)


