set_targetdir("./")
set_languages("cxx17")

set_toolchains("clang")
set_warnings("allextra", "error")
set_optimize("fastest")
set_symbols("debug")

add_requires("magic_enum")
add_requires("imgui", {configs = {glfw = true, opengl3 = true}})
includes("submodules/Engine")

PATH_TO_ENGINE = "submodules/Engine/"
set_config("PATH_TO_ENGINE", PATH_TO_ENGINE)

target("game")
    set_kind("binary")
    add_files("srcs/Game/**.cpp")
    add_files("srcs/Common/**.cpp")
    add_includedirs("srcs")
    add_deps("Engine")

target("editor")
    set_kind("binary")
    add_files("srcs/Editor/**.cpp")
    add_files("srcs/Common/**.cpp")
    add_includedirs("srcs")
    add_packages("magic_enum")
    add_packages("imgui")
    add_deps("Engine")