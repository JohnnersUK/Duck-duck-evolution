#pragma once
#include "NonCopyable.h"
namespace ASGE
{
	enum class SpriteSortMode
	{
		IMMEDIATE,
		DEFERRED,
		TEXTURE,
		BACK_TO_FRONT,
		FRONT_TO_BACK
	};

	class Texture2D
	{
	public:
		Texture2D(int width, int height)
		{
			dims[0] = width;
			dims[1] = height;
		}
			
		virtual ~Texture2D() = default;

		enum Format
		{
			MONOCHROME = 1,
			MONOCHROME_ALPHA = 2,
			RGB = 3,
			RGBA = 4
		};

		void setFormat(Format f) {	format = f; }
		Format getFormat() const { return format;}

		virtual void  setData(void* data) = 0;
		virtual void* getData() = 0;

		unsigned int getWidth()  const { return dims[0]; }
		unsigned int getHeight() const { return dims[1]; }

	protected:
		Format format = RGB;			/**< Texture2D Format. The pixel format used when loading the texture file. */
		unsigned int dims[2]{ 0,0 };	/**< Texture2D Dimensions. The dimensions of the loaded texture file. */
	};
}