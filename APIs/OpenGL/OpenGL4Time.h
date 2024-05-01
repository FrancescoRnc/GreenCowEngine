#pragma once

#include "../GreenCowEngine.h"

namespace GreenCow
{
	class OpenGL4Time : public ITime
	{
		public:

		const float GetDelta() override;

		private:

		float last, now;
	};
}