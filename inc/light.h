#ifndef LIGHT_H
#define LIGHT_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stb/stb_image.h>

#include "camera.h"
#include "shader.h"
#include "model.h"
#include "transform3d.h"

/*
	glm::vec4 white(1.0f,1.0f,1.0f,1.0f), emy_barva((float)255/255, (float)150/255, (float)250/255, 1.0f);


	//create light with white color - light will automaticly append and create from light shader program
	Light someLight(shaderProgram, white, glm::vec3(0.5f, 0.5f, 0.5f));

*/

#define LIGHT_TYPE_NOLIGHT 0
#define LIGHT_TYPE_POINT 1
#define LIGHT_TYPE_SPOT 2
#define LIGHT_TYPE_DIRECT 3

#define GRADIENT_NOGRADIENT 0
#define GRADIENT_NORMAL 1
#define GRADIENT_ANIMATED 2

struct LightSettings{
	//for spot light:
	float outerCone = 0.90f;//outercone angle - cos value
 	float innerCone = 0.95f;//innercone angle - cos value

	//distance for point light
 	float distance = 5.0f;

	//for all lights - light function parametres
 	float a = 1.0f;//pr 1    nebo 3
 	float b = 0.04f;//pr 0,04 nebo 0,7
};


class Light{
public:
	
    Light(){}
	Light(Shader lightShader, glm::vec3 lightColor, glm::vec3 lightEndColor, glm::vec3 lightPos, int type, int gradient, LightSettings set){
		glm::mat4 lightModel = glm::mat4(1.0f);
		lightModel = glm::translate(lightModel, lightPos);
		lightShader.Activate();
		glUniform1i(glGetUniformLocation(lightShader.ID, "colorGrad"), gradient);
		glUniform1i(glGetUniformLocation(lightShader.ID, "lightType"), type);
		glUniform1f(glGetUniformLocation(lightShader.ID, "outerCone"), set.outerCone);
		glUniform1f(glGetUniformLocation(lightShader.ID, "innerCone"), set.innerCone);
		glUniform1f(glGetUniformLocation(lightShader.ID, "distance"), set.distance);
		glUniform1f(glGetUniformLocation(lightShader.ID, "a"), set.a);
		glUniform1f(glGetUniformLocation(lightShader.ID, "b"), set.b);
		glUniform3f(glGetUniformLocation(lightShader.ID, "lightColor"), lightColor.x, lightColor.y, lightColor.z);
		glUniform3f(glGetUniformLocation(lightShader.ID, "lightEndColor"), lightEndColor.x, lightEndColor.y, lightEndColor.z);
		glUniform3f(glGetUniformLocation(lightShader.ID, "lightPos"), lightPos.x, lightPos.y, lightPos.z);
	}

	void recreate(Shader lightShader, glm::vec3 lightColor, glm::vec3 lightEndColor, glm::vec3 lightPos, int type, int gradient, LightSettings set){
		glm::mat4 lightModel = glm::mat4(1.0f);
		lightModel = glm::translate(lightModel, lightPos);
		lightShader.Activate();
		glUniform1i(glGetUniformLocation(lightShader.ID, "colorGrad"), gradient);
		glUniform1i(glGetUniformLocation(lightShader.ID, "lightType"), type);
		glUniform1f(glGetUniformLocation(lightShader.ID, "outerCone"), set.outerCone);
		glUniform1f(glGetUniformLocation(lightShader.ID, "innerCone"), set.innerCone);
		glUniform1f(glGetUniformLocation(lightShader.ID, "distance"), set.distance);
		glUniform1f(glGetUniformLocation(lightShader.ID, "a"), set.a);
		glUniform1f(glGetUniformLocation(lightShader.ID, "b"), set.b);
		glUniform3f(glGetUniformLocation(lightShader.ID, "lightColor"), lightColor.x, lightColor.y, lightColor.z);
		glUniform3f(glGetUniformLocation(lightShader.ID, "lightEndColor"), lightEndColor.x, lightEndColor.y, lightEndColor.z);
		glUniform3f(glGetUniformLocation(lightShader.ID, "lightPos"), lightPos.x, lightPos.y, lightPos.z);
	}

};


glm::vec3 col2vec(int r, int g, int b);

glm::vec3 fcol2vec(float col[4]);

glm::fvec3 col2vecf(int r, int g, int b);

glm::fvec3 fcol2vecf(float col[4]);

glm::fvec4 genFcol4(int r, int g, int b, int a);
glm::fvec3 genFcol3(int r, int g, int b);

glm::fvec4 genFcol4(float col[4]);

//float * vec3float4(glm::vec3 c);
#endif