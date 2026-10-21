cmake_minimum_required(VERSION 3.21)
project(ccpp2026)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

add_executable(p01_running_letter level1/p01_running_letter/main.c)

add_executable(p02_is_prime  level1/p02_is_prime/main.c)

add_executable(p03_all_primes  level1/p03_all_primes/main.c)

add_executable(p04_hanoi  level1/p04_hanoi/main.c)

add_executable(p05_maze  level1/p05_maze/main.c)

add_executable(p06_push_boxes  level1/p06_push_boxes/main.c)

add_executable(p07_linked_list  level1/p07_linked_list/main.c)

add_executable(p08_warehouse  level1/p08_warehouse/main.c)

add_executable(p09_safe_array_cpp  level1/p09_safe_array_cpp/main.cpp)

add_executable(p10_zoo_cpp level1/p10_zoo_cpp/main.c
)
