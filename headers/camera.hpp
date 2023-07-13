#pragma once
#ifndef CAMERA_HPP
#define CAMERA_HPP

#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>

namespace skgl {

class Camera
{
private:
	
	// Data
	glm::quat m_dir = glm::quat(0.f, 0.f, 0.f, 1.f); // towards z axis
	glm::quat m_up  = glm::quat(0.f, 0.f, 1.f, 0.f); // towards y axis

public:

	// Data
	glm::vec3 m_pos = glm::vec3(0.f);

	float m_fov = 45.f;
	float m_speed = 1.f;
	float m_sensitivity = 0.1f;

	float m_z_near = 0.1f, m_z_far = 100.f;
	float m_aspect_ratio = 1.f; // aspect ratio of the viewport

	// Methods

	Camera() {}

	void rotate(float degree, const glm::vec3& axis);
	void rotate(const glm::vec3& eulers_degree);

	void set_pos(const glm::vec3& new_pos)
	{ m_pos = new_pos; }

	void move(const glm::vec3& dir)
	{ m_pos += dir; }

	glm::vec3 get_dir() const 
	{ 
		return { m_dir.x, m_dir.y, m_dir.z }; 
	}
	glm::vec3 get_up() const 
	{ 
		return { m_up.x, m_up.y, m_up.z }; 
	}
	glm::vec3 get_right() const { return glm::cross(get_dir(), get_up()); }


	glm::mat4 get_proj() const
	{
		return glm::perspective(m_fov, m_aspect_ratio, m_z_near, m_z_far);
	}
	glm::mat4 look_at() const
	{
		return glm::lookAt(m_pos, m_pos + get_dir(), get_up());
	}
};

} // namespace skgl

#endif // !CAMERA_HPP
