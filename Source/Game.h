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
	//Functions
	SnakeGame();
	~SnakeGame();

	virtual bool init() override;

	//Variables
	Player player;
	Body *snake_body;
	Body *temp_body;
	Pickup pickup;


private:
	//Functions
	void processGameActions(); 
	void input(ASGE::SharedEventData data) const;
	void setPickupPos();
	void updateSnakeBody();

	bool shouldExit() const;

	//render game screens
	void renderMain();
	void renderHelp();
	void renderPlay();
	void renderPause();
	void renderGameOver();

	// Inherited via OGLGame
	virtual void update(const ASGE::GameTime &) override;
	virtual void render(const ASGE::GameTime &) override;

	//Variables
	ASGE::Sprite* sprite = nullptr;    /**< Sprite Object. The background sprite. */
	ASGE::Sprite* pause = nullptr;

	bool exit = false;                 /**< Exit boolean. If true the game loop will exit. */

	float count = 0.0f;
	float game_speed = 30.0f;

	int  callback_id = -1;  /**< Input Callback ID. The callback ID assigned by the game engine. */
	int new_pos[1];
	int menu_option = 1;
};

