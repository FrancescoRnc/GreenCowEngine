#pragma once
#include "../Engine/GreenCowEngine.h"

namespace Engine
{
	class CameraController
	{
		static CameraController* _instance;
		ICamera* ActiveCamera{ nullptr };

	public:
		CameraController()
		{
			_instance = this;
		}

		CameraController(ICamera* startingCamera) : ActiveCamera(startingCamera) 
		{
			_instance = this;
		}


		static CameraController* Get();

		ICamera* GetActiveCamera() const;

		void Possess(ICamera* newCamera);
	};
}

