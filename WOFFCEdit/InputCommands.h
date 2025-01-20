#pragma once

struct InputCommands
{
	void Reset() {
		horizontal_z = 0.0f;
		horizonal_x = 0.0f;
		vertical = 0.0f;
		pitch = 0.0f;
		yaw = 0.0f;

	}
	float horizontal_z;
	float horizonal_x;
	float vertical;
	float pitch;
	float yaw;
};
