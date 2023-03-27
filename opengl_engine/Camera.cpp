#include "Camera.h"
#include <iostream>
Camera::Camera(glm::vec3 _start_position, glm::vec3 _start_up, float _start_yaw, float _start_pitch,float _start_move_speed, float _start_turn_speed): 
	position_(_start_position), 
	world_up_(_start_up),
	yaw_(_start_yaw),
	pitch_(_start_pitch),
	movement_speed_(_start_move_speed),
	turn_speed_(_start_turn_speed)
{
	front_position_ = glm::vec3(0.0f, 0.0f, -1.0f);

	update();
}

Camera::~Camera()
{
}

void Camera::key_control(std::span<bool> _keys,float _delta_time)
{
	float velocity = movement_speed_ * _delta_time;

	if (_keys[GLFW_KEY_W])
	{
		position_ += front_position_ * velocity;
	}
	if (_keys[GLFW_KEY_D])
	{
		position_ += right_ * velocity;
	}
	if (_keys[GLFW_KEY_S])
	{
		position_ -= front_position_ * velocity;
	}
	if (_keys[GLFW_KEY_A])
	{
		position_ -= right_ * velocity;
	}
	if (_keys[GLFW_KEY_SPACE])
	{
		//std::cout << "pressed space" << '\n';
		position_ += up_ * velocity;
	}
	if (_keys[GLFW_KEY_LEFT_CONTROL])
	{
		//std::cout << "pressed control" << '\n';
		//position_.x -= front_position_.x * velocity;
		position_ -= up_ * velocity;
	}

}

void Camera::mouse_control(float _x_change, float _y_change)
{
	_x_change *= turn_speed_;
	_y_change *= turn_speed_;
	yaw_ += _x_change;
	pitch_ += _y_change;

	if (pitch_ > 89.0f) 
	{
		pitch_ = 89.0f;
	}

	if (pitch_ < -89.0f)
	{
		pitch_ = -89.0f;
	}

	update();
}

glm::mat4 Camera::calculate_view_matrix()
{
	return glm::lookAt(position_, position_ + front_position_, up_);
}

glm::vec3 Camera::get_camera_position()
{
	return position_;
}

void Camera::update()
{
	front_position_.x = std::cos(glm::radians(yaw_)) * cos(glm::radians(pitch_));
	front_position_.y = sin(glm::radians(pitch_));
	front_position_.z = std::sin(glm::radians(yaw_)) * cos(glm::radians(pitch_));
	front_position_ = glm::normalize(front_position_);

	right_ = glm::normalize(glm::cross(front_position_, world_up_));
	up_ = glm::normalize(glm::cross(right_, front_position_));
}
