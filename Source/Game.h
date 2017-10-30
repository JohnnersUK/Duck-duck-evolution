#pragma once
#include <string>
#include <Engine/OGLGame.h>
#include <vector>
#include "Player.h"
#include "Body.h"
#include "Pickup.h"

struct GameFont;

/**
*  SnakeGame. An OpenGL Game based on ASGE.
*/

class SnakeGame:
	public ASGE::OGLGame
{
public:
	SnakeGame();
	~SnakeGame();
	virtual bool init() override;
	Player player;
	Body *snake_body[100];
	Pickup pickup;


private:
	void processGameActions(); 
	void input(ASGE::SharedEventData data) const;
	bool shouldExit() const;

	// Inherited via OGLGame
	virtual void update(const ASGE::GameTime &) override;
	virtual void render(const ASGE::GameTime &) override;

	int  callback_id = -1;             /**< Input Callback ID. The callback ID assigned by the game engine. */
	bool exit = false;                 /**< Exit boolean. If true the game loop will exit. */
	ASGE::Sprite* sprite = nullptr;    /**< Sprite Object. The background sprite. */

	int count = 0;
	int new_pos[1];
	int menu_option = 0;

	void updateSnakeBody();
	void renderMain();
	void renderPlay();
	void renderGameOver();
};

