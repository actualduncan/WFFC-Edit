#pragma once
class Action
{
public:
	Action();
	~Action() {}

	virtual void ExecuteAction() = 0;
	char GetKeybind() { return m_keybind; }
protected:
	char m_keybind;
};

