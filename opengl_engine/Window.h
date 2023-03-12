#pragma once

#include <stdio.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <memory>
#include <iostream>
#include <array>

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

	auto get_keys() { return keys_; };
	float get_x_change();
	float get_y_change();

	void swap_buffers() { glfwSwapBuffers(main_window_.get()); };

private:
	std::shared_ptr<GLFWwindow> main_window_;
	int width_, height_;
	int buffer_width_, buffer_height_;

	std::array<bool, 1024> keys_;

	void create_callbacks();

	float last_x_ = 0.0f;
	float last_y_ = 0.0f;
	float x_change_ = 0.0f;
	float y_change_ = 0.0f;
	bool mouse_first_moved = true;

	static void handle_keys(GLFWwindow* _window, int _key, int _code, int _action, int _mode);
	static void handle_mouse(GLFWwindow* _window, double _x_pos, double _y_pos);
};

