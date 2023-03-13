#pragma once
#include <gl/glew.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <span>

#include <GLFW/glfw3.h>

class Camera
{
public:
	Camera() = default;
	Camera(glm::vec3 _start_position, glm::vec3 _start_up, float _start_yaw, float _start_pitch, float _start_move_speed, float _start_turn_speed);
	~Camera();

	void key_control(std::span<bool> _keys,float _delta_time);
	void mouse_control(float _x_change, float _y_change);

	glm::mat4 calculate_view_matrix();

private:
	void update();


private:
	glm::vec3 position_;
	glm::vec3 front_position_;
	glm::vec3 up_;
	glm::vec3 right_;
	glm::vec3 world_up_;

	float yaw_;
	float pitch_;

	float movement_speed_;
	float turn_speed_;

	
};

