#pragma once
#include <functional>
#include <vector>
#include <memory>
#include <map>

#include "Gamepad.h"
#include "InputEvents.h"


namespace ASGE {
	class Renderer;
	class Input
	{

	public:
		Input();
		virtual ~Input();
		virtual bool init(Renderer*) = 0;
		virtual void update() = 0;
		virtual void getCursorPos(double &xpos, double &ypos) const = 0;
		virtual const GamePadData getGamePad(int idx) const = 0;


		void sendEvent(EventType, SharedEventData);

		template<typename T, typename T2>
		int addCallbackFnc(EventType type, T fncPtr, T2* obj)
		{
			using namespace std::placeholders;
			return this->registerCallback(type, std::bind(fncPtr, obj, _1));
		}

		template<typename T>
		int addCallbackFnc(EventType type, T fncPtr)
		{
			using namespace std::placeholders;
			return this->registerCallback(type, std::bind(fncPtr, _1));
		}

		void unregisterCallback(unsigned int id);
		bool use_threads = true;

	private:
		using InputFnc = std::function<void(SharedEventData)>;
		int registerCallback(EventType, InputFnc);
		
		using InputFncPair = std::pair<EventType, InputFnc>;
		using InputFncs = std::vector<InputFncPair>;
		InputFncs callback_funcs;
	};
}

