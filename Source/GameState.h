#pragma once
#include <atomic>
enum class GameState
{
	MAIN,
	PLAY,
	HELP,
	PAUSE,
	GAMEOVER
};

extern std::atomic<GameState> game_state;