#include "game.h"

void resizeCallback(GLFWwindow* win, int w, int h){
    glfwGetWindowSize(win, &w, &h);
}
void frameBufferCallback(GLFWwindow* win, int w, int h){
    glViewport(0,0,w,h);
}

bool GameApp::Init(){
    //init glfw
	if(glfwInit() == GLFW_FALSE){
        //cant init
        return false;
    }
    //set glfw version gl to 3.3
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    //set core profile
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    //create window
	#ifndef NO_IMGUI
	window = glfwCreateWindow(width, height, "Universe - imgui", NULL, NULL);
    #else
	window = glfwCreateWindow(width, height, "Universe", NULL, NULL);
	#endif
    if (window == NULL)
	{
        //end glfw
        glfwTerminate();
        return false;
    }

    //set glfw to window
    glfwMakeContextCurrent(window);
    //load glad
    gladLoadGLLoader((GLADloadproc) glfwGetProcAddress);
	// Specify the viewport of OpenGL in the Window to 0,0
	glViewport(0, 0, width, height);

    //set input callbacks
	glfwSetFramebufferSizeCallback(window, frameBufferCallback);
    glfwSetWindowSizeCallback(window, resizeCallback);

    return true;
}

void GameApp::Clear(float r, float g, float b){
	glClearColor(r,g,b, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT |  GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT); 
}

void GameApp::Destroy(){
	glfwDestroyWindow(window);
	glfwTerminate();
    #ifndef NO_IMGUI
    //shutdown imgui
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();
    #endif
}

void GameApp::OnEvents(){
    glfwSwapBuffers(window);
	glfwPollEvents();
}

int GameApp::ShouldClose(){
    return glfwWindowShouldClose(window);
}

void GameApp::SetInstancingDraw(){
	// Enables the Depth Buffer
	glEnable(GL_DEPTH_TEST);

	//------------OULINE-----------
	// Enables the Stencil Buffer
	glEnable(GL_STENCIL_TEST);
	/// Sets rules for outcomes of stecil tests
	glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);

	 //Enables Cull Facing
	glEnable(GL_CULL_FACE);
	// Keeps front faces
	glCullFace(GL_FRONT);
	// Uses counter clock-wise standard
	glFrontFace(GL_CCW);
}

void GameApp::UpdateFps(){
    // Updates counter and times
		crntTime = glfwGetTime();
		timeDiff = crntTime - prevTime;
		counter++;

		if (timeDiff >= 1.0 / 30.0)
		{
			// Creates new title
			std::string FPS = std::to_string((1.0 / timeDiff) * counter);
			std::string ms = std::to_string((timeDiff / counter) * 1000);
			#ifndef NO_IMGUI
			std::string newTitle = "Universe - imgui - " + FPS + "FPS / " + ms + "ms";
			#else
			std::string newTitle = "Universe - " + FPS + "FPS / " + ms + "ms";
			#endif
			glfwSetWindowTitle(window, newTitle.c_str());

			// Resets times and counter
			prevTime = crntTime;
			counter = 0;

			// Use this if you have disabled VSync
			//camera.Inputs(window);
		}
}


void Skybox::Init(){
    // Create VAO, VBO, and EBO for the skybox
    glGenVertexArrays(1, &skyboxVAO);
	glGenBuffers(1, &skyboxVBO);
	glGenBuffers(1, &skyboxEBO);
	glBindVertexArray(skyboxVAO);
	glBindBuffer(GL_ARRAY_BUFFER, skyboxVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(skyboxVertices), &skyboxVertices, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, skyboxEBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(skyboxIndices), &skyboxIndices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void Skybox::LoadResources(std::string _facesCubemap[6]){
	glGenTextures(1, &cubemapTexture);
	glBindTexture(GL_TEXTURE_CUBE_MAP, cubemapTexture);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	// These are very important to prevent seams
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
	// This might help with seams on some systems
	//glEnable(GL_TEXTURE_CUBE_MAP_SEAMLESS);

	// Cycles through all the textures and attaches them to the cubemap object
	for (unsigned int i = 0; i < 6; i++)
	{
		int width, height, nrChannels;
		unsigned char* data = stbi_load(_facesCubemap[i].c_str(), &width, &height, &nrChannels, 0);
		if (data)
		{
			stbi_set_flip_vertically_on_load(false);
			glTexImage2D
			(
				GL_TEXTURE_CUBE_MAP_POSITIVE_X + i,
				0,
				GL_RGB,
				width,
				height,
				0,
				GL_RGB,
				GL_UNSIGNED_BYTE,
				data
			);
			stbi_image_free(data);
		}
		else
		{
			stbi_image_free(data);
		}
	}
}

void Skybox::LoadResources(){
	loaded = false;
    glGenTextures(1, &cubemapTexture);
	glBindTexture(GL_TEXTURE_CUBE_MAP, cubemapTexture);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	// These are very important to prevent seams
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
	// This might help with seams on some systems
	//glEnable(GL_TEXTURE_CUBE_MAP_SEAMLESS);

	// Cycles through all the textures and attaches them to the cubemap object
	for (unsigned int i = 0; i < 6; i++)
	{
		int width, height, nrChannels;
		unsigned char* data = stbi_load(facesCubemap[i].c_str(), &width, &height, &nrChannels, 0);
		if (data)
		{
			stbi_set_flip_vertically_on_load(false);
			glTexImage2D
			(
				GL_TEXTURE_CUBE_MAP_POSITIVE_X + i,
				0,
				GL_RGB,
				width,
				height,
				0,
				GL_RGB,
				GL_UNSIGNED_BYTE,
				data
			);
			stbi_image_free(data);
		}
		else
		{
			stbi_image_free(data);
		}
	}
}

void Skybox::LoadResources2(){
		loaded = true;
    glGenTextures(1, &cubemapTexture);
	glBindTexture(GL_TEXTURE_CUBE_MAP, cubemapTexture);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	// These are very important to prevent seams
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
	// This might help with seams on some systems
	//glEnable(GL_TEXTURE_CUBE_MAP_SEAMLESS);

	// Cycles through all the textures and attaches them to the cubemap object
	for (unsigned int i = 0; i < 6; i++)
	{
		int width, height, nrChannels;
		unsigned char* data = stbi_load(facesCubemap2[i].c_str(), &width, &height, &nrChannels, 0);
		if (data)
		{
			stbi_set_flip_vertically_on_load(false);
			glTexImage2D
			(
				GL_TEXTURE_CUBE_MAP_POSITIVE_X + i,
				0,
				GL_RGB,
				width,
				height,
				0,
				GL_RGB,
				GL_UNSIGNED_BYTE,
				data
			);
			stbi_image_free(data);
		}
		else
		{
			stbi_image_free(data);
		}
	}
}

void Skybox::ReloadResources(std::string _facesCubemap[6]){
	 glGenTextures(1, &cubemapTexture);
	glBindTexture(GL_TEXTURE_CUBE_MAP, cubemapTexture);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	// These are very important to prevent seams
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
	// This might help with seams on some systems
	//glEnable(GL_TEXTURE_CUBE_MAP_SEAMLESS);

	// Cycles through all the textures and attaches them to the cubemap object
	for (unsigned int i = 0; i < 6; i++)
	{
		int width, height, nrChannels;
		unsigned char* data = stbi_load(_facesCubemap[i].c_str(), &width, &height, &nrChannels, 0);
		if (data)
		{
			stbi_set_flip_vertically_on_load(false);
			glTexImage2D
			(
				GL_TEXTURE_CUBE_MAP_POSITIVE_X + i,
				0,
				GL_RGB,
				width,
				height,
				0,
				GL_RGB,
				GL_UNSIGNED_BYTE,
				data
			);
			stbi_image_free(data);
		}
		else
		{
			stbi_image_free(data);
		}
	}
}

void Skybox::LoadShader(){
	//activate and locate skybox shader
	shader->Activate();
	glUniform1i(glGetUniformLocation(shader->ID, "skybox"), 0);
}

void Skybox::Draw(Camera *cam, int width, int height){
    glDepthFunc(GL_LEQUAL);

		shader->Activate();
		glm::mat4 view = glm::mat4(1.0f);
		glm::mat4 projection = glm::mat4(1.0f);
		// We make the mat4 into a mat3 and then a mat4 again in order to get rid of the last row and column
		// The last row and column affect the translation of the skybox (which we don't want to affect)
		view = glm::mat4(glm::mat3(glm::lookAt(cam->Position, cam->Position + cam->Orientation, cam->Up)));
		projection = glm::perspective(glm::radians(45.0f), (float)width / height, 0.1f, 100.0f);
		glUniformMatrix4fv(glGetUniformLocation(shader->ID, "view"), 1, GL_FALSE, glm::value_ptr(view));
		glUniformMatrix4fv(glGetUniformLocation(shader->ID, "projection"), 1, GL_FALSE, glm::value_ptr(projection));

		// Draws the cubemap as the last object so we can save a bit of performance by discarding all fragments
		// where an object is present (a depth of 1.0f will always fail against any object's depth value)
		glBindVertexArray(skyboxVAO);
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_CUBE_MAP, cubemapTexture);
		glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);

		glDepthFunc(GL_LESS);
}

void Skybox::Destroy(){
    cubemapTexture=0;
	skyboxVAO=0;
    skyboxVBO=0;
    skyboxEBO=0;
    for(int i = 0; i < 6; i++){
        facesCubemap[i] = "";
    }
    for(int i = 0; i < 3; i++){
        for(int y = 0; y < 12; y++){
            skyboxIndices[i][y] = 0;
        }
        for(int y = 0; y < 12; y++){
            skyboxVertices[i][y] = 0;
        }
    }
	shader->Delete();

}

#ifndef NO_IMGUI

void GameApp::InitDraw(){
    // Initialize ImGUI
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	ImGui::StyleColorsDark();
	ImGui_ImplGlfw_InitForOpenGL(window, true);
	ImGui_ImplOpenGL3_Init("#version 330");
}


void GameApp::ImguiDraw(Shader& shaderProgram){
   //drop here things to draw
 	//imgui frame init
    ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();
	ImGui::SetNextWindowSize(ImVec2(350,height));
	ImGui::SetNextWindowPos(ImVec2(0,0));
	
	ImGui::Begin("settings");
	ImGui::BeginGroup();
	
	if (ImGui::BeginTabBar("actions"))
	{
    	if (ImGui::BeginTabItem("Main"))
    	{
            ImVec2 padding = ImGui::GetStyle().WindowPadding;
            ImGui::SetCursorPosX(ImGui::GetCursorPosX() - padding.x);
            ImVec2 size = ImGui::GetContentRegionAvail();
            size.x += padding.x;
            ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(padding.x, 0.0f));

            ImGui::BeginChild("h", size, false, ImGuiWindowFlags_AlwaysUseWindowPadding);
            	ImGui::PopStyleVar();

				//push here things to settings
				ImGui::Checkbox("Draw trees", &trees.draw_it);
				ImGui::Checkbox("Draw crow", &crow.draw_it);
				ImGui::Checkbox("Draw outline", &outline);
				ImGui::Checkbox("Draw ground", &ground.draw_it);
				ImGui::Checkbox("Draw textured balls", &draw1);
				ImGui::Checkbox("Draw color balls", &draw2);
				ImGui::Checkbox("Draw sky", &draw_sky);

            ImGui::EndChild();

       		ImGui::EndTabItem();
    	}
    	if (ImGui::BeginTabItem("Balls"))
    	{
			ImVec2 padding = ImGui::GetStyle().WindowPadding;
            ImGui::SetCursorPosX(ImGui::GetCursorPosX() - padding.x);
            ImVec2 size = ImGui::GetContentRegionAvail();
            size.x += padding.x;//ImGuiStyleVar_ScrollbarSize
            ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(padding.x, 0.0f));

            if(ImGui::BeginChild("h", size, false, ImGuiWindowFlags_AlwaysUseWindowPadding)){
            	ImGui::PopStyleVar();
        		ImGui::SliderInt("Speed of first colored balls", &speed1, 1, 5000);
				ImGui::SliderInt("Speed of second colored balls", &speed2, 1, 5000);
				ImGui::SliderInt("Speed of textured balls", &speed3, 1, 5000);
				ImGui::SliderFloat("Radius of first colored balls", &r, 2.0f, 30.0f);
				ImGui::SliderFloat("Radius of second colored balls", &r2, 2.0f, 30.0f);
				ImGui::SliderFloat("Radius of textured balls", &r3, 2.0f, 30.0f);
				ImGui::SliderInt("Number of textured balls", &num_balls, 1, 1000);
				ImGui::InputFloat("Y position of first colored balls", &ball_y, 0.1f);
				ImGui::InputFloat("Y position of second colored balls", &ball_y2, 0.1f);
				ImGui::ColorPicker4("ball color", ball_col);
				ImGui::ColorPicker4("ball color2", ball_col2);
				

            ImGui::EndChild();
			}
       	 	ImGui::EndTabItem();
    	}
		if (ImGui::BeginTabItem("Crow"))
    	{
        	ImGui::Checkbox("Draw crow", &crow.draw_it);
			ImGui::Checkbox("Draw outline", &outline);
			ImGui::SliderFloat("Scale", &crow.scale, 0.2f, 2.0f); 
			ImGui::SliderFloat("Rotation", &crow.rotation, 0.0f, 360.0f);
			ImGui::InputFloat("x", &crow.x1,0.01f);
			ImGui::InputFloat("y", &crow.y1,0.01f);
			ImGui::InputFloat("z", &crow.z1, 0.01f);
       	 	ImGui::EndTabItem();
    	}
		if (ImGui::BeginTabItem("Light"))
    	{
			ImVec2 padding = ImGui::GetStyle().WindowPadding;
            ImGui::SetCursorPosX(ImGui::GetCursorPosX() - padding.x);
            ImVec2 size = ImGui::GetContentRegionAvail();
            size.x += padding.x;//ImGuiStyleVar_ScrollbarSize
            ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(padding.x, 0.0f));

            if(ImGui::BeginChild("hah", size, false, ImGuiWindowFlags_AlwaysUseWindowPadding)){            	ImGui::PopStyleVar();
			ImGui::InputFloat("x", &lightPos.x,0.01f);
			ImGui::InputFloat("y", &lightPos.y,0.01f);
			ImGui::InputFloat("z", &lightPos.z, 0.01f);
			ImGui::Combo("type", &type, "no light\0point\0spot\0direct");
			ImGui::Combo("gradient", &gradient, "no gradient\0normal\0animated");
			ImGui::InputFloat("innercone", &set.innerCone, 0.01f);
			ImGui::InputFloat("outercone", &set.outerCone, 0.01f);
			ImGui::InputFloat("point light dist.", &set.distance, 0.01f);
			ImGui::InputFloat("f(a)", &set.a, 0.01f);
			ImGui::InputFloat("f(b)", &set.b, 0.01f);
			float f[4] = {lightColor.x,lightColor.y,lightColor.z, 1.0f};
			float f2[4] = {lightEndColor.x,lightEndColor.y,lightEndColor.z, 1.0f};
        	ImGui::ColorPicker3("light color - start", f);
			ImGui::ColorPicker3("light color - end", f2);
			lightColor.x = f[0];
			lightColor.y = f[1];
			lightColor.z = f[2];
			lightEndColor.x = f2[0];
			lightEndColor.y = f2[1];
			lightEndColor.z = f2[2];
			
			 ImGui::EndChild();
			}
       	 	ImGui::EndTabItem();
    	}
		if (ImGui::BeginTabItem("Others"))
    	{
			ImGui::Checkbox("Draw sky", &draw_sky);
        	ImGui::ColorPicker4("sky color", color);
			ImGui::Checkbox("Use galaxy skybox", &use_galaxy);
			ImGui::Checkbox("Use jirka.jpg textures on balls", &use_jirka);
       	 	ImGui::EndTabItem();
    	}
		
   		ImGui::EndTabBar();
	}

	ImGui::EndGroup();
	
	// Ends the window
	ImGui::End();

	glUniform4f(glGetUniformLocation(shaderProgram.ID, "color"), color[0], color[1], color[2], color[3]);

	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}
#endif