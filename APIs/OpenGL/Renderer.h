#pragma once
#include "../Engine/GreenCowEngine.h"
#include "Pipeline.h"
#include "Shader.h"
#include "Mesh.h"
#include "../Engine/CameraController.h"

namespace OpenGL
{
	class Renderer
	{
		Pipeline* pipeline{ nullptr };
		Camera* refCamera{ nullptr };
		std::vector<Mesh*> meshes{};

	public:

		COPY_MOVE_DELETE(Renderer)

		Renderer(){}
		Renderer(Pipeline* _pipeline) : pipeline(_pipeline), meshes{}
		{
			refCamera = static_cast<Camera*>(CameraController::Get()->GetActiveCamera());
		}

		void InjectMeshes(std::vector<Mesh*> inMeshes);

		void Draw();

	private:
		
	};
}

