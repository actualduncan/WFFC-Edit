#pragma once

#include "pch.h"
#include "InputCommands.h"
#include "StepTimer.h"


class Camera
{
public:
	Camera(HWND hwnd, int windowWidth, int windowHeight );
	~Camera();

	void Update(InputCommands input, DX::StepTimer const& timer);

	void Rotate(int deltaX, int deltaY, float dt);
	void Move(DirectX::SimpleMath::Vector3 direction, float dt);

	DirectX::SimpleMath::Matrix GetView();

private:

	void CalculateView();

	//camera
	DirectX::SimpleMath::Vector3		m_camPosition;
	DirectX::SimpleMath::Vector3		m_camRotation ;
	DirectX::SimpleMath::Vector3		m_camLookAt;
	DirectX::SimpleMath::Vector3		m_camUp;
	DirectX::SimpleMath::Vector3		m_camRight;
	DirectX::SimpleMath::Vector3		m_forward;
	DirectX::SimpleMath::Matrix         m_rotationMatrix;
	DirectX::SimpleMath::Matrix         m_view;

	float m_camRotRate;
	float m_movespeed;

	int m_width;
	int m_height;

	POINT m_cursor;
	HWND m_hwnd;

	bool isMouseActive = false;;
};

