#include "Engine/WindowManager/WindowManager.hpp"
#include <GLFW/glfw3.h>
#include <glad/glad.h>
#include <stdexcept>
#include "globals.hpp"

GLFWwindow *WindowManager::window = NULL;
glm::vec2 WindowManager::mousePosition = glm::vec2(0,0);
glm::vec2 WindowManager::windowSize = glm::vec2(0,0);
std::map<int, int> WindowManager::keyMap;

void mouse_callback(GLFWwindow *window, double xPos, double yPos);
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);

void WindowManager::InitWindow(const std::string &name, unsigned int width, unsigned int height)
{
    if (glfwInit() == GL_FALSE)
        throw(std::runtime_error("INIT_GLFW::INITIALIZATION_FAILED"));

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef FULL_SCREEN
    window = glfwCreateWindow(width, height, name.c_str(), glfwGetPrimaryMonitor(), NULL);
#else
    window = glfwCreateWindow(width, height, name.c_str(), NULL, NULL);
#endif

    if (!window)
        throw(std::runtime_error("INIT_WINDOW::INITIALIZATION_FAILED"));
    glfwMakeContextCurrent(window);
    //glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
        throw(std::runtime_error("INIT_OPENGL::INITIALIZATION_FAILED"));

    int viewPortWidth, viewportHeight;
    glfwGetFramebufferSize(window, &viewPortWidth, &viewportHeight);
    glViewport(0, 0, viewPortWidth, viewportHeight);

    glClearColor(0.5f, 0.5f, 0.5f, 0.5f);

    // cull face enabled make openGL draw only on one side
    glEnable(GL_CULL_FACE);
    glCullFace(GL_FRONT);
    glFrontFace(GL_CW);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetKeyCallback(window, key_callback);

    windowSize = glm::vec2(width, height);
}

void WindowManager::DestructWindowManager()
{
    glfwTerminate();
}

void WindowManager::StartUpdateLoop(AProgram *game)
{
    while (!glfwWindowShouldClose(window))
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        
        game->Run();

        for (auto it = keyMap.begin(); it != keyMap.end(); it++)
        {
            if (it->second == GLFW_PRESS)
                it->second = GLFW_REPEAT;
        }

        glfwPollEvents();
        glfwSwapBuffers(window);
    }
}

void WindowManager::StopUpdateLoop()
{
    glfwSetWindowShouldClose(window, true);
}

bool WindowManager::IsKeyPressed(int key)
{
    if (keyMap.find(key) == keyMap.end())
    {
        keyMap[key] = GLFW_RELEASE;
        return (false);
    }

    return (keyMap[key] == GLFW_PRESS);
}

bool WindowManager::IsKeyPressedOrMaintain(int key)
{
    if (keyMap.find(key) == keyMap.end())
    {
        keyMap[key] = GLFW_RELEASE;
        return (false);
    }

    return (keyMap[key] == GLFW_PRESS || keyMap[key] == GLFW_REPEAT);
}

bool WindowManager::IsKeyReleased(int key)
{
    if (keyMap.find(key) == keyMap.end())
    {
        keyMap[key] = GLFW_RELEASE;
        return (true);
    }

    return (keyMap[key] == GLFW_RELEASE);
}

bool WindowManager::IsMouseButtonPressed(int mouseButton)
{
    return (glfwGetMouseButton(window, mouseButton) == GLFW_PRESS);
}

GLFWwindow* WindowManager::GetWindow()
{
    return (window);
}

glm::vec2 WindowManager::GetWindowSize()
{
    return (windowSize);
}

unsigned int WindowManager::GetWindowWidth()
{
    return (windowSize.x);
}

unsigned int WindowManager::GetWindowHeight()
{
    return (windowSize.y);
}

void WindowManager::SetMousePosition(double xPos, double yPos)
{
    mousePosition = glm::vec2(xPos, yPos);
}

glm::vec2 WindowManager::GetMousePosition()
{
    return (mousePosition);
}

void WindowManager::SetUserPointer(void *ptr)
{
    glfwSetWindowUserPointer(window, ptr);
}

void WindowManager::SetCharCallback(void (*func)(GLFWwindow *window, unsigned int character))
{
    glfwSetCharCallback(window, func);
}

void WindowManager::SetScrollCallback(void (*func)(GLFWwindow *window, double xOffset, double yOffset))
{
    glfwSetScrollCallback(window, func);
}

void mouse_callback(GLFWwindow *window, double xPos, double yPos)
{
    (void)window;
    WindowManager::SetMousePosition(xPos, yPos);
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    (void)window;
    (void)scancode;
    (void)mods;
    
    if (action == GLFW_REPEAT)
        return;

    WindowManager::SetKeyAction(key, action);
}