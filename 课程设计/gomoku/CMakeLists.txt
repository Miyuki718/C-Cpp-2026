
cmake_minimum_required(VERSION 3.20)

project(gomoku LANGUAGES C)

# 使用 C11 标准
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)

# 自动收集 src 目录下的 C 源文件
file(GLOB GOMOKU_SOURCES CONFIGURE_DEPENDS
        "${CMAKE_CURRENT_SOURCE_DIR}/src/*.c"
)

# 检查是否存在源文件
if(NOT GOMOKU_SOURCES)
    message(FATAL_ERROR "No C source files found in src/")
endif()

# 创建可执行程序
add_executable(gomoku ${GOMOKU_SOURCES}
        src/main.c
        src/ui.c
        inc/ui.h
        src/game.c
        inc/game.h
        src/rules.c
        inc/rules.h
        src/evaluate.c
        inc/evaluate.h
        src/search.c
        inc/search.h
        inc/search.h
        src/board.c
        inc/board.h
        src/common.c
        inc/common.h
)

# 添加头文件搜索路径
target_include_directories(gomoku PRIVATE
        "${CMAKE_CURRENT_SOURCE_DIR}/inc"
)

# 编译警告
if(MSVC)
    target_compile_options(gomoku PRIVATE /W4)
else()
    target_compile_options(gomoku PRIVATE
            -Wall
            -Wextra
            -Wpedantic
    )
endif()
