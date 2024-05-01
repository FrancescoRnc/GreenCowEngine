#pragma once

#ifndef INCLUDE_CUSTOM
#define INCLUDE_CUSTOM
#include "Helpers/FileReader.h"
#endif // !INCLUDE_CUSTOM


#ifndef INCLUDE_STD
#define INCLUDE_STD
#include <stdint.h>
#include <iostream>
#include <filesystem>
#include <vector>
#include <unordered_map>
#include <stack>
#include <array>
#include <functional>
#endif // !INCLUDE_STD

#ifndef INCLUDE_OPENGL
#define INCLUDE_OPENGL
//#include <GL/glew.h>
#include "glad/glad.h"
#include "KHR/khrplatform.h"
#include <GLFW/glfw3.h>
#endif // !INCLUDE_OPENGL

#ifndef INCLUDE_MATH
#define INCLUDE_MATH
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#endif // !INCLUDE_MATH

#ifndef INCLUDE_STB_IMAGE
#define INCLUDE_STB_IMAGE
#include <stb/stb_image.h>
#endif // !INCLUDE_STB_IMAGE



#define COPY_MOVE_DELETE(I) \
I(const I&) = delete; \
I(I&&) = delete; \
I& operator= (const I&) = delete; \
I& operator= (I&&) = delete; \


namespace GreenCow
{
	struct Vertex
	{
		glm::vec3 position;
		glm::vec3 normal;
		glm::vec2 texCoords;
	};

	class GPUMesh
	{
		public:

		virtual void Setup(std::vector<Vertex> vertices, std::vector<GLint> indices) = 0;

		virtual void Draw(GLuint program) = 0;
	};

	class GPUPipeline
	{
		public:

		virtual void CreateProgram(std::string shaders_name) = 0;

		virtual void Draw() = 0;
	}; 

	class ITexture
	{
		public:

		virtual void Setup() = 0;
	};

	template<typename Key, typename ... Params>
	class FunctionMatcher
	{
		public:
		FunctionMatcher() = default;
		FunctionMatcher(Key _worst_key, std::function<void(Params...)> _dummy_func)
		{
			Matcher = { { _worst_key, _dummy_func } };
		}

		// This adds a new function, with its own key, to be called
		inline void Add(Key key, std::function<void(Params...)> function)
		{
			Matcher.insert({ key, function });
		}

		// This calls your function given a key
		void Call(Key key) noexcept
		{
			auto found = Matcher.find(key);
			Key k = found != Matcher.end() ? key : worst_key;
			Matcher[k]();
		}
		// USE THIS ONLY IF YOUR KEY IS SAFE FROM EXCEPTIONS
		void SimpleCall(Key key) noexcept
		{
			Matcher[key]();
		}

		private:
		std::unordered_map<Key, std::function<void(Params...)>> Matcher;
		Key worst_key;
	};

	class Transform
	{
		public:

		glm::vec3 Position, Rotation, Scale;
		glm::vec3 Right, Up, Front;
		float Angle;

		void Translate(glm::vec3 newPos)
		{
			Position = newPos;
			translationMatrix = glm::translate(glm::mat4(1.0f), Position);
		}
		void AddTranslation(glm::vec3 delta)
		{
			Position += delta;
			Translate(Position);
		}

		void Rotate(glm::vec3 axis, float angleRad)
		{
			Angle = angleRad;
			rotationMatrix = glm::rotate(glm::mat4(1.0f), Angle, axis);
		}
		void AddRotation(glm::vec3 axis, float deltaAngleRad)
		{
			Angle += deltaAngleRad;
			Rotate(axis, Angle);
		}

		void ReScale(glm::vec3 newSc)
		{
			Scale = newSc;
			scaleMatrix = glm::scale(glm::mat4(1.0f), Scale);
		}
		void AddScale(glm::vec3 delta)
		{
			Scale += delta;
			ReScale(Scale);
		}

		//glm::vec3 Forward()
		//{
		//	return glm::cross()
		//}

		//private:
		glm::mat4 modelMatrix;
		glm::mat4 translationMatrix;
		glm::mat4 rotationMatrix;
		glm::mat4 scaleMatrix;

		glm::mat4 forward;
		glm::mat4 right;
		glm::mat4 up;
	};

	// Interfaces
	class IWindow
	{
		public:

		//UNIQUE_INSTANCE_RULE(IWindow)

		virtual const uint32_t GetWidth() const = 0;
		virtual const uint32_t GetHeight() const = 0;

		virtual void Create(const char* title, const int width, const int height) = 0;
		virtual void Clear() = 0;
		virtual void Present() = 0;
		virtual bool Close() = 0;
		virtual void Destroy() = 0;
	};

	class IRenderer
	{
		public:

		virtual void Initialize() = 0;

		virtual void Draw() = 0;
	};

	class ICamera
	{
		public:

		virtual void Setup(GLfloat FOV, GLfloat width, GLfloat height, GLfloat znear, GLfloat zfar) = 0;
		//virtual const glm::mat4 GetView() const = 0;
		//virtual const glm::mat4 GetProjection() const = 0;
		//virtual const glm::vec3 GetPosition() const = 0;
		//virtual const glm::vec3 GetDirection() const = 0;
		//virtual const glm::quat GetRotation() const = 0;
		virtual void LookAt(const glm::vec3 target) = 0;
		virtual void Orbit(const glm::vec3 target, 
						   const float distance, 
						   const float deltaRad) = 0;

		virtual void Update() = 0;
	};

	class ITime
	{
		public:

		virtual const float GetDelta() = 0;

	};

	class IScene
	{
		public:

		virtual void Load(const char* scene_filename) = 0;
		virtual void Unload() = 0;
		virtual void Update(const float deltaTime) = 0;
		virtual void Draw() = 0;
	};
}