#include "Camera.h"

Camera::Camera()
	: m_camPosition(0.0f, 3.7f, -3.5f)
	, m_camOrientation(0.0f, 0.0f, 0.0f)
	, m_camLookAt(0.0f, 0.0f, 0.0f)
	, m_camLookDirection(0.0f, 0.0f, 0.0f)
	, m_camRight(0.0f, 0.0f, 0.0f)
	, m_camRotRate(3.0f)
	, m_movespeed(0.30f)
{

}

Camera::~Camera()
{

}

void Camera::Update(DirectX::SimpleMath::Matrix& view)
{
	//create look direction from Euler angles in m_camOrientation
	m_camLookDirection.x = sinf((m_camOrientation.y) * 3.1415f / 180.0f);
	m_camLookDirection.z = cosf((m_camOrientation.y) * 3.1415f / 180.0f);
	m_camLookDirection.Normalize();

	//create right vector from look Direction
	m_camLookDirection.Cross(DirectX::SimpleMath::Vector3::UnitY, m_camRight);

	m_camLookAt = m_camPosition + m_camLookDirection;

	view = DirectX::SimpleMath::Matrix::CreateLookAt(m_camPosition, m_camLookAt, DirectX::SimpleMath::Vector3::UnitY);
}

void Camera::Rotate(float pitch, float yaw)
{

	m_camOrientation.y += yaw * m_camRotRate;
}

void Camera::Move(DirectX::SimpleMath::Vector3 direction)
{

	m_camPosition += m_camLookDirection * (direction.z * m_movespeed);
	m_camPosition += m_camRight * (direction.x * m_movespeed);

}
