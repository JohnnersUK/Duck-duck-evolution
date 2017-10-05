#pragma once
#include <memory>

#include "Gametime.h"
#include "Input.h"
#include "Renderer.h"

namespace ASGE {
	class Game
	{

	public:
		Game() = default;
		~Game() = default;

		virtual bool init() = 0;
		int run();
		void signalExit();

		virtual void update(const GameTime&) = 0;
		
		virtual void beginFrame() = 0;
		virtual void render(const GameTime&) = 0;
		virtual void endFrame() = 0;

		virtual bool initAPI() = 0;
		virtual bool exitAPI() = 0;
		

	protected:
		void toggleFPS();
		void updateFPS();

		std::unique_ptr<Renderer> renderer;
		std::unique_ptr<Input>    inputs;

		int  width      = 640;
		int  height     = 480;
		bool show_fps   = false;	
		bool exit		= false;  /**< Exit boolean. If true the game loop will exit. */

	private:
		static std::chrono::milliseconds getGameTime();
		GameTime us;
	};
}