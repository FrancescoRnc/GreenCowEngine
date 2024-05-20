#pragma once
#include "../Engine/GreenCowEngine.h"
#include "../Engine/IGPUApi.h"
#include "Time.h"

namespace OpenGL
{
	class OpenGL4Api : public Engine::IGPUApi
	{
		public:

		OpenGL4Api();

		// Inherited via IGPUApi
		void Initialize() override;		
		void LoadFiles() override;

		void Start() override;
		bool IsWindowOpen() override;
		void DequeueEvents() override;
		void Update() override;

		void Clear() override;
		void Draw() override;
		void Present() override;

		void Exit() override;
		// - - - -

		void CallKeyFunc(int action, int key);


		class Window* window;
		class Pipeline* pipeline;
		//class Renderer* renderer;
		class Scene* activeScene;
		Time time;

		private:

		void SetupInputBinding();

		Engine::FunctionMatcher<int>* InputPressMatcher;
		Engine::FunctionMatcher<int>* InputReleaseMatcher;
		float angspd = 0;
		float movespd = 0;
	};

	
	
	

	

	
}
