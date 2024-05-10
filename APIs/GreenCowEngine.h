#pragma once

#define COPY_MOVE_DELETE(I) \
I(const I&) = delete; \
I(I&&) = delete; \
I& operator= (const I&) = delete; \
I& operator= (I&&) = delete; \

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
#include <memory>
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

#ifndef INCLUDE_ENGINE
#define INCLUDE_ENGINE
#include "Transform.h"
#endif // !INCLUDE_ENGINE

#ifndef INCLUDE_HELPERS
#define INCLUDE_HELPERS
#include "Helpers/FileReader.h"
#include "Helpers/FileWriter.h"
#include "Helpers/SerializedDataRetriever.h"
#include "Helpers/AssetWrapper.h"
#include "Helpers/AssetsLoader.h"
#endif // !INCLUDE_HELPERS


namespace Engine
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

		virtual void Setup(std::vector<Vertex> vertices, std::vector<int> indices) = 0;

		virtual void Draw(uint32_t program) = 0;
	};

	class GPUPipeline
	{
		public:

		virtual void CreateProgram(std::string programName, std::vector<std::string> files, bool useAsDefault) = 0;

		virtual void Draw() = 0;
	}; 

	class ITexture
	{
		public:

		virtual void Setup() = 0;
	};

	template<typename T>
	class ISerializable
	{
	public:
		virtual void Serialize() = 0;
		virtual T Deserialize() = 0;
	};

	class IUpdatable
	{
	public:
		virtual void Update(const float deltaTime) = 0;
	};
	class IDrawable
	{
	public:
		virtual void Draw() = 0;
	};

	class IWindow
	{
		public:

		//UNIQUE_INSTANCE_RULE(IWindow)

		virtual const uint32_t GetWidth() const = 0;
		virtual const uint32_t GetHeight() const = 0;

		virtual void Create(const char* title, const int width, const int height) = 0;
		virtual void Show() = 0;
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

		virtual void Setup(float FOV, float width, float height, float znear, float zfar) = 0;
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
		virtual void Init() = 0;
		virtual void Update(const float deltaTime) = 0;
		virtual void Draw() = 0;
	};

	class IAppController
	{

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

}

using namespace Engine;