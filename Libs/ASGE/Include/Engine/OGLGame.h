#pragma once
#include <Engine/Game.h>

namespace ASGE {
	class OGLGame: public Game
	{
	public:
		// Inherited via Game
		virtual bool initAPI() override final;
		virtual bool exitAPI() override final;
		virtual void beginFrame() override final;
		virtual void endFrame() override final;
	};
}