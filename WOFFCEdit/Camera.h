#pragma once

#include "pch.h"
class Camera
{
public:
	Camera();
	~Camera();

	void Update(DirectX::SimpleMath::Matrix& view);
	void Rotate(float pitch, float yaw);
	void Move(DirectX::SimpleMath::Vector3 direction);
private:
	//camera
	DirectX::SimpleMath::Vector3		m_camPosition;
	DirectX::SimpleMath::Vector3		m_camOrientation;
	DirectX::SimpleMath::Vector3		m_camLookAt;
	DirectX::SimpleMath::Vector3		m_camLookDirection;
	DirectX::SimpleMath::Vector3		m_camRight;

	float m_camRotRate;
	float m_movespeed;
};

