#include "Camera.h"

Camera::Camera()
	: m_camPosition(0.0f, 3.7f, -3.5f)
	, m_camOrientation(0.0f, 0.0f, 0.0f)
	, m_camLookAt(0.0f, 0.0f, 0.0f)
	, m_camLookDirection(0.0f, 0.0f, 0.0f)
	, m_camRight(0.0f, 0.0f, 0.0f)
	, m_camRotRate(0.30f)
	, m_movespeed(30.0f)
{

}

Camera::~Camera()
{

}

void Camera::Update()
{

}