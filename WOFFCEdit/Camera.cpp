#include "Camera.h"
#include <algorithm>
#include <iostream>
#include "DisplayObject.h"
using namespace DirectX;
using namespace DirectX::SimpleMath;

float clamp(float n, float lower, float upper)
{
	return n <= lower ? lower : n >= upper ? upper : n;
}

Camera::Camera(HWND window, float aspectRatio, std::vector<DisplayObject>* displayList, float minZ, float maxZ)
	: m_camPosition(0.0f, 3.7f, -3.5f)
	, m_camRotation(0.0f, 0.0f, 0.0f)
	, m_camLookAt(0.0f, 0.0f, 1.0f)
	, m_camRight(0.0f, 0.0f, 0.0f)
	, m_camRotRate(0.1f)
	, m_movespeed(30.0f)
	, m_window(window)
	, m_cursor()
{

	WindowSizeChanged(aspectRatio, minZ, maxZ);
	
	pAction = PickAction(' ', displayList);
}

Camera::~Camera()
{

}

void Camera::WindowSizeChanged(float aspectRatio, float minZ, float maxZ)
{
	float fovAngleY = 70.0f * XM_PI / 180.0f;

	// This is a simple example of change that can be made when the app is in
	// portrait or snapped view.
	if (aspectRatio < 1.0f)
	{
		fovAngleY *= 2.0f;
	}

	m_projectionMatrix = Matrix::CreatePerspectiveFieldOfView(
		fovAngleY,
		aspectRatio,
		minZ,
		maxZ
	);
}

void Camera::Update(InputCommands input, DX::StepTimer const& timer)
{
	GetClientRect(m_window, &m_viewportRect);

	m_cursor.x = input.mouseX;
	m_cursor.y = input.mouseY;

	float deltaTime = timer.GetElapsedSeconds();
 	if (input.mouseRButtonDown && isMouseActive)
	{
		int deltax = m_cursor.x - (m_viewportRect.right / 2);
		int deltay = m_cursor.y - (m_viewportRect.bottom / 2);
		
		Rotate(deltax, deltay, deltaTime);
		m_cursor.x = (m_viewportRect.right / 2);
		m_cursor.y = (m_viewportRect.bottom / 2);

		SetCursorPos(m_cursor.x, m_cursor.y);
	}
	
	if (input.mouseRButtonDown && !isMouseActive)
	{
		m_cursor.x = (m_viewportRect.right / 2);
		m_cursor.y = (m_viewportRect.bottom / 2);

		SetCursorPos(m_cursor.x, m_cursor.y);
		ShowCursor(false);
		isMouseActive = true;
	}

	if (!input.mouseRButtonDown && isMouseActive)
	{
		ShowCursor(true);
		isMouseActive = false;
	}
	


	
	Move(Vector3(input.horizontalX, input.vertical, input.horizontalZ), deltaTime);

	CalculateView();

	if (input.mouseLButtonDown && !pAction.OnCooldown())
	{
		if (ScreenToClient(m_window, &m_cursor))
		{
			intersected = pAction.ExecuteAction(Vector2(m_cursor.x, m_cursor.y), m_viewportRect, m_projectionMatrix, m_view);
		}
	}

	pAction.CooldownUpdate(deltaTime);
}

void Camera::CalculateView()
{
	float pitch = m_camRotation.x * 0.0174532f;
	float yaw = m_camRotation.y * 0.0174532f;
	float roll = m_camRotation.z * 0.0174532f;

	m_camLookAt = Vector3(0.0, 0.0, 1.0f);
	Matrix rotationMatrix = Matrix::CreateFromYawPitchRoll(yaw, pitch, roll);

	m_camLookAt = Vector3::Transform(m_camLookAt, rotationMatrix);
	m_camLookAt = m_camLookAt + m_camPosition;

	m_camUp = Vector3::Transform(Vector3::UnitY, rotationMatrix);
	m_camRight = Vector3::Transform(Vector3::UnitX, rotationMatrix);
	m_forward = m_camUp.Cross(-m_camRight);

	m_view = Matrix::CreateLookAt(m_camPosition, m_camLookAt, Vector3::UnitY);
}

void Camera::Rotate(int deltaX, int deltaY, float dt)
{
	m_camRotation.x += deltaY / m_camRotRate * dt;
    m_camRotation.y -= deltaX / m_camRotRate * dt;
	m_camRotation.z = 0;

	// clamp x rotation by 90 degrees
	m_camRotation.x = clamp(m_camRotation.x, -90.0f, 90.0f);
}

void Camera::Move(Vector3 direction, float dt)
{
	direction.Normalize();
	
	m_camPosition += (m_forward * (direction.z * m_movespeed)) * dt;
	m_camPosition += (-m_camRight * (direction.x * m_movespeed)) * dt;
	m_camPosition += (Vector3::UnitY * (direction.y * m_movespeed)) * dt;
}


Matrix Camera::GetView()
{
	return m_view;
}

void Camera::SetProjection(Matrix projectionMatrix)
{
	m_projectionMatrix = projectionMatrix;
}

Matrix Camera::GetProjectionMatrix()
{
	return m_projectionMatrix;
}