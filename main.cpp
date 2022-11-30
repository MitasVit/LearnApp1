//moznosti:
//NO_IMGUI - bez imgui
//NO_DEBUG - bez debugu

#include"inc/mesh.h"
#include "inc/model.h"
#include "inc/game.h"
#include "inc/transform3d.h"
#include "inc/interactive.h"
#include "inc/timer.h"
#include "inc/path.h"
#include "inc/imgui_style.h"


#include <vector>
#include <thread>
#include <sstream>


#define STB_IMAGE_IMPLEMENTATION
#include <stb/stb_image.h>
#include <stb/stb_easy_font.h>

using namespace std;
using namespace glm;

float DistanceFromCamera(Camera cam, vec3 objpos){
	return (length(cam.Position - objpos));
}

int main()
{
	try{
		//app create & init
		GameApp app;
		DEBUG("creating app");
		if(app.Init() == false){
			DEBUG("cant create app");
			app.Destroy();
		}

		//create & init & load sky
		DEBUG("creating skybox")
		Skybox sky("../res/fragments/skybox.vert", "../res/fragments/skybox.frag");
		//prepare data for skybox
		DEBUG("skybox init");
		sky.Init();
		//load textures from files
		DEBUG("skybox load textures");
		sky.LoadResources();

		// Generates Shader objects
		DEBUG("shader program - default");
		Shader shaderProgram("../res/fragments/default.vert", "../res/fragments/default.frag");
		DEBUG("shader program - outlining");
		Shader outliningProgram("../res/fragments/outlining.vert","../res/fragments/outlining.frag");

		Shader colorProgram("../res/fragments/colored.vert","../res/fragments/colored.frag" );

		DEBUG("creating light");
		app.CreateLight(shaderProgram);
		//Light someLight(shaderProgram, _white, _blue, vec3(10.5f, 10.5f, 10.5f), LIGHT_TYPE_DIRECT, GRADIENT_NOGRADIENT, defSettings);


		#ifndef NO_IMGUI
			//init draw for imgui
			DEBUG("preparing imgui");
			app.InitDraw();
		#endif

		//load data from fragment & vertex shader
		DEBUG("load shader for skybox");
		sky.LoadShader();

		// Creates camera object
		DEBUG("creating camera");
		Camera camera(app.width, app.height, vec3(0.0f, 2.0f, 2.0f));//position
	
		// Load models
		DEBUG("-start loading models");
		DEBUG("\n\nLOADING: \"../res/models/sphere/scene.gltf\"\n\n");
		Model sphere("../res/models/sphere/scene.gltf");
		DEBUG("\n\nLOADING: \"../res/bunny/scene.gltf\"\n\n");
		Model bunny("../res/models/bunny/scene.gltf");
		DEBUG("\n\nLOADING: \"../res/ground/scene.gltf\"\n\n");
		Model ground("../res/models/ground/scene.gltf");

		//DEBUG("\n\nLOADING: \"../res/crow/scene.gltf\"\n\n");
		Model crow("../res/models/crow/scene.gltf");
		DEBUG("\n\nLOADING: \"../res/crow-outline/scene.gltf\"\n\n");
		Model crow_outline("../res/models/crow-outline/scene.gltf");

		DEBUG("\n\nLOADING: \"../res/tree/scene.gltf\"\n\n");
		Model tree("../res/models/tree/scene.gltf");



		DEBUG("creating transformation");
		Transform3D tr;
		tr.SetScale(0.5f);
		tr.SetPosition(vec3(0, 2.4, 0));//y.z.x
		tr.SetRotation(vec3(radians(50.0f)));
		vector<mat4> mats;
		for(int i = 0; i < crow.GetNumMatricesMeshes(); i++){
			mats.push_back(tr.GetMatrix());
		}

		DEBUG("loading textures");
		Texture plank("../res/img/planks.png", "diffuse", 0);
		Texture dif("../res/img/crow/diffuse.png", "diffuse", 0);
		Texture tex("../res/img/icon.png", "diffuse", 0);
		Texture jirka("../res/img/jirka.jpg", "diffuse", 0);

		//for faster rendering when there are many models
		app.SetInstancingDraw();

		Timer game_time;
		game_time.Start();

		bool stoupat = true;

		DEBUG("\n\nLOADING: \"../res/models/sphere/scene.gltf\"\n\n");
		InteractiveSphere test("../res/models/sphere/scene.gltf"), test2, test3, test4, test5;
		test.clone(test2);
		test.clone(test3);
		test.clone(test4);
		test.clone(test5);
		vector<InteractiveSphere> balls;
		for(int i = 0; i < 20; i++){
			InteractiveSphere tmp;
			test.clone(tmp);
			balls.push_back(tmp);
		}

		app.crow.draw_it = false;//we dont want to see crow
		app.trees.draw_it = false;

		vector<Point *> points;
		points.push_back(new Point(1.f,1.f));
		points.push_back(new Point(10.f,1.f));
		points.push_back(new Point(20.f,11.f));
		points.push_back(new Point(10.f,21.f));
		points.push_back(new Point(20.f,31.f));

		Path pathtest(points,game_time.GetTime(), true, false, 1.f, 0);


		SetupMyImGuiStyle();

		// Main while loop
		while (!app.ShouldClose())
		{
			DEBUG("drawing");
			glUniform1f(glGetUniformLocation(shaderProgram.ID, "u_time" ), glfwGetTime());
			app.RecreateLight(shaderProgram);

			app.UpdateFps();

			if(app.num_balls > balls.size()){
				//too few balls what we want - creating them
				for(int i = 0; i < (app.num_balls - balls.size()); i++ ){
					InteractiveSphere tmp;
					test.clone(tmp);
					balls.push_back(tmp);
				}
			}
			else if(app.num_balls < balls.size()){
				//too much balls what we want
				for(int i = 0; i < (balls.size() - app.num_balls); i++ ){
					balls.erase(balls.end());
				}
			}
			if(app.draw1){
				for(int i =0;  i < balls.size();i++){
					balls.at(i).SetY(i*0.5);
					balls.at(i).CircleForce(game_time.GetTime()+(i*2), app.r3, app.speed3, 0, 2);
					balls.at(i).Update();
				}
			}
			if(app.draw2){
				test2.SetY(app.ball_y2);
				test3.SetY(app.ball_y);
				test4.SetY(app.ball_y);
				test5.SetY(app.ball_y);

				Point *p = new Point(0,0);
				p->SetPosFromPoint(pathtest.GetPos(game_time.GetTime()));
				test.SetPos(p->GetX(), 5.0f, p->GetY());
				test2.CircleForce(game_time.GetTime(), app.r2, app.speed2, 0, 2);
				test3.CircleForce(game_time.GetTime(), app.r2, app.speed1, 10, 2);
				test4.CircleForce(game_time.GetTime(), app.r, app.speed1, 10, 2);
				test5.CircleMove(game_time.GetTime(), app.r, app.speed1, 20);

				test.Update();
				test2.Update();
				test3.Update();
				test4.Update();
				test5.Update();
			}

			DEBUG("setting app title");
			string newTitle = "glfwtime: " + to_string(glfwGetTime()) + " - gametime: " + to_string(game_time.GetTime()) + " - x: " + to_string(test5.x) + " - y: " + to_string(test5.y) + " - z: " + to_string(test.z) + "--CAMPOS x: " + to_string(camera.Position.x) + " -y: " + to_string(camera.Position.y) + " -z: " +to_string(camera.Position.z)+"--num object: " + to_string(balls.size() + 6); 
			glfwSetWindowTitle(app.window, newTitle.c_str());
		

			#ifndef NO_IMGUI
				glViewport(350,0,app.width+350, app.height);
			#endif

			// Handles camera inputs
			DEBUG("input for camera + updating camera matrix");
			camera.Inputs(app.window);
			// Updates and exports the ../res/fragments/camera matrix to the Vertex Shader
			camera.updateMatrix(45.0f, 0.1f, 100.0f);
		
			if(app.draw_sky){
				DEBUG("drawing skybox");
				app.Clear(0.0f,0.0f,0.0f);//black
				if(sky.loaded == 0 && app.use_galaxy == false){
					sky.LoadResources2();
				}
				else if(sky.loaded == 1 && app.use_galaxy == true){
					sky.LoadResources();
				}
				sky.Draw(&camera, app.width, app.height);
			}else{
				DEBUG("clearing with color");
				#ifndef NO_IMGUI
					app.Clear(app.color[0], app.color[1], app.color[2]);
				#else
					app.Clear(0.0f,0.0f,0.0f);//black
				#endif
			}
			if(app.ground.draw_it){
				DEBUG("drawing ground");
				ground.Draw(shaderProgram, camera, plank);
			}

			glDisable(GL_CULL_FACE);

			//app.pokoj.AppendF(pokoj);
			//pokoj.Draw(shaderProgram, camera);
			//grass.Draw(shaderProgram, camera);
			if(app.trees.draw_it){
				DEBUG("drawing trees");
				tree.Draw(shaderProgram, camera, plank);
			}

			if(app.draw2){

				if(app.use_jirka){
					test.Draw(camera, shaderProgram, jirka);
					test2.Draw(camera, shaderProgram, jirka);
					test3.Draw(camera, shaderProgram, jirka);
					test4.Draw(camera, shaderProgram, jirka);
					test5.Draw(camera, shaderProgram, jirka);
				}else{
					test.Draw(camera, shaderProgram, genFcol4(app.ball_col2));
					test2.Draw(camera, shaderProgram, genFcol4(app.ball_col2));

					test3.Draw(camera, shaderProgram, genFcol4(app.ball_col));
					test4.Draw(camera, shaderProgram, genFcol4(app.ball_col));
					test5.Draw(camera, shaderProgram, genFcol4(app.ball_col));
				}
			}
			if(app.draw1){
				for(int i =0;  i < balls.size();i++){
					balls.at(i).Draw(camera, shaderProgram, plank);
				}
			}
		
			if(app.crow.draw_it){
				DEBUG("drawing crow");
				DEBUG("appendign floats");
				app.crow.AppendF(crow, crow_outline);

				if(!app.outline){
					DEBUG("crow without outline");
					crow.DrawF(shaderProgram, camera, dif);
				}else{
					DEBUG("crow with outline");
					crow.DrawWithOutline(shaderProgram, camera, dif, crow_outline, outliningProgram);
				}
			}
			#ifndef NO_IMGUI
				DEBUG("Drawing imgui");
				app.ImguiDraw(outliningProgram);
			#else
				DEBUG("Imgui drawing turned off");
			#endif

			app.OnEvents();
		}
		DEBUG("Destroying...");

		// Delete all the objects we've created

		shaderProgram.Delete();
		outliningProgram.Delete();
	
		sky.Destroy();
		app.Destroy();

		tex.Delete();
		dif.Delete();
		jirka.Delete();
		plank.Delete();

		return 0;
	}catch(json::exception &e){
		cout << endl << e.what() << endl;
	}catch(exception &e){
		cout << endl << e.what() << endl;
	}
}