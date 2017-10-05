#pragma once
#include <memory>
#include <Engine\Colours.h>

namespace ASGE {
	class Renderer;
	class Texture2D;

	/**
	*  Sprite. An ASGE supported sprite which can be used 
	*  to render and load textures.
	*/

	class Sprite
	{
	public:
		virtual ~Sprite() = default;
		virtual bool loadTexture(const char*) = 0;
		virtual const Texture2D* getTexture() const = 0;

	public:
		float position[2] { 0,0 };		  /**< Sprite Position. The sprites position on the screen. */
		unsigned int dims[2]{ 0,0 };      /**< Sprite Dimensions. The dimensions of the loaded texture file. */
		float angle = 0.0f;				  /**< Sprite Rotation. Rotation around the sprite's origin. */
		float scalar = 1.0f;              /**< Sprite Scale. Scales the sprite equally in both dims. */
		Colour tint = COLOURS::WHITE;	  /**< Sprite Colour. Sets the colour of the sprite. */
	};
}