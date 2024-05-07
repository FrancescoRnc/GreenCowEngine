#pragma once
#include "../GreenCowEngine.h"

namespace OpenGL
{
	class Window : public Engine::IWindow
	{
		public:

		~Window();

		// Inherited via IWindow
		const uint32_t GetWidth() const override { return width; };
		const uint32_t GetHeight() const override { return height; };
		void Create(const char* title, const int width, const int height) override;
		void Show() override;
		void Clear() override;
		void Present() override;
		bool Close() override;
		void Destroy() override;
		// - - - -

		GLFWwindow* GetWindowData() { return internal_window; }

		bool IsOpen = true;


		private:

		GLFWwindow* internal_window = NULL;
		uint32_t width = 0;
		uint32_t height = 0;
		glm::vec4 clearColor = glm::vec4(0.0f);
	};
}