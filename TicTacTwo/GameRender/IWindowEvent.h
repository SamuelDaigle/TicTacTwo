#pragma once

enum WIN_EVENEMENT{ NONE, CLICK, QUIT };

class IWindowEvent
{
public:
	virtual WIN_EVENEMENT getEventType() const = 0;

private:
	WIN_EVENEMENT eventType;
};