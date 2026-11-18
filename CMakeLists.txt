
cmake_minimum_required(VERSION 3.21)

# =========================
# 1. 整个课程项目
# =========================

project(ccpp2026 LANGUAGES C CXX)


# =========================
# 2. 设置语言标准
# =========================

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)


# =========================
# 3. Level 1 - C 语言练习
# =========================

add_executable(p01_running_letter
        level1/p01_running_letter/main.c
)

add_executable(p02_is_prime
        level1/p02_is_prime/main.c
)

add_executable(p03_all_primes
        level1/p03_all_primes/main.c
)

add_executable(p04_hanoi
        level1/p04_hanoi/main.c
)

add_executable(p05_maze
        level1/p05_maze/main.c
)

add_executable(p06_push_boxes
        level1/p06_push_boxes/main.c
)

add_executable(p07_linked_list
        level1/p07_linked_list/main.c
)

add_executable(p08_warehouse
        level1/p08_warehouse/main.c
)


# =========================
# 4. C++ 语言练习
# =========================

add_executable(p09_safe_array_cpp
        level1/p09_safe_array_cpp/main.cpp
)

add_executable(p10_zoo_cpp
        level1/p10_zoo_cpp/main.cpp
)


# =========================
# 5. 课程设计：Gomoku
# =========================

add_subdirectory("课程设计/gomoku")
