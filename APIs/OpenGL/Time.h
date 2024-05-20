#pragma once

#include "../Engine/GreenCowEngine.h"

namespace OpenGL
{
	class Time : public Engine::ITime
	{
	public:

		const double GetDelta() override;

	private:

		double last{ 0.f }, now{ 0.f };
	};
}