#pragma once
#include <atomic>
enum class GameState
{
	MAIN,
	PLAY,
	PAUSE,
	GAMEOVER
};

extern std::atomic<GameState> game_state;