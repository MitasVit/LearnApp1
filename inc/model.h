#ifndef MODEL_CLASS_H
#define MODEL_CLASS_H

#include<json/json.hpp>
#include"mesh.h"

using json = nlohmann::json;

class Model
{
public:
	// Loads in a model from a file and stores tha information in 'data', 'JSON', and 'file'
	Model(const char* file);
	Model(std::vector<Mesh> _meshes,std::vector<glm::mat4> mats);

	void Draw(Shader& shader, Camera& camera);
		void DrawF(Shader& shader, Camera& camera);
				void DrawF(Shader& shader, Camera& camera, Texture& tex);
	void Draw(Shader& shader, Camera& camera, Texture& _texture);
		void DrawColF(Shader& shader, Camera& camera, glm::fvec3 _color, float alpha = 1.0f);
	void DrawSpec(Shader& shader, Camera& camera);

	void DrawWithOutline(Shader& shader, Camera& camera, Texture& texture, Model& outlinemodel, Shader& outliningshader);

	void DrawWithOutline(Shader& shader, Camera& camera, Model& outlinemodel, Shader& outliningshader);

	void SetMatricesMeshes(std::vector<glm::mat4> _matricesMeshes);
	void SetMatricesMeshesF(std::vector<glm::fmat4> _matricesMeshes);
	int GetNumMatricesMeshes();

	std::vector<Mesh> GetMeshes();

private:
	// Variables for easy access
	const char* file;
	std::vector<unsigned char> data;
	json JSON;

	// All the meshes and transformations
	std::vector<Mesh> meshes;
	std::vector<glm::vec3> translationsMeshes;
	std::vector<glm::quat> rotationsMeshes;
	std::vector<glm::vec3> scalesMeshes;
	std::vector<glm::mat4> matricesMeshes, matricesMeshesf;

	// Prevents textures from being loaded twice
	std::vector<std::string> loadedTexName;
	std::vector<Texture> loadedTex;

	// Loads a single mesh by its index
	void loadMesh(unsigned int indMesh);

	// Traverses a node recursively, so it essentially traverses all connected nodes
	void traverseNode(unsigned int nextNode, glm::mat4 matrix = glm::mat4(1.0f));

	// Gets the binary data from a file
	std::vector<unsigned char> getData();
	// Interprets the binary data into floats, indices, and textures
	std::vector<float> getFloats(json accessor);
	std::vector<GLuint> getIndices(json accessor);
	std::vector<Texture> getTextures();

	// Assembles all the floats into vertices
	std::vector<Vertex> assembleVertices
	(
		std::vector<glm::vec3> positions, 
		std::vector<glm::vec3> normals, 
		std::vector<glm::vec2> texUVs
	);

	// Helps with the assembly from above by grouping floats
	std::vector<glm::vec2> groupFloatsVec2(std::vector<float> floatVec);
	std::vector<glm::vec3> groupFloatsVec3(std::vector<float> floatVec);
	std::vector<glm::vec4> groupFloatsVec4(std::vector<float> floatVec);
};

/*
#include <assimp/cimport.h>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
void color4_to_float4(const C_STRUCT aiColor4D *c, float f[4]);
void set_float4(float f[4], float a, float b, float c, float d);

#define aisgl_min(x,y) (x<y?x:y)
#define aisgl_max(x,y) (y>x?y:x)


class ModelA{
public:
	ModelA(std::string path);
	void Draw();
	void Destroy();

private:
	const C_STRUCT aiScene* scene = NULL;
	GLuint scene_list = 0;
	C_STRUCT aiVector3D scene_min, scene_max, scene_center;
	float angle = 0.f;

	void apply_material(const C_STRUCT aiMaterial *mtl);
	void recursive_render (const C_STRUCT aiScene *sc, const C_STRUCT aiNode* nd);
	void get_bounding_box(C_STRUCT aiVector3D* min, C_STRUCT aiVector3D* max);
	void get_bounding_box_for_node (const C_STRUCT aiNode* nd, C_STRUCT aiVector3D* min, C_STRUCT aiVector3D* max,C_STRUCT aiMatrix4x4* trafo);
};
*/
#endif