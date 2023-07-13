#include "camera.hpp"

#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>

namespace skgl {

void Camera::rotate(float degree, const glm::vec3& axis)
{
	auto a = glm::radians(degree / 2);
	auto l = glm::normalize(axis);
	const glm::quat q(
		cosf(a),
		l.x * sinf(a),
		l.y * sinf(a),
		l.z * sinf(a)
		);

	m_dir = q * m_dir * glm::conjugate(q);

	m_up = q * m_up * glm::conjugate(q);
}


// pitch yaw roll
void skgl::Camera::rotate(const glm::vec3& degrees)
{
	glm::quat q(degrees);
	m_dir = q * m_dir * glm::conjugate(q);
	m_up = q * m_up * glm::conjugate(q);
}

} // namespace skgl