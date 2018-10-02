#ifdef _WINDOWS
#include <GL/glew.h>
#endif
#include <SDL.h>
#include <SDL_opengl.h>
#include <SDL_image.h>

#ifdef _WINDOWS
#define RESOURCE_FOLDER ""
#else
#define RESOURCE_FOLDER "NYUCodebase.app/Contents/Resources/"
#endif

#include "ShaderProgram.h"
#include "glm/mat4x4.hpp"
#include "glm/gtc/matrix_transform.hpp"

SDL_Window* displayWindow;

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

GLuint LoadTexture(const char *filePath) {
	int w, h, comp;
	unsigned char* image = stbi_load(filePath, &w, &h, &comp, STBI_rgb_alpha);
	if (image == NULL) {
		std::cout << "Unable to load image. Make sure the path is correct\n";
		assert(false);
	}
	GLuint retTexture;
	glGenTextures(1, &retTexture);
	glBindTexture(GL_TEXTURE_2D, retTexture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w, h, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	stbi_image_free(image);
	return retTexture;
}

int main(int argc, char *argv[])
{
    SDL_Init(SDL_INIT_VIDEO);
    displayWindow = SDL_CreateWindow("My Game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 360, SDL_WINDOW_OPENGL);
    SDL_GLContext context = SDL_GL_CreateContext(displayWindow);
    SDL_GL_MakeCurrent(displayWindow, context);

#ifdef _WINDOWS
    glewInit();
#endif

	
	glViewport(0, 0, 640, 360); // leave
	ShaderProgram program; // leave
	program.Load(RESOURCE_FOLDER"vertex.glsl", RESOURCE_FOLDER"fragment.glsl"); // leave


	GLuint texture = LoadTexture(RESOURCE_FOLDER"glow3.png");

	glm::mat4 projectionMatrix1 = glm::mat4(1.0f);
	glm::mat4 modelMatrix1 = glm::mat4(1.0f);
	glm::mat4 viewMatrix1 = glm::mat4(1.0f);
	projectionMatrix1 = glm::ortho(-1.777f, 1.777f, -1.0f, 1.0f, -1.0f, 1.0f);

	glm::mat4 projectionMatrix2 = glm::mat4(1.0f);
	glm::mat4 modelMatrix2 = glm::mat4(1.0f);
	glm::mat4 viewMatrix2 = glm::mat4(1.0f);
	projectionMatrix2 = glm::ortho(-1.777f, 1.777f, -1.0f, 1.0f, -1.0f, 1.0f);

	glm::mat4 projectionMatrix3 = glm::mat4(1.0f);
	glm::mat4 modelMatrix3 = glm::mat4(1.0f);
	glm::mat4 viewMatrix3 = glm::mat4(1.0f);
	projectionMatrix3 = glm::ortho(-1.777f, 1.777f, -1.0f, 1.0f, -1.0f, 1.0f);

	glUseProgram(program.programID); // leave


    SDL_Event event;
    bool done = false;
    while (!done) 
	{

		
		glClear(GL_COLOR_BUFFER_BIT); // leave
		program.SetModelMatrix(modelMatrix1);
		program.SetProjectionMatrix(projectionMatrix1);
		program.SetViewMatrix(viewMatrix1);
		glBindTexture(GL_TEXTURE_2D, texture);
		float vertices1[] = { 0.5f, -0.5f, 0.0f, 0.5f, -0.5f, -0.5f };
		glVertexAttribPointer(program.positionAttribute, 2, GL_FLOAT, false, 0, vertices1);
		glEnableVertexAttribArray(program.positionAttribute);
		float texCoords[] = { 0.5f, -0.5f, 0.0f, 0.5f, -0.5f, -0.5f };
		glVertexAttribPointer(program.texCoordAttribute, 2, GL_FLOAT, false, 0, texCoords);
		glEnableVertexAttribArray(program.texCoordAttribute);
		glDrawArrays(GL_TRIANGLES, 0, 6);
		glDisableVertexAttribArray(program.positionAttribute);
		glDisableVertexAttribArray(program.texCoordAttribute);



		float angle = 45.0f * (3.1415926f / 180.0f);
		modelMatrix2 = glm::rotate(modelMatrix2, angle, glm::vec3(0.0f, 0.0f, 1.0f));

		program.SetModelMatrix(modelMatrix2);
		program.SetProjectionMatrix(projectionMatrix2);
		program.SetViewMatrix(viewMatrix2);
		float vertices2[] = { 1.0f, 0.0f, 1.0f, -0.5f, 1.5f, 0.0f };
		glVertexAttribPointer(program.positionAttribute, 2, GL_FLOAT, false, 0, vertices2);
		glEnableVertexAttribArray(program.positionAttribute);
		glDrawArrays(GL_TRIANGLES, 0, 3);
		glDisableVertexAttribArray(program.positionAttribute);

		program.SetModelMatrix(modelMatrix3);
		program.SetProjectionMatrix(projectionMatrix3);
		program.SetViewMatrix(viewMatrix3);
		float vertices3[] = { -1.0f, 0.0f, -1.0f, -0.5f, -1.5f, 0.0f };
		glVertexAttribPointer(program.positionAttribute, 2, GL_FLOAT, false, 0, vertices3);
		glEnableVertexAttribArray(program.positionAttribute);
		glDrawArrays(GL_TRIANGLES, 0, 3);
		glDisableVertexAttribArray(program.positionAttribute);

		SDL_GL_SwapWindow(displayWindow); // leave


        while (SDL_PollEvent(&event)) 
		{
            if (event.type == SDL_QUIT || event.type == SDL_WINDOWEVENT_CLOSE)
                done = true;
        }
        glClear(GL_COLOR_BUFFER_BIT);
    }
    
    SDL_Quit();
    return 0;
}
