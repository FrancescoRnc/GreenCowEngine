#include "Pipeline.h"

void OpenGL::Pipeline::CreateProgram(std::string shaders_name)
{
	auto fullVSpath = "Assets/Shaders/v_" + shaders_name + ".glsl";
	auto fullFSpath = "Assets/Shaders/f_" + shaders_name + ".glsl";

	auto VScontent = Helpers::FileReader::GetFileSource(fullVSpath);
	GLint vssize = static_cast<GLint>(VScontent.size);
	auto vertex_shader = glCreateShader(GL_VERTEX_SHADER);
	std::string vssource = reinterpret_cast<char*>(VScontent.source->data());
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
		std::cout << "Error compiling vertex shader: " << shaders_name << std::endl
			<< &shader_log[0] << std::endl;

		return;
	}


	auto FScontent = Helpers::FileReader::GetFileSource(fullFSpath);
	GLint fssize = static_cast<GLint>(FScontent.size);
	auto fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
	std::string fssource = reinterpret_cast<char*>(FScontent.source->data());
	auto fssource_c = fssource.c_str();
	glShaderSource(fragment_shader, 1, &fssource_c, &fssize);
	glCompileShader(fragment_shader);

	compile_result = 0;
	glGetShaderiv(fragment_shader, GL_COMPILE_STATUS, &compile_result);
	if (compile_result == GL_FALSE)
	{
		int info_log_length = 0;
		glGetShaderiv(fragment_shader, GL_INFO_LOG_LENGTH, &info_log_length);
		std::vector<char> shader_log(info_log_length);
		glGetShaderInfoLog(fragment_shader, info_log_length, NULL, &shader_log[0]);
		std::cout << "Error compiling fragment shader: " << shaders_name << std::endl
			<< &shader_log[0] << std::endl;

		return;
	}


	Program = glCreateProgram();

	glAttachShader(Program, vertex_shader);
	glAttachShader(Program, fragment_shader);
	glLinkProgram(Program);

	int link_result = 0;
	glGetProgramiv(Program, GL_LINK_STATUS, &link_result);
	if (link_result == GL_FALSE)
	{
		int info_log_length = 0;
		glGetProgramiv(Program, GL_INFO_LOG_LENGTH, &info_log_length);
		std::vector<char> program_log(info_log_length);
		glGetProgramInfoLog(Program, info_log_length, NULL,
			&program_log[0]);
		std::cout << "Shader Loader : LINK ERROR" << std::endl
			<< &program_log[0] << std::endl;
		return;
	}

	glDetachShader(Program, vertex_shader);
	glDetachShader(Program, fragment_shader);

	glDeleteShader(vertex_shader);
	glDeleteShader(fragment_shader);
}

void OpenGL::Pipeline::Draw()
{

}