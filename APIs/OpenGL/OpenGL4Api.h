#pragma once
#include "../GreenCowEngine.h"
#include "../IGPUApi.h"
#include "Time.h"

namespace OpenGL
{
	//class Window;
	//class Camera;
	//class Mesh;
	//class Pipeline;
	//class Time;
	class OpenGL4Api : public Engine::IGPUApi
	{
		public:

		OpenGL4Api();

		// Inherited via IGPUApi
		void Initialize() override;		
		void LoadFiles() override;

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
		class Camera* camera;
		class Pipeline* pipeline;
		class Scene* scene;
		//class Mesh* mesh;
		Time time;

		private:

		void SetupInputBinding();

		Engine::FunctionMatcher<int>* InputPressMatcher;
		Engine::FunctionMatcher<int>* InputReleaseMatcher;
		float angspd = 0;
		float movespd = 0;
	};

	
	
	

	

	
}
