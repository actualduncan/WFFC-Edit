#pragma once
#include "Action.h"
#include "pch.h"
#include "DisplayObject.h"
class PickAction
{
public:
	PickAction();
	PickAction(char keybind, std::vector<DisplayObject>* displayList, float cooldownSeconds = 0.5f);
	void CooldownUpdate(float deltaTime);
	void ResetCooldown();
	bool ExecuteAction(DirectX::SimpleMath::Vector2 screenPosition, RECT viewportRect, DirectX::SimpleMath::Matrix projectionMatrix, DirectX::SimpleMath::Matrix cameraViewMatrix);
	bool OnCooldown();
private:
	char m_keybind = ' ';
	std::vector<DisplayObject>* m_displayList;
	float m_cooldownSeconds;
	float m_cooldown = 0.5f;
};

