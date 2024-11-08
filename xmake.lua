set_targetdir("./")
set_languages("cxx17")

set_toolchains("clang")
add_ldflags("-stdlib=libc++")
add_cxxflags("-std=c++17")
add_cxxflags("-Wall")
add_cxxflags("-Werror")
add_cxxflags("-Wextra")
add_cxxflags("-O3")

add_requires("freetype")
add_requires("glfw")
add_requires("glm")
add_requires("stb")
add_requires("glad")
add_requires("box2d")

target("2d_game")
    set_kind("binary")
    add_files("srcs/**.cpp")
    add_headerfiles("srcs/**.hpp")
    add_includedirs("srcs")
    add_packages("glfw")
    add_packages("glm")
    add_packages("stb")
    add_packages("glad")
    add_packages("box2d")