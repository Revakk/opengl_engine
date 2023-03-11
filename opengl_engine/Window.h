#pragma once

#include <stdio.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <memory>
#include <iostream>

class Window
{
public:
	Window();
	Window(int _width, int _height);
	~Window();

	int initialise();

	float get_buffer_width() { return buffer_width_; };
	float get_buffer_height() { return buffer_height_; };

	bool get_should_close() { return glfwWindowShouldClose(main_window_.get()); }

	void swap_buffers() { glfwSwapBuffers(main_window_.get()); };

private:
	std::shared_ptr<GLFWwindow> main_window_;
	int width_, height_;
	int buffer_width_, buffer_height_;

};

