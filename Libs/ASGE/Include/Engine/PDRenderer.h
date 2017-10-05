#pragma once
#include "Engine/renderer.h"

namespace ASGE {
	class PDRenderer: public Renderer
	{
	public:
		PDRenderer();
		~PDRenderer();

		bool init(int w, int h) override;
		bool exit() override;
		void renderText(const char* str, int x, int y, float) override;
		void prefresh() override;
		void update() override;

	private:

		// Inherited via Renderer
		virtual std::shared_ptr<Input> inputPtr() override;

	};
}
