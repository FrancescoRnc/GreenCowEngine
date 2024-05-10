#pragma once

#include "../GreenCowEngine.h"

namespace OpenGL
{
	class Time : public Engine::ITime
	{
		public:

		const float GetDelta() override;

		private:

		float last, now = 0.f;
	};
}