#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>

const GLint WIDTH = 800, HEIGHT = 600;

int main()
{
    //initialize GLFW
    if (!glfwInit())
    {
        std::cout << "GLFINIT failed" << '\n';
        glfwTerminate();
        return 1;
    }

    // setup glfw window properties
    // opengl version

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

    // Core profile = no backwards compatibility
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // Allow forward compatibility
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    GLFWwindow* main_window = glfwCreateWindow(WIDTH, HEIGHT, "Test window", nullptr, nullptr);

    if (!main_window)
    {
        std::cout << "GLFW window creation failed" << '\n';
        glfwTerminate();
        return 1;
    }

    // get buffer size information, later used for viewport
    int buffer_width, buffer_height;
    glfwGetFramebufferSize(main_window, &buffer_width, &buffer_height);

    // set context for GLEW to use
    glfwMakeContextCurrent(main_window);

    // Allow modern extension features
    glewExperimental = GL_TRUE;

    if (glewInit() != GLEW_OK) 
    {
        std::cout << "glew initialization failed" << '\n';
        glfwDestroyWindow(main_window);
        glfwTerminate();
        return 1;
    }

    // Setup viewport size

    glViewport(0, 0, buffer_width, buffer_height);

    // Loop until window closed
    while (!glfwWindowShouldClose(main_window))
    {
        // get + handle user input events

        glfwPollEvents();

        // clear window
        glClearColor(1.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glfwSwapBuffers(main_window);
    }

    return 0;
}