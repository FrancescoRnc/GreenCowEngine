#include "CameraController.h"

Engine::CameraController* Engine::CameraController::_instance = nullptr;

CameraController* Engine::CameraController::Get()
{
    return _instance ? _instance : new CameraController();
}

ICamera* Engine::CameraController::GetActiveCamera() const
{
    return ActiveCamera;
}

void Engine::CameraController::Possess(ICamera* newCamera)
{
    ActiveCamera = newCamera;
}
