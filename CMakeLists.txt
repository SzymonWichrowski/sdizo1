cmake_minimum_required(VERSION 3.25)
project(sdizoP1)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -static-libstdc++ -static-libgcc")
set(CMAKE_EXE_LINKER_FLAGS "-static")

add_executable(sdizoP1 main/main.cpp menu/Menu.h menu/Menu.cpp tablica_dynamiczna/Tablica.h tablica_dynamiczna/Tablica.cpp czas/Czas.h czas/Czas.cpp lista_dwukierunkowa/Lista.cpp lista_dwukierunkowa/Lista.h lista_dwukierunkowa/ElementListy.cpp lista_dwukierunkowa/ElementListy.h kopiec/Kopiec.cpp kopiec/Kopiec.h)
