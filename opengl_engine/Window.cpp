#include "Window.h"
#include <memory>

Window::Window()
{
	width_ = 800;
	height_ = 600;
}

Window::Window(int _width, int _height): width_(_width), height_(_height)
{
	
}

Window::~Window()
{
    glfwDestroyWindow(main_window_.get());
    glfwTerminate();
}

int Window::initialise()
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

    main_window_ = std::shared_ptr<GLFWwindow>( glfwCreateWindow(width_, height_, "Test window", nullptr, nullptr) );

    if (!main_window_)
    {
        std::cout << "GLFW window creation failed" << '\n';
        glfwTerminate();
        return 1;
    }

    
    glfwGetFramebufferSize(main_window_.get(), &buffer_width_, &buffer_height_);

    // set context for GLEW to use
    glfwMakeContextCurrent(main_window_.get());

    // Allow modern extension features
    glewExperimental = GL_TRUE;

    if (glewInit() != GLEW_OK)
    {
        std::cout << "glew initialization failed" << '\n';
        glfwDestroyWindow(main_window_.get());
        glfwTerminate();
        return 1;
    }

    // enable depth test
    glEnable(GL_DEPTH_TEST);

    // Setup viewport size

    glViewport(0, 0, buffer_width_, buffer_height_);
}
