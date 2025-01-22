#pragma once
class Action
{
public:
	Action() {};
	~Action() {}

	virtual void ExecuteAction() = 0;
protected:

};

