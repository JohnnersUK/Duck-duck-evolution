#pragma once
#include <chrono>
#include <chrono>
namespace ASGE {
	struct GameTime
	{
		// The time point of the current frame
		std::chrono::time_point<std::chrono::steady_clock> frame_time = std::chrono::steady_clock::now();

		// The amount of elapsed game time since the last update.
		std::chrono::duration<double, std::milli> delta_time;

		// The amount of time since the start of the game.
		std::chrono::milliseconds game_time;
	};
}