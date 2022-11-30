#ifndef GAME_H
#define GAME_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stb/stb_image.h>

#include "light.h"
#include "lesson.h"

#ifndef NO_IMGUI
#include <imgui/imgui.h>
#include <imgui/imgui_impl_glfw.h>
#include <imgui/imgui_impl_opengl3.h>
#endif

struct ModelSettings{
	float scale = 1.0f;
	float rotation = 180.0f;
	int x=0;
	int y=0;
	int z=0;
	float x1 = 0.0f, y1 = 0.0f, z1 = 0.0f;
	bool draw_it = true;
	void Append(Model& model){
		Transform3D transform;
		transform.SetScale(scale);
		transform.SetPosition(glm::vec3(x,y,z));//y.z.x
		transform.SetRotation(glm::vec3(glm::radians(rotation)));
		std::vector<glm::mat4> matrices;
		for(int i = 0; i < model.GetNumMatricesMeshes(); i++){
			matrices.push_back(transform.GetMatrix());
		}	
		model.SetMatricesMeshes(matrices);
	}
	void AppendF(Model& model){
		Transform3D transform;
		transform.SetScale(scale);
		transform.SetPositionF(glm::fvec3(x1,y1,z1));//y.z.x
		
		transform.SetRotation(glm::vec3(glm::radians(rotation)));
		std::vector<glm::fmat4> matricesf;
		for(int i = 0; i < model.GetNumMatricesMeshes(); i++){
			matricesf.push_back(transform.GetMatrixF());
		}	
		model.SetMatricesMeshesF(matricesf);
	}
	void AppendF(Model& model, Model& model2){
		Transform3D transform;
		transform.SetScale(scale);
		transform.SetPositionF(glm::fvec3(x1,y1,z1));//y.z.x
		
		transform.SetRotation(glm::vec3(glm::radians(rotation)));
		std::vector<glm::fmat4> matricesf;
		for(int i = 0; i < model.GetNumMatricesMeshes(); i++){
			matricesf.push_back(transform.GetMatrixF());
		}	
		model.SetMatricesMeshesF(matricesf);
		model2.SetMatricesMeshesF(matricesf);
	}
	void Append(Model& model, Model& model2){
		Transform3D transform;
		transform.SetScale(scale);
		transform.SetPosition(glm::vec3(x,y,z));//y.z.x
		transform.SetRotation(glm::vec3(glm::radians(rotation)));
		std::vector<glm::mat4> matrices;
		for(int i = 0; i < model.GetNumMatricesMeshes(); i++){
			matrices.push_back(transform.GetMatrix());
		}	
		model.SetMatricesMeshes(matrices);
		model2.SetMatricesMeshes(matrices);
	}
};

 

class GameApp{
public:
	//float size = 1.0f, rotation = 180.0f;//crow scale
	//int x=0, y=5, z=0;
	//bool draw_crow = true, draw_trees = true, outline = true, draw_ground = true;
	bool outline = true;//for crow
	ModelSettings crow, trees, ground, pokoj;
	bool draw_sky = false;
	float color[4] = {0.0f, 0.0f,0.0f,0.0f};
    GLFWwindow * window;
    int width=800, height=800;
	// Variables to create periodic event for FPS displaying
	double prevTime = 0.0;
	double crntTime = 0.0;
	double timeDiff;

	bool use_galaxy = true;//else -> use skybox2

	//interactiveball
	int speed1=70, speed2 = 350, speed3 = 80;
	bool draw1 = true, draw2 = true, use_jirka = false;
	int num_balls = 35;
	float r = 4.0f, r2 = 6.0f, r3 = 4.0f, ball_y=5.0f, ball_y2=5.0f;//polomer
	float ball_col[4] = {1.0f,0.5f,0.3f,1.0f}, ball_col2[4] = {0.0f,0.1f,0.0f,1.0f};//rgba

	//light settings

	glm::vec3 lightColor = {1.0f,1.0f,1.0f};
	glm::vec3 lightEndColor = {1.0f,1.0f,1.0f};
	glm::vec3 lightPos = {0.0f,0.0f,0.0f};
	int type = LIGHT_TYPE_DIRECT;
	int gradient = GRADIENT_NOGRADIENT;
	LightSettings set =
	{
		 0.90f,
 		 0.95f,
			//distance for point light
 		 5.0f,
 		 1.0f,//pr 1    nebo 3
 		 0.04f,//pr 0,04 nebo 0,7
	};
	Light *light;

	// Keeps track of the amount of frames in timeDiff
	unsigned int counter = 0;
    GameApp(){
		
    }
	void CreateLight(Shader shaderligh){light = new Light(shaderligh, lightColor, lightEndColor, lightPos, type, gradient, set);}
	void RecreateLight(Shader shaderligh){

		light->recreate(shaderligh, lightColor, lightEndColor, lightPos, type, gradient, set);
	}
    bool Init();
    void Clear(float r, float g, float b);
    void Destroy();
	void UpdateFps();
    void OnEvents();
    int ShouldClose();
    void SetInstancingDraw();
	#ifndef NO_IMGUI
	void ImguiDraw(Shader& shaderProgram);
	void InitDraw();
	#endif
};



//need :
// skybox.frag
// skybox.vert
// skybox/right.png
// skybox/left.png
// skybox/top.png
// skybox/bottom.png
// skybox/front.png
// skybox/back.png
class Skybox{
public:
	Shader*shader;
	unsigned int cubemapTexture;
	unsigned int skyboxVAO, skyboxVBO, skyboxEBO;
	bool loaded = false; //0 -> 1. skybox, 1 -> 2. skybox
    std::string facesCubemap[6] =
	{
		"../res/img/skybox/right.png",
		"../res/img/skybox/left.png",
		"../res/img/skybox/top.png",
		"../res/img/skybox/bottom.png",
		"../res/img/skybox/front.png",
		"../res/img/skybox/back.png",
	};
	std::string facesCubemap2[6] =
	{
		"../res/img/skybox2/right.jpg",
		"../res/img/skybox2/left.jpg",
		"../res/img/skybox2/top.jpg",
		"../res/img/skybox2/bottom.jpg",
		"../res/img/skybox2/front.jpg",
		"../res/img/skybox2/back.jpg",
	};
    float skyboxVertices[3][8] =
    {
	    //   Coordinates
	   -1.0f, -1.0f,  1.0f,//        7--------6
	    1.0f, -1.0f,  1.0f,//       /|       /|
	    1.0f, -1.0f, -1.0f,//      4--------5 |
	   -1.0f, -1.0f, -1.0f,//      | |      | |
	   -1.0f,  1.0f,  1.0f,//      | 3------|-2
	    1.0f,  1.0f,  1.0f,//      |/       |/
	    1.0f,  1.0f, -1.0f,//      0--------1
	    -1.0f,  1.0f, -1.0f
    };

    unsigned int skyboxIndices[3][12] =
    {
	    // Right
	    1, 2, 6,
	    6, 5, 1,
	    // Left
	    0, 4, 7,
	    7, 3, 0,
	    // Top
	    4, 5, 6,
	    6, 7, 4,
	    // Bottom
	    0, 3, 2,
	    2, 1, 0,
	    // Back
	    0, 1, 5,
	    5, 4, 0,
	    // Front
	    3, 7, 6,
	    6, 2, 3
    };
    Skybox(std::string vertex_path, std::string fragment_path){
		shader = new Shader(vertex_path.c_str(), fragment_path.c_str());
    }
    void Init();
    void LoadResources();
	void LoadResources2();
	void LoadResources(std::string _facesCubemap[6]);
	void ReloadResources(std::string _facesCubemap[6]);
	void LoadShader();
    void Draw(Camera *cam, int width, int height);
    void Destroy();

};

void resizeCallback(GLFWwindow* win, int w, int h);
void frameBufferCallback(GLFWwindow* win, int w, int h);



#endif