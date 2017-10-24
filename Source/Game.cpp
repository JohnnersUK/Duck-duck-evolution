#include <Engine/Keys.h>
#include <Engine/Input.h>
#include <Engine/InputEvents.h>
#include <Engine/Sprite.h>

#include "Actions.h"
#include "Constants.h"
#include "Game.h"
#include "GameFont.h"
#include "Player.h"
#include "Pickup.h"


/**
*   @brief   Default Constructor.
*/
SnakeGame::SnakeGame()
{

}


/**
*   @brief   Destructor.
*   @details Remove any non-managed memory and callbacks.
*/
SnakeGame::~SnakeGame()
{
	this->inputs->unregisterCallback(callback_id);

	if (sprite)
	{
		delete sprite;
		sprite = nullptr;
	}

	for (auto& font : GameFont::fonts)
	{
		delete font;
		font = nullptr;
	}
}


/**
*   @brief   Initialises the game.
*   @details The game window is created and all assets required to
			 run the game are loaded. The input callback should also
			 be set in the initialise function. 
*   @return  True if the game initialised correctly.
*/
bool SnakeGame::init()
{
	width = WINDOW_WIDTH;
	height = WINDOW_HEIGHT;
	if (!initAPI())
	{
		return false;
	}

	renderer->setWindowTitle("Snake - Game 2");
	renderer->setClearColour(ASGE::COLOURS::BLACK);
	renderer->setSpriteMode(ASGE::SpriteSortMode::IMMEDIATE);
	toggleFPS();

	// input callback function
	callback_id = this->inputs->addCallbackFnc(ASGE::EventType::E_KEY, &SnakeGame::input, this);
	
	// load fonts we need
	GameFont::fonts[0] = new GameFont(
		renderer->loadFont("..\\..\\Resources\\Fonts\\Comic.ttf", 42), "default", 42);
	
	if (GameFont::fonts[0]->id == -1)
	{
		return false;
	}
	// load snake background sprite
	sprite = renderer->createRawSprite();
	sprite->position[0] = 0;
	sprite->position[1] = 0;
	sprite->scalar = 1.10f;


	if (!sprite->loadTexture("..\\..\\Resources\\Textures\\snake-1200x627.png"))
	{
		return false;
	}

	player.drawPlayer(renderer.get());
	pickup.drawPickup(renderer.get());
	last_pos[0] = 0;
	last_pos[1] = 0;
	new_pos[0] = 0;
	new_pos[1] = 0;
	return true;
}


/**
*   @brief   Should the game exit?
*   @details Has the renderer terminated or the game requesting to exit?
*   @return  True if the game should exit
*/
bool SnakeGame::shouldExit() const
{
	return (renderer->exit() || this->exit);
}


/**
*   @brief   Processes any key inputs and translates them to a GameAction
*   @details This function is added as a callback to handle the game's 
			 input. Key presseses are translated in to GameActions which 
			 are then processed by the main game loop.
*   @param   key is the key the action relates to
*   @param   action whether the key was released or pressed
*   @return  void
*/
void SnakeGame::input(ASGE::SharedEventData data) const
{
	auto key_event = static_cast<ASGE::KeyEvent*>(data.get());
	auto action = key_event->action;
	auto key = key_event->key;

	if (action == ASGE::KEYS::KEY_PRESSED)
	{
		if (key == ASGE::KEYS::KEY_ESCAPE)
		{
			game_action = GameAction::EXIT;
		}

		if (key == ASGE::KEYS::KEY_UP)
		{
			game_action = GameAction::UP;
			player.player_sprite->angle = 0.0f;
		}

		if (key == ASGE::KEYS::KEY_DOWN)
		{
			game_action = GameAction::DOWN;
			player.player_sprite->angle = 3.14f; //Oddly specific that it's in radians rather than degrees
		}

		if (key == ASGE::KEYS::KEY_LEFT)
		{
			game_action = GameAction::LEFT;
			player.player_sprite->angle = 4.71f;
		}

		if (key == ASGE::KEYS::KEY_RIGHT)
		{
			game_action = GameAction::RIGHT;
			player.player_sprite->angle = 1.57f;
		}
	}
}


/**
*   @brief   Updates the scene
*   @details Prepares the renderer subsystem before drawing the
			 current frame. Once the current frame is has finished
			 the buffers are swapped accordingly and the image shown.
*   @return void
*/
void SnakeGame::update(const ASGE::GameTime & time)
{
	i += 1;
	// gamepad input is polled
	auto& gamepad = inputs->getGamePad(0);
	if (gamepad.is_connected &&
		gamepad.buttons[1])
	{
		game_action = GameAction::EXIT;
	}

	// run the game loop
	processGameActions();
	if (i == 30)
	{
		new_pos[0] = player.player_sprite->position[0];
		new_pos[1] = player.player_sprite->position[1];

		player.player_sprite->position[player.player_direction] += player.player_speed*64;

		//TODO Fix this function to properly pass the last position
		for (int x = 0; x < player.getLength(); x++)
		{
			/* For some reason unknown to me, this line of code breaks
			the game and makes the snake body move at a tangent to the
			player body... fuck my life  */
			last_pos[0] = snake_body[x]->body_sprite->position[0]; 
			last_pos[1] = snake_body[x]->body_sprite->position[1];
			snake_body[x]->body_sprite->position[0] = new_pos[0];
			snake_body[x]->body_sprite->position[1] = new_pos[1];
			new_pos[0] = last_pos[0];
			new_pos[1] = last_pos[1];
		}
		i = 0;
	}



	if (player.collision(pickup, snake_body))
	{
		snake_body[player.getLength() - 1]->drawBody(renderer.get());
	}

	// should we terminate the game?
	if (shouldExit())
	{
		signalExit();
	}
}


/**
*   @brief   Renders the scene
*   @details Renders all the game objects to the current frame.
			 Once the current frame is has finished the buffers are 
			 swapped accordingly and the image shown.
*   @return  void
*/
void SnakeGame::render(const ASGE::GameTime &)
{
	renderer->renderSprite(*sprite);
	renderer->renderSprite(*player.player_sprite);
	renderer->renderSprite(*pickup.pickup_sprite);

	//TODO make this render each body part independant
	for (int x = 0; x < player.getLength(); x++)
	{
		renderer->renderSprite(*snake_body[x]->body_sprite);
	}


	renderer->setFont(GameFont::fonts[0]->id);
	renderer->renderText("\nSTART", 375, 325, 1.0, ASGE::COLOURS::DARKORANGE);
}




/**
*   @brief   Processes the next game action
*   @details Uses the game action that was a direct result of 
*            user input. It allows input to processed in a different
             thread and the game actions performed in the main thread. 
*   @return  void
*/
void SnakeGame::processGameActions()
{
	if (game_action == GameAction::EXIT)
	{
		this->exit = true;
	}

	if (game_action == GameAction::UP)
	{
		player.player_direction = 1;
		player.player_speed = -1;
	}

	if (game_action == GameAction::DOWN)
	{
		player.player_direction = 1;
		player.player_speed = 1;
	}

	if (game_action == GameAction::LEFT)
	{
		player.player_direction = 0;
		player.player_speed = -1;
	}

	if (game_action == GameAction::RIGHT)
	{
		player.player_direction = 0;
		player.player_speed = 1;
	}

	game_action = GameAction::NONE;
}