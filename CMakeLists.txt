cmake_minimum_required(VERSION 3.27)
project(ProjetoFinalAED2 C)

set(CMAKE_C_STANDARD 11)

add_executable(ProjetoFinalAED2 main.c
        libs/DynamicArray.c
        headers/DynamicArray.h
        libs/Leitura.c
        headers/Leitura.h
        libs/Busca.c
        headers/Busca.h
        libs/Arvores.c
        headers/Arvores.h
)
