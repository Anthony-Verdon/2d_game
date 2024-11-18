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
add_requires("nlohmann_json")
add_requires("imgui", {configs = {glfw = true, opengl3 = true}})

target("game")
    set_kind("binary")
    add_files("srcs/Engine/**.cpp")
    add_files("srcs/Game/**.cpp")
    add_includedirs("srcs")
    add_packages("glfw")
    add_packages("glm")
    add_packages("stb")
    add_packages("glad")
    add_packages("box2d")
    add_packages("nlohmann_json")

target("editor")
    set_kind("binary")
    add_files("srcs/Engine/**.cpp")
    add_files("srcs/Editor/**.cpp")
    add_includedirs("srcs")
    add_packages("glfw")
    add_packages("glm")
    add_packages("stb")
    add_packages("glad")
    add_packages("box2d")
    add_packages("nlohmann_json")
    add_packages("imgui")
