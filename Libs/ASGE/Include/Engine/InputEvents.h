#pragma once
#include "Keys.h"
namespace ASGE
{
	enum EventType
	{
		E_KEY,
		E_MOUSE_CLICK,
		E_MOUSE_SCROLL,
		E_MOUSE_MOVE,
		E_GAMEPAD_STATUS
	};


	// @todo
	// create a look up hash table, referened by hash/string
	// returns a value, should we use <T> or a generic value 
	struct EventData
	{

	};

	struct KeyEvent : public EventData
	{
		int key			= -1;
		int scancode	= -1;
		int action		= -1;
		int mods		= -1;
	};

	struct ClickEvent : public EventData
	{
		int button	= -1;
		int action	= -1;
		int mods	= -1;
	};

	struct ScrollEvent : public EventData
	{
		double xoffset = 0;
		double yoffset = 0;
	};

	struct MoveEvent : public EventData
	{
		double xpos = 0;
		double ypos = 0;
	};

	struct GamePadEvent : public EventData
	{
		bool connected = false;
	};

	using SharedEventData = std::shared_ptr<EventData>;
}