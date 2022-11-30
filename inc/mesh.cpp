#include "mesh.h"

Mesh::Mesh(std::vector <Vertex>& vertices, std::vector <GLuint>& indices, std::vector <Texture>& textures)
{
	Mesh::vertices = vertices;
	Mesh::indices = indices;
	Mesh::textures = textures;

	vao.Bind();
	// Generates Vertex Buffer Object and links it to vertices
	VBO vbo(vertices);
	// Generates Element Buffer Object and links it to indices
	EBO ebo(indices);
	// Links VBO attributes such as coordinates and colors to VAO
	vao.LinkAttrib(vbo, 0, 3, GL_FLOAT, sizeof(Vertex), (void*)0);
	vao.LinkAttrib(vbo, 1, 3, GL_FLOAT, sizeof(Vertex), (void*)(3 * sizeof(float)));
	vao.LinkAttrib(vbo, 2, 3, GL_FLOAT, sizeof(Vertex), (void*)(6 * sizeof(float)));
	vao.LinkAttrib(vbo, 3, 2, GL_FLOAT, sizeof(Vertex), (void*)(9 * sizeof(float)));
	// Unbind all to prevent accidentally modifying them
	vao.Unbind();
	vbo.Unbind();
	ebo.Unbind();
}

void Mesh::DrawF
(
	Shader& shader, 
	Camera& camera,
	glm::fmat4 matrix,
	glm::vec3 translation, 
	glm::quat rotation, 
	glm::vec3 scale
)
{
	// Bind shader to be able to access uniforms
	shader.Activate();
	vao.Bind();

	// Keep track of how many of each type of textures we have
	unsigned int numDiffuse = 0;
	unsigned int numSpecular = 0;

	for (unsigned int i = 0; i < textures.size(); i++)
	{
		std::string num;
		std::string type = textures[i].type;
		if (type == "diffuse")
		{
			num = std::to_string(numDiffuse++);
		}
		else if (type == "specular")
		{
			num = std::to_string(numSpecular++);
		}
		textures[i].texUnit(shader, (type + num).c_str(), i);
		textures[i].Bind();
	}
	// Take care of the camera Matrix
	glUniform3f(glGetUniformLocation(shader.ID, "camPos"), camera.Position.x, camera.Position.y, camera.Position.z);
	camera.Matrix(shader, "camMatrix");

	// Initialize matrices
	glm::fmat4 trans = glm::fmat4(1.0f);
	glm::fmat4 rot = glm::fmat4(1.0f);
	glm::fmat4 sca = glm::fmat4(1.0f);

	// Transform the matrices to their correct form
	trans = glm::translate(trans, translation);
	rot = glm::mat4_cast(rotation);
	sca = glm::scale(sca, scale);

	// Push the matrices to the vertex shader
	glUniformMatrix4fv(glGetUniformLocation(shader.ID, "translation"), 1, GL_FALSE, glm::value_ptr(trans));
	glUniformMatrix4fv(glGetUniformLocation(shader.ID, "rotation"), 1, GL_FALSE, glm::value_ptr(rot));
	glUniformMatrix4fv(glGetUniformLocation(shader.ID, "scale"), 1, GL_FALSE, glm::value_ptr(sca));
	glUniformMatrix4fv(glGetUniformLocation(shader.ID, "model"), 1, GL_FALSE, glm::value_ptr(matrix));

	// Draw the actual mesh
	glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
}

void Mesh::DrawColF(
		Shader& shader, 
		Camera& camera,
		glm::fvec3 color,
		float alpha,
		glm::mat4 matrix ,
		glm::vec3 translation ,
		glm::quat rotation,
		glm::vec3 scale
		){

	shader.Activate();
	vao.Bind();

	// Take care of the camera Matrix
	glUniform3f(glGetUniformLocation(shader.ID, "camPos"), camera.Position.x, camera.Position.y, camera.Position.z);
	camera.Matrix(shader, "camMatrix");
	
	glUniform1i(glGetUniformLocation(shader.ID, "colored"),1);
	glUniform4f(glGetUniformLocation(shader.ID, "texcol"), color.x, color.y, color.z, alpha);

	// Initialize matrices
	glm::fmat4 trans = glm::fmat4(1.0f);
	glm::fmat4 rot = glm::fmat4(1.0f);
	glm::fmat4 sca = glm::fmat4(1.0f);

	// Transform the matrices to their correct form
	trans = glm::translate(trans, translation);
	rot = glm::mat4_cast(rotation);
	sca = glm::scale(sca, scale);

	// Push the matrices to the vertex shader
	glUniformMatrix4fv(glGetUniformLocation(shader.ID, "translation"), 1, GL_FALSE, glm::value_ptr(trans));
	glUniformMatrix4fv(glGetUniformLocation(shader.ID, "rotation"), 1, GL_FALSE, glm::value_ptr(rot));
	glUniformMatrix4fv(glGetUniformLocation(shader.ID, "scale"), 1, GL_FALSE, glm::value_ptr(sca));
	glUniformMatrix4fv(glGetUniformLocation(shader.ID, "model"), 1, GL_FALSE, glm::value_ptr(matrix));
	glUniform3i(glGetUniformLocation(shader.ID, "color"), color.x, color.y, color.z);
	// Draw the actual mesh
	glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
		glUniform1i(glGetUniformLocation(shader.ID, "colored"),0);
}
void Mesh::DrawF
(
	Shader& shader, 
	Camera& camera,
	Texture& tex,
	glm::fmat4 matrix,
	glm::vec3 translation, 
	glm::quat rotation, 
	glm::vec3 scale
)
{
	// Bind shader to be able to access uniforms
	shader.Activate();
	vao.Bind();

	// Keep track of how many of each type of textures we have
	unsigned int numDiffuse = 0;
	unsigned int numSpecular = 0;
	tex.Bind();
	// Take care of the camera Matrix
	glUniform3f(glGetUniformLocation(shader.ID, "camPos"), camera.Position.x, camera.Position.y, camera.Position.z);
	camera.Matrix(shader, "camMatrix");

	// Initialize matrices
	glm::fmat4 trans = glm::fmat4(1.0f);
	glm::fmat4 rot = glm::fmat4(1.0f);
	glm::fmat4 sca = glm::fmat4(1.0f);

	// Transform the matrices to their correct form
	trans = glm::translate(trans, translation);
	rot = glm::mat4_cast(rotation);
	sca = glm::scale(sca, scale);

	// Push the matrices to the vertex shader
	glUniformMatrix4fv(glGetUniformLocation(shader.ID, "translation"), 1, GL_FALSE, glm::value_ptr(trans));
	glUniformMatrix4fv(glGetUniformLocation(shader.ID, "rotation"), 1, GL_FALSE, glm::value_ptr(rot));
	glUniformMatrix4fv(glGetUniformLocation(shader.ID, "scale"), 1, GL_FALSE, glm::value_ptr(sca));
	glUniformMatrix4fv(glGetUniformLocation(shader.ID, "model"), 1, GL_FALSE, glm::value_ptr(matrix));

	// Draw the actual mesh
	glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
}


void Mesh::Draw
(
	Shader& shader, 
	Camera& camera,
	glm::mat4 matrix,
	glm::vec3 translation, 
	glm::quat rotation, 
	glm::vec3 scale
)
{
	// Bind shader to be able to access uniforms
	shader.Activate();
	vao.Bind();

	// Keep track of how many of each type of textures we have
	unsigned int numDiffuse = 0;
	unsigned int numSpecular = 0;

	for (unsigned int i = 0; i < textures.size(); i++)
	{
		std::string num;
		std::string type = textures[i].type;
		if (type == "diffuse")
		{
			num = std::to_string(numDiffuse++);
		}
		else if (type == "specular")
		{
			num = std::to_string(numSpecular++);
		}
		textures[i].texUnit(shader, (type + num).c_str(), i);
		textures[i].Bind();
	}
	// Take care of the camera Matrix
	glUniform3f(glGetUniformLocation(shader.ID, "camPos"), camera.Position.x, camera.Position.y, camera.Position.z);
	camera.Matrix(shader, "camMatrix");

	// Initialize matrices
	glm::mat4 trans = glm::mat4(1.0f);
	glm::mat4 rot = glm::mat4(1.0f);
	glm::mat4 sca = glm::mat4(1.0f);

	// Transform the matrices to their correct form
	trans = glm::translate(trans, translation);
	rot = glm::mat4_cast(rotation);
	sca = glm::scale(sca, scale);

	// Push the matrices to the vertex shader
	glUniformMatrix4fv(glGetUniformLocation(shader.ID, "translation"), 1, GL_FALSE, glm::value_ptr(trans));
	glUniformMatrix4fv(glGetUniformLocation(shader.ID, "rotation"), 1, GL_FALSE, glm::value_ptr(rot));
	glUniformMatrix4fv(glGetUniformLocation(shader.ID, "scale"), 1, GL_FALSE, glm::value_ptr(sca));
	glUniformMatrix4fv(glGetUniformLocation(shader.ID, "model"), 1, GL_FALSE, glm::value_ptr(matrix));

	// Draw the actual mesh
	glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
}

void Mesh::Draw
(
	Shader& shader, 
	Camera& camera,
	Texture& _texture,
	glm::mat4 matrix,
	glm::vec3 translation, 
	glm::quat rotation, 
	glm::vec3 scale
)
{
	// Bind shader to be able to access uniforms
	shader.Activate();
	vao.Bind();

	// Keep track of how many of each type of textures we have
	
	// Take care of the camera Matrix
	glUniform3f(glGetUniformLocation(shader.ID, "camPos"), camera.Position.x, camera.Position.y, camera.Position.z);
	camera.Matrix(shader, "camMatrix");

	_texture.Bind();
	// Initialize matrices
	glm::mat4 trans = glm::mat4(1.0f);
	glm::mat4 rot = glm::mat4(1.0f);
	glm::mat4 sca = glm::mat4(1.0f);

	// Transform the matrices to their correct form
	trans = glm::translate(trans, translation);
	rot = glm::mat4_cast(rotation);
	sca = glm::scale(sca, scale);

	// Push the matrices to the vertex shader
	glUniformMatrix4fv(glGetUniformLocation(shader.ID, "translation"), 1, GL_FALSE, glm::value_ptr(trans));
	glUniformMatrix4fv(glGetUniformLocation(shader.ID, "rotation"), 1, GL_FALSE, glm::value_ptr(rot));
	glUniformMatrix4fv(glGetUniformLocation(shader.ID, "scale"), 1, GL_FALSE, glm::value_ptr(sca));
	glUniformMatrix4fv(glGetUniformLocation(shader.ID, "model"), 1, GL_FALSE, glm::value_ptr(matrix));

	// Draw the actual mesh
	glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
}

void Mesh::DrawSpec
(
	Shader& shader, 
	Camera& camera,
	glm::mat4 matrix,
	glm::vec3 translation, 
	glm::quat rotation, 
	glm::vec3 scale
)
{
	// Bind shader to be able to access uniforms
	shader.Activate();
	vao.Bind();

	// Take care of the camera Matrix
	glUniform3f(glGetUniformLocation(shader.ID, "camPos"), camera.Position.x, camera.Position.y, camera.Position.z);
	camera.Matrix(shader, "camMatrix");

	// Initialize matrices
	glm::mat4 trans = glm::mat4(1.0f);
	glm::mat4 rot = glm::mat4(1.0f);
	glm::mat4 sca = glm::mat4(1.0f);

	// Transform the matrices to their correct form
	trans = glm::translate(trans, translation);
	rot = glm::mat4_cast(rotation);
	sca = glm::scale(sca, scale);

	// Push the matrices to the vertex shader
	glUniformMatrix4fv(glGetUniformLocation(shader.ID, "translation"), 1, GL_FALSE, glm::value_ptr(trans));
	glUniformMatrix4fv(glGetUniformLocation(shader.ID, "rotation"), 1, GL_FALSE, glm::value_ptr(rot));
	glUniformMatrix4fv(glGetUniformLocation(shader.ID, "scale"), 1, GL_FALSE, glm::value_ptr(sca));
	glUniformMatrix4fv(glGetUniformLocation(shader.ID, "model"), 1, GL_FALSE, glm::value_ptr(matrix));

	// Draw the actual mesh
	glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
}

/*----------------------------------------------------------------------**/
//MeshA

MeshA::MeshA(std::vector<Vertex3dUVNormal> vertices, std::vector<unsigned short> indices)
{
	m_vertices = vertices;
	m_indices = indices;
	// Create the shape by setting up buffers

	// Set up vertex buffer
	glGenBuffers(1, &m_vertexBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, m_vertices.size() * sizeof(Vertex3dUVNormal), &m_vertices[0], GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	// Set up index buffer
	glGenBuffers(1, &m_indexBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, m_indexBuffer);
	glBufferData(GL_ARRAY_BUFFER, m_indices.size() * sizeof(unsigned int), &m_indices[0], GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

MeshA::MeshA(std::string filePath)
{
    // before we do anything, lets first check if the file even exists:
    std::ifstream file(filePath);

    if (!file.good())
    {
        // If we encounter an error, print a message and return.
        std::cout << "Can't read file: " << filePath << std::endl;
        return;
    }

	// create variables
	Assimp::Importer importer;
	const aiScene* scene = NULL;
	unsigned int n = 0, t;
	
	// Load the file into a "scene"
	for(int k = 0; k < 1; k++)
	scene = importer.ReadFile(filePath, aiProcessPreset_TargetRealtime_Quality | aiProcess_PreTransformVertices);

	// only one mesh in the file, because its a simple tutorial
	const struct aiMesh* mesh = scene->mMeshes[0];

	// make the vertex buffer
	for (t = 0; t < mesh->mNumVertices; ++t)
	{
		// make a vertex
		Vertex3dUVNormal v;
		
		// copy from arrays to each vertex
		memcpy(&v.m_position, 	&mesh->mVertices[t], 		sizeof(glm::vec3));
		memcpy(&v.m_normal, 	&mesh->mNormals[t], 		sizeof(glm::vec3));
		memcpy(&v.m_texCoord, 	&mesh->mTextureCoords[0][t],sizeof(glm::vec2));
		
		// add to vertex buffer
		m_vertices.push_back(v);
	}

	// make the index buffer
	for (t = 0; t < mesh->mNumFaces; ++t) 
	{
		const struct aiFace* face = &mesh->mFaces[t];
	
		 // add the first 3 indices of the face to our index collection to form a triangle
		 for (int i = 0; i < 3; i++)
		 {
			 m_indices.push_back(face->mIndices[i]);
		 }
		 
		 // the face is a quad, add 3 more vertices to form a triangle
		 if (face->mNumIndices == 4)
		 {
			 m_indices.push_back(face->mIndices[0]);
			 m_indices.push_back(face->mIndices[2]);
			 m_indices.push_back(face->mIndices[3]);
		 }
	}

	printf("%d %d\n", (int)m_vertices.size(), (int)m_indices.size());

    // create buffers for opengl just like normal

	// Set up vertex buffer
    glGenBuffers(1, &m_vertexBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer);
    glBufferData(GL_ARRAY_BUFFER, m_vertices.size() * sizeof(Vertex3dUVNormal), &m_vertices[0], GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    // Set up index buffer
    glGenBuffers(1, &m_indexBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, m_indexBuffer);
    glBufferData(GL_ARRAY_BUFFER, m_indices.size() * sizeof(unsigned short), &m_indices[0], GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

MeshA::~MeshA()
{
	// Clear buffers for the shape object when done using them.
	glDeleteBuffers(1, &m_vertexBuffer);
	glDeleteBuffers(1, &m_indexBuffer);
}

// This macro will help us make the attribute pointers
// position, size, type, struct, element
#define SetupAttribute(index, size, type, structure, element) \
	glVertexAttribPointer(index, size, type, 0, sizeof(structure), (void*)offsetof(structure, element)); \

void MeshA::Draw()
{
	// Previously, we multiplied each vertex one by one, but now we just have to send the world matrix to the gpu.

	// Bind Vertex Buffer and Index Buffer
	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_indexBuffer);

	// Setup Vertex Attributes
	SetupAttribute(0, 3, GL_FLOAT, Vertex3dUVNormal, m_position);
	SetupAttribute(1, 2, GL_FLOAT, Vertex3dUVNormal, m_texCoord);
	SetupAttribute(2, 3, GL_FLOAT, Vertex3dUVNormal, m_normal);

	// Enable all attrubutes
	for (int i = 0; i < 3; i++)
		glEnableVertexAttribArray(i);

	// Draw all indices in the index buffer
	glDrawElements(GL_TRIANGLES, m_indices.size(), GL_UNSIGNED_SHORT, (void*)0);

	// Unbind Vertex Buffer and Index Buffer
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	// Disable all attributes (enabled in the macro)
	for (int i = 0; i < 3; i++)
		glDisableVertexAttribArray(i);

}