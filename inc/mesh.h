#ifndef MESH_CLASS_H
#define MESH_CLASS_H

#include<string>
#include <vector>

#include"VAO.h"
#include"EBO.h"
#include"camera.h"
#include"texture.h"


class Mesh
{
public:
	std::vector <Vertex> vertices;
	std::vector <GLuint> indices;
	std::vector <Texture> textures;
	// Store VAO in public so it can be used in the Draw function
	VAO vao;

	// Initializes the mesh
	Mesh(std::vector <Vertex>& vertices, std::vector <GLuint>& indices, std::vector <Texture>& textures);

	// Draws the mesh
	void Draw
	(
		Shader& shader, 
		Camera& camera,
		glm::mat4 matrix = glm::mat4(1.0f),
		glm::vec3 translation = glm::vec3(0.0f, 0.0f, 0.0f),
		glm::quat rotation = glm::quat(1.0f, 0.0f, 0.0f, 0.0f),
		glm::vec3 scale = glm::vec3(1.0f, 1.0f, 1.0f)
	);
	void DrawF
	(
		Shader& shader, 
		Camera& camera,
		glm::fmat4 matrix = glm::fmat4(1.0f),
		glm::vec3 translation = glm::vec3(0.0f, 0.0f, 0.0f),
		glm::quat rotation = glm::quat(1.0f, 0.0f, 0.0f, 0.0f),
		glm::vec3 scale = glm::vec3(1.0f, 1.0f, 1.0f)
	);
	void DrawF
	(
		Shader& shader, 
		Camera& camera,
		Texture& tex,
		glm::fmat4 matrix = glm::fmat4(1.0f),
		glm::vec3 translation = glm::vec3(0.0f, 0.0f, 0.0f),
		glm::quat rotation = glm::quat(1.0f, 0.0f, 0.0f, 0.0f),
		glm::vec3 scale = glm::vec3(1.0f, 1.0f, 1.0f)
	);
	//draw the mesh with applied texture from texture_path
	void Draw
		(
		Shader& shader, 
		Camera& camera,
		Texture& _texture,
		glm::mat4 matrix = glm::mat4(1.0f),
		glm::vec3 translation = glm::vec3(0.0f, 0.0f, 0.0f),
		glm::quat rotation = glm::quat(1.0f, 0.0f, 0.0f, 0.0f),
		glm::vec3 scale = glm::vec3(1.0f, 1.0f, 1.0f)
	);
	void DrawSpec
		(
		Shader& shader, 
		Camera& camera,
		glm::mat4 matrix = glm::mat4(1.0f),
		glm::vec3 translation = glm::vec3(0.0f, 0.0f, 0.0f),
		glm::quat rotation = glm::quat(1.0f, 0.0f, 0.0f, 0.0f),
		glm::vec3 scale = glm::vec3(1.0f, 1.0f, 1.0f)
	);
	void DrawColF(
		Shader& shader, 
		Camera& camera,
		glm::fvec3 color,
		float alpha =1.0f,
		glm::mat4 matrix = glm::mat4(1.0f),
		glm::vec3 translation = glm::vec3(0.0f, 0.0f, 0.0f),
		glm::quat rotation = glm::quat(1.0f, 0.0f, 0.0f, 0.0f),
		glm::vec3 scale = glm::vec3(1.0f, 1.0f, 1.0f)
		);

};

#include <assimp/Importer.hpp>	//OO version Header!
#include <assimp/postprocess.h>
#include <assimp/scene.h>
#include <assimp/DefaultLogger.hpp>
#include <assimp/LogStream.hpp>

//struct for vertex with uv
struct Vertex3dUVNormal
{

    glm::vec3 m_position;
    glm::vec2 m_texCoord;
    glm::vec3 m_normal;

    // Makes a 2d vertex with uc and color data.
    Vertex3dUVNormal(glm::vec3 position, glm::vec2 texCoord, glm::vec3 normal) {
        m_position = position;
        m_texCoord = texCoord;
        m_normal = normal;
    }

	Vertex3dUVNormal() {}
};

class MeshA {


private:
	// Vectors of shape information
	std::vector<Vertex3dUVNormal> m_vertices;
	std::vector<unsigned short> m_indices;

	// Buffered shape info
	GLuint m_vertexBuffer;
	GLuint m_indexBuffer;


public:
	// Constructor for a shape, takes a vector for vertices and indices
	MeshA(std::vector<Vertex3dUVNormal> vertices, std::vector<unsigned short> indices);

    // Constructor for a mesh. reads in an obj file.
    MeshA(std::string filePath);

	// Shape destructor to clean up buffers
	~MeshA();


	// Draws the shape using a given world matrix
	void Draw();
};

#endif