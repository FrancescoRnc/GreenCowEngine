#include "Pipeline.h"
#include "DataArchivers/GameDataArchiver.h"
#include "Shader.h"
#include "Material.h"
#include "Mesh.h"
#include "../Engine/CameraController.h"
#include "../Helpers/AssetManager.h"

/*GLuint OpenGL::Pipeline::_getVertexShaderFromSource(std::string shaderFilename)
{
	Helpers::AssetContent* vsAsset = Helpers::AssetManager::Get()->GetAsset(shaderFilename);
	GLint vssize = static_cast<GLint>(vsAsset->Size());
	auto vertex_shader = glCreateShader(GL_VERTEX_SHADER);
	std::string vssource = reinterpret_cast<char*>(vsAsset->GetSource()->data());
	auto vssource_c = vssource.c_str();
	glShaderSource(vertex_shader, 1, &vssource_c, &vssize);
	glCompileShader(vertex_shader);

	int compile_result = 0;
	glGetShaderiv(vertex_shader, GL_COMPILE_STATUS, &compile_result);
	if (compile_result == GL_FALSE)
	{
		int info_log_length = 0;
		glGetShaderiv(vertex_shader, GL_INFO_LOG_LENGTH, &info_log_length);
		std::vector<char> shader_log(info_log_length);
		glGetShaderInfoLog(vertex_shader, info_log_length, NULL, &shader_log[0]);
		std::cout << "Error compiling vertex shader from file: " << vsAsset->Filepath() << std::endl
			<< &shader_log[0] << std::endl;

		return 0;
	}
	return vertex_shader;
}

GLuint OpenGL::Pipeline::_getFragmentShaderFromSource(std::string shaderFilename)
{
	Helpers::AssetContent* fsAsset = Helpers::AssetManager::Get()->GetAsset(shaderFilename);
	GLint fssize = static_cast<GLint>(fsAsset->Size());
	auto fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
	std::string fssource = reinterpret_cast<char*>(fsAsset->GetSource()->data());
	auto fssource_c = fssource.c_str();
	glShaderSource(fragment_shader, 1, &fssource_c, &fssize);
	glCompileShader(fragment_shader);

	int compile_result = 0;
	glGetShaderiv(fragment_shader, GL_COMPILE_STATUS, &compile_result);
	if (compile_result == GL_FALSE)
	{
		int info_log_length = 0;
		glGetShaderiv(fragment_shader, GL_INFO_LOG_LENGTH, &info_log_length);
		std::vector<char> shader_log(info_log_length);
		glGetShaderInfoLog(fragment_shader, info_log_length, NULL, &shader_log[0]);
		std::cout << "Error compiling fragment shader from file: " << fsAsset->Filepath() << std::endl
			<< &shader_log[0] << std::endl;

		return 0;
	}
	return fragment_shader;
}*/

GLuint OpenGL::Pipeline::_getShaderFromSource(GLenum shaderType, std::string shaderFilename)
{
	Helpers::AssetContent* asset = Helpers::AssetManager::Get()->GetAsset(shaderFilename);
	GLint size = static_cast<GLint>(asset->Size());
	auto shader = glCreateShader(shaderType);
	std::string source = reinterpret_cast<char*>(asset->GetSource()->data());
	auto source_c = source.c_str();
	glShaderSource(shader, 1, &source_c, &size);
	glCompileShader(shader);

	int compile_result = 0;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &compile_result);
	if (compile_result == GL_FALSE)
	{
		int info_log_length = 0;
		glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &info_log_length);
		std::vector<char> shader_log(info_log_length);
		glGetShaderInfoLog(shader, info_log_length, NULL, &shader_log[0]);
		std::cout << "Error compiling fragment shader from file: " << asset->Filepath() << std::endl
			<< &shader_log[0] << std::endl;

		return 0;
	}
	return shader;
}

void OpenGL::Pipeline::_linkShadersToProgram(GLuint program, const std::vector<GLuint>& shaders)
{
	for (auto shader : shaders)
	{
		glAttachShader(program, shader);
	}
	glLinkProgram(program);

	int link_result = 0;
	glGetProgramiv(program, GL_LINK_STATUS, &link_result);
	if (link_result == GL_FALSE)
	{
		int info_log_length = 0;
		glGetProgramiv(program, GL_INFO_LOG_LENGTH, &info_log_length);
		std::vector<char> program_log(info_log_length);
		glGetProgramInfoLog(program, info_log_length, NULL,
			&program_log[0]);
		std::cout << "Shader Loader : LINK ERROR" << std::endl
			<< &program_log[0] << std::endl;
		return;
	}
}

void OpenGL::Pipeline::_detachShadersFromProgram(const GLuint program, const std::vector<GLuint>& shaders)
{
	for (auto shader : shaders)
	{
		glDetachShader(program, shader);
	}
}

void OpenGL::Pipeline::_deleteShaders(const std::vector<GLuint>& shaders)
{
	for (auto shader : shaders)
	{
		glDeleteShader(shader);
	}
}


void OpenGL::Pipeline::CreateProgram(std::string programName, std::vector<std::string> filenames, bool useAsDefault)
{
	std::vector<GLuint> newShaders{};

	GLuint vertex_shader = _getShaderFromSource(GL_VERTEX_SHADER, filenames[0]);
	if (!vertex_shader) { return; }
	newShaders.push_back(vertex_shader);

	GLuint fragment_shader = _getShaderFromSource(GL_FRAGMENT_SHADER, filenames[1]);
	if (!fragment_shader) { return; }
	newShaders.push_back(fragment_shader);

	GLuint newProgram = glCreateProgram();

	_linkShadersToProgram(newProgram, newShaders);

	_detachShadersFromProgram(newProgram, newShaders);
	_deleteShaders(newShaders);
	newShaders.clear();

	_registeredPrograms.insert({ programName, newProgram });
	GameDataArchiver::Get()->StoreShader(programName, { newProgram });

	if (useAsDefault) _defaultProgram = newProgram;
}

void OpenGL::Pipeline::Draw()
{
	UseDefaultProgram();

	/*for (auto mesh : meshes)
	{
		glUseProgram(mesh->CurrentMaterial->GetProgram());

		mesh->CurrentMaterial->ApplyUniformMat4To("camMatrix", refCamera->GetView() * refCamera->GetProjection());
		mesh->CurrentMaterial->ApplyMat4Uniforms(
			{
				{"camMatrix", refCamera->GetView() * refCamera->GetProjection()},
				{"model", mesh->ModelMatrix}
			});

		glBindVertexArray(mesh->Data->VAO);
		//glDrawElements(GL_TRIANGLES, Indices.size(), GL_UNSIGNED_INT, 0);
		glDrawArrays(GL_TRIANGLES, 0, static_cast<GLsizei>(mesh->Data->Vertices.size()));
		//glDrawArraysInstanced(GL_TRIANGLES, 0, static_cast<GLsizei>(mesh->Data->Vertices.size()), 10);
		glBindVertexArray(0);
	}*/

	ICamera* cam = CameraController::Get()->GetActiveCamera();
	for (auto mprofile : meshInstances)
	{
		UseProgram(mprofile.Program);

		GLsizei count = static_cast<GLsizei>(mprofile.Count());
		Material* mat = GameDataArchiver::Get()->GetMaterial(mprofile.MaterialName);
		MeshData* mdata = GameDataArchiver::Get()->GetMesh(mprofile.MeshName);

		// Model Uniforms
		mat->ApplyUniformMat4To("camMatrix", cam->GetView() * cam->GetProjection());
		for (int i = 0; i < count; i++)
		{
			mat->ApplyUniformMat4To(("models[" + std::to_string(i) + "]").c_str(), mprofile.Models[i]);
		}

		// Texture Uniforms

		glBindVertexArray(mdata->VAO);
		glDrawElementsInstanced(GL_TRIANGLES, static_cast<GLsizei>(mdata->Indices.size()), GL_UNSIGNED_INT, 0, count);
		glDrawArraysInstanced(GL_TRIANGLES, 0, static_cast<GLsizei>(mdata->Vertices.size()), count);
		glBindVertexArray(0);
	}
}

void OpenGL::Pipeline::InjectMeshes(std::vector<Mesh*> inMeshes)
{
	meshes = inMeshes;
}

GLuint OpenGL::Pipeline::DefaultProgram() const { return _defaultProgram; }
GLuint OpenGL::Pipeline::GetProgram(const std::string name) const
{
	if (_registeredPrograms.size() == 0) return 0;
	auto found = _registeredPrograms.find(name);
	return found != _registeredPrograms.end() ? _registeredPrograms.at(name) : 0;
}

void OpenGL::Pipeline::UseDefaultProgram() const { glUseProgram(_defaultProgram); }

void OpenGL::Pipeline::UseProgram(GLuint program) const { glUseProgram(program); }
