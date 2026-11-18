
# ==================================================
# Gomoku - CMake Configuration
# ==================================================


# ==================================================
# 1. 下载 raylib
# ==================================================

include(FetchContent)

# 不编译 raylib 自带的示例程序
set(BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

# 下载 raylib 5.5
FetchContent_Declare(
        raylib
        GIT_REPOSITORY https://github.com/raysan5/raylib.git
        GIT_TAG 5.5
        GIT_SHALLOW TRUE
)

# 获取并构建 raylib
FetchContent_MakeAvailable(raylib)


# ==================================================
# 2. 收集 Gomoku 源文件
# ==================================================

file(GLOB GOMOKU_SOURCES CONFIGURE_DEPENDS
        "${CMAKE_CURRENT_SOURCE_DIR}/src/*.c"
)

# 检查源文件是否存在
if(NOT GOMOKU_SOURCES)
    message(FATAL_ERROR
            "No C source files found in Gomoku/src/"
    )
endif()

message(STATUS "====================================")
message(STATUS "Gomoku source files:")

foreach(SOURCE_FILE ${GOMOKU_SOURCES})
    message(STATUS "  ${SOURCE_FILE}")
endforeach()

message(STATUS "raylib source: ${raylib_SOURCE_DIR}")
message(STATUS "====================================")


# ==================================================
# 3. 创建 Gomoku 可执行程序
# ==================================================

add_executable(gomoku
        ${GOMOKU_SOURCES}
)


# ==================================================
# 4. 配置 C 语言标准
# ==================================================

set_target_properties(gomoku PROPERTIES
        C_STANDARD 11
        C_STANDARD_REQUIRED ON
        C_EXTENSIONS OFF
)


# ==================================================
# 5. 配置头文件搜索路径
# ==================================================

target_include_directories(gomoku PRIVATE

        # Gomoku 自己的头文件
        "${CMAKE_CURRENT_SOURCE_DIR}/inc"

        # raylib 的头文件
        "${raylib_SOURCE_DIR}/src"
)


# ==================================================
# 6. 链接 raylib
# ==================================================

target_link_libraries(gomoku PRIVATE
        raylib
)


# ==================================================
# 7. 编译警告
# ==================================================

if(MSVC)

    target_compile_options(gomoku PRIVATE
            /W4
    )

else()

    target_compile_options(gomoku PRIVATE
            -Wall
            -Wextra
            -Wpedantic
    )

endif()


# ==================================================
# 8. 完成提示
# ==================================================

message(STATUS "Gomoku CMake configuration completed!")
