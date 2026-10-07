cmake_minimum_required(VERSION 3.30)

project(
  TheRemindersTree
  VERSION 0.1.0
  LANGUAGES CXX
  DESCRIPTION "Trabajo final de Estructuras de Datos y Algoritmos."
)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(PROJECT_SOURCES
  input.hpp
  input.cpp
  main.cpp
  person.hpp
  person.cpp
  tree.hpp
  tree.cpp
  utils.hpp
  utils.cpp
)

add_executable(thereminderstree ${PROJECT_SOURCES})
