#pragma once
#include "GreenCowEngine.h"

namespace Engine
{
	class IGPUApi
	{
		public:

		COPY_MOVE_DELETE(IGPUApi)

		virtual void Initialize() = 0;
		virtual void LoadFiles() = 0;

		virtual bool IsWindowOpen() = 0;
		virtual void DequeueEvents() = 0;

		virtual void Start() = 0;

		// This function updates Physics, Input controlls etc. if needed
		virtual void Update() = 0;

		// This clears the screen
		virtual void Clear() = 0;
		
		// Free implementation for drawing meshes
		virtual void Draw() = 0;

		// Here you could use SwapChain and other techniques
		virtual void Present() = 0;

		// Once finished the game loop, Exit handles objects destruction
		virtual void Exit() = 0;


		protected:

		IGPUApi() = default;
	};

}


