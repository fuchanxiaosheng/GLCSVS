#define GLEW_STATIC
#define FREEGLUT_STATIC

#include <GL/glew.h>
#include <GL/glut.h>
#include <GL/freeglut.h>
#include <spdlog/spdlog.h>


enum VAO_IDs { Triangles, NumVAOs};
enum Buffer_IDs { ArrayBuffer, NumBuffers};
enum Attrib_IDs { vPosition = 0};

GLuint VAOs[NumVAOs];
GLuint Buffers[NumBuffers];

const GLuint NumVertices = 6;


void init(void)
{
	glGenVertexArrays(NumVAOs, VAOs);
	glBindVertexArray(VAOs[Triangles]);
	GLfloat vertices[NumVertices][2] = {
		{-0.90, -0.90},
		{0.85, -0.90},
		{-0.90, 0.85},
		{0.90, -0.85},
		{0.90, 0.90},
		{-0.85, 0.90}
	};
	glGenBuffers(NumBuffers, Buffers);
	glBindBuffer(GL_ARRAY_BUFFER, Buffers[ArrayBuffer]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	char* vertexShaderSource =
		R"-(
	#version 430 core
	layout(location = 0) in vec4 vPosition;
	void main()
	{
		gl_Position = vPosition;
	}
	)-";

	unsigned int vertexShader;
	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	glCompileShader(vertexShader);

	int success;
	char infoLog[512];
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
		spdlog::error("error::shader::vertex::compilation_failed");
		spdlog::info("================");
		spdlog::info(infoLog);
		spdlog::info("================");
	}

	char* fragmentShaderSource =
		R"-(
		#version 430 core
		out vec4 fColor;

		void main()
		{
			fColor = vec4(0.0, 0.0, 1.0, 1.0);
		}
	)-";
	unsigned int fragmentShader;
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentShader);
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
		spdlog::error("error::shader::fragment::compilation_failed");
		spdlog::info("================");
		spdlog::info(infoLog);
		spdlog::info("================");
	}

	GLuint shaderProgram;
	shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);
	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
	if (!success)
	{
		glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
		spdlog::error("error::shaderProgram::Link_failed");
		spdlog::info("================");
		spdlog::info(infoLog);
		spdlog::info("================");
	}
	glUseProgram(shaderProgram);
	glVertexAttribPointer(vPosition, 2, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(vPosition);
}

void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT);
	glBindVertexArray(VAOs[Triangles]);
	glDrawArrays(GL_TRIANGLES, 0, NumVertices);
	glFlush();
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA);
	glutInitWindowSize(512, 512);
	glutInitContextVersion(4, 3);
	glutInitContextProfile(GLUT_CORE_PROFILE);
	glutCreateWindow(argv[0]);

	if (glewInit())
	{
		spdlog::info("Unable to initialize GLEW");
		return -1;
	}

	init();
	glutDisplayFunc(display);
	glutMainLoop();
}