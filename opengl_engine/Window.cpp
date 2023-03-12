#include "Window.h"
#include <memory>

Window::Window()
{
	width_ = 800;
	height_ = 600;

    for (size_t i = 0; i < 1024; i++)
    {
        keys_[i] = 0;
    }
}

Window::Window(int _width, int _height): width_(_width), height_(_height)
{
    for (size_t i = 0; i < 1024; i++)
    {
        keys_[i] = 0;
    }
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

    create_callbacks();

    glfwSetInputMode(main_window_.get(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);

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

    glfwSetWindowUserPointer(main_window_.get(), this);
}

float Window::get_x_change()
{
    float change = x_change_;
    x_change_ = 0;
    return change;
}

float Window::get_y_change()
{
    float change = y_change_;
    y_change_ = 0;
    return change;
}

void Window::create_callbacks()
{
    glfwSetKeyCallback(main_window_.get(), handle_keys);
    glfwSetCursorPosCallback(main_window_.get(), handle_mouse);
}

void Window::handle_mouse(GLFWwindow* _window, double _x_pos, double _y_pos)
{
    Window* the_window = static_cast<Window*>(glfwGetWindowUserPointer(_window));

    if (the_window->mouse_first_moved)
    {
        the_window->last_x_ = _x_pos;
        the_window->last_y_ = _y_pos;
        the_window->mouse_first_moved = false;
    }

    the_window->x_change_ = _x_pos - the_window->last_x_;
    the_window->y_change_ = the_window->last_y_ - _y_pos;

    the_window->last_x_ = _x_pos;
    the_window->last_y_ = _y_pos;

}

void Window::handle_keys(GLFWwindow* _window, int _key, int _code, int _action, int _mode)
{
    Window* the_window = static_cast<Window*>(glfwGetWindowUserPointer(_window));

    if (_key == GLFW_KEY_ESCAPE && _action == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(_window, GL_TRUE);
    }

    if (_key >= 0 && _key < 1024)
    {
        if (_action == GLFW_PRESS)
        {
            the_window->keys_[_key] = true;
            std::cout << "pressed: " << _key << '\n';
        }
        else if(_action == GLFW_RELEASE)
        {
            the_window->keys_[_key] = false;
            std::cout << "released: " << _key << '\n';
        }
    }
}


