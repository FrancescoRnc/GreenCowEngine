#pragma once
#include "../GreenCowEngine.h"
#include "../IGPUApi.h"
#include "OpenGL4Time.h"

namespace GreenCow
{
	//class OpenGL4Window;
	//class OpenGL4Camera;
	//class OpenGL4Mesh;
	//class OpenGL4Pipeline;
	//class OpenGL4Time;
	class OpenGL4Api : public IGPUApi
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


		class OpenGL4Window* window;
		class OpenGL4Camera* camera;
		class OpenGL4Pipeline* pipeline;
		class OpenGL4Scene* scene;
		//class OpenGL4Mesh* mesh;
		OpenGL4Time time;

		private:

		void SetupInputBinding();

		FunctionMatcher<int>* InputPressMatcher;
		FunctionMatcher<int>* InputReleaseMatcher;
		float angspd = 0;
		float movespd = 0;
	};

	
	
	

	

	
}
