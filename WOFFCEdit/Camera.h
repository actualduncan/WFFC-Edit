#pragma once

#include "pch.h"
#include "InputCommands.h"
#include "StepTimer.h"
#include "Action.h"
#include "PickAction.h"
#include "DisplayObject.h"
class Camera
{
public:
	Camera(HWND window, float aspectRatio, std::vector<DisplayObject>* displayList, float minZ = 0.01f, float maxZ = 1000.0f);
	~Camera();

	void SetProjection(DirectX::SimpleMath::Matrix);
	void WindowSizeChanged(float aspectRatio, float minZ = 0.01f, float maxZ = 1000.0f);
	void Update(InputCommands input, DX::StepTimer const& timer);

	void Rotate(int deltaX, int deltaY, float dt);
	void Move(DirectX::SimpleMath::Vector3 direction, float dt);

	DirectX::SimpleMath::Matrix GetView();
	DirectX::SimpleMath::Matrix GetProjectionMatrix();

	bool intersected = false;
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

	DirectX::SimpleMath::Matrix        m_projectionMatrix;

	RECT m_viewportRect;

	float m_camRotRate;
	float m_movespeed;

	POINT m_cursor;
	HWND m_window;

	bool isMouseActive = false;;

	PickAction pAction;


};

