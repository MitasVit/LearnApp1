#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"

#include "inc/imgui_style.h"
#include "lib/IconsFontAwesome5.h"

#include <iostream>
#include <vector>
#include <ctime>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <math.h>
#include <inc/lesson.h>

#define STB_IMAGE_IMPLEMENTATION
#include <stb/stb_image.h>

#include "utils.h"

#include "bakalari/bakalari.h"

// Vertex Shader source code
const char* vertexShaderSource = "#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"uniform float size;\n"
"void main()\n"
"{\n"
"   gl_Position = vec4(size * aPos.x, size * aPos.y, size * aPos.z, 1.0);\n"
"}\0";
//Fragment Shader source code
const char* fragmentShaderSource = "#version 330 core\n"
"out vec4 FragColor;\n"
"uniform vec4 color;\n"
"void main()\n"
"{\n"
"   FragColor = color;\n"
"}\n\0";

using namespace std;

class ImTexture{
public:
	int width, height;
	GLuint id;

	ImTexture(string path){
		// Assigns the type of the texture ot the texture object

	// Stores the width, height, and the number of color channels of the image
	int widthImg, heightImg, numColCh;
	// Flips the image so it appears right side up
	//stbi_set_flip_vertically_on_load(true);
	
	// Reads the image from a file and stores it in bytes
	unsigned char* bytes = stbi_load(path.c_str(), &widthImg, &heightImg, &numColCh, 0);
	width = widthImg;
	height = heightImg;
	// Generates an OpenGL texture object
	glGenTextures(1, &id);
	// Assigns the texture to a Texture Unit
	glActiveTexture(GL_TEXTURE0 + 1);
	glBindTexture(GL_TEXTURE_2D, id);

	// Configures the type of algorithm that is used to make the image smaller or bigger
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	// Configures the way the texture repeats (if it does at all)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	// Extra lines in case you choose to use GL_CLAMP_TO_BORDER
	// float flatColor[] = {1.0f, 1.0f, 1.0f, 1.0f};
	// glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, flatColor);

	// Check what type of color channels the texture has and load it accordingly
	if (numColCh == 4)
		glTexImage2D
		(
			GL_TEXTURE_2D,
			0,
			GL_RGBA,
			widthImg,
			heightImg,
			0,
			GL_RGBA,
			GL_UNSIGNED_BYTE,
			bytes
		);
	else if (numColCh == 3)
		glTexImage2D
		(
			GL_TEXTURE_2D,
			0,
			GL_RGBA,
			widthImg,
			heightImg,
			0,
			GL_RGB,
			GL_UNSIGNED_BYTE,
			bytes
		);
	else if (numColCh == 1)
		glTexImage2D
		(
			GL_TEXTURE_2D,
			0,
			GL_RGBA,
			widthImg,
			heightImg,
			0,
			GL_RED,
			GL_UNSIGNED_BYTE,
			bytes
		);
	else
		throw std::invalid_argument("Automatic Texture type recognition failed");

	// Generates MipMaps
	glGenerateMipmap(GL_TEXTURE_2D);

	// Deletes the image data as it is already in the OpenGL Texture object
	stbi_image_free(bytes);

	// Unbinds the OpenGL Texture object so that it can't accidentally be modified
	glBindTexture(GL_TEXTURE_2D, 0);
	}

	int GetWidth(){
		return width;
	}

	int GetHeight(){ 
		return height;
	}

	GLuint GetID(){
		return id;
	}

};


bool *show_testing = new bool(false);
bool *show_main = new bool(false);
bool *show_form = new bool(false);
bool *show_text_editor = new bool(false);
bool *show_connect = new bool(false);
bool *show_tools = new bool(false);
bool *show_settings = new bool(false);
bool *show_main_menu = new bool(true);

static void ShowPlaceholderObject(const char* prefix)
{
   // ImGui::PushID(450);

    // Text and Tree nodes are less high than framed widgets, using AlignTextToFramePadding() we add vertical spacing to make the tree lines equal high.
    ImGui::TableNextRow();
    ImGui::TableSetColumnIndex(0);
    ImGui::AlignTextToFramePadding();
	//node open1
   // bool no1 = ImGui::TreeNode("Menu", "%s", prefix);
	ImGuiTreeNodeFlags otvirac = ImGuiTreeNodeFlags_OpenOnArrow | ImGuiTreeNodeFlags_DefaultOpen;
	ImGuiTreeNodeFlags otvirac2 = ImGuiTreeNodeFlags_OpenOnArrow;
	ImGuiTreeNodeFlags polozka = ImGuiTreeNodeFlags_Leaf | ImGuiTreeNodeFlags_DefaultOpen;
	ImGuiTreeNodeFlags subpolozka = ImGuiTreeNodeFlags_Bullet | ImGuiTreeNodeFlags_DefaultOpen;
	
	bool no1 = ImGui::TreeNodeEx("Menu", otvirac, "Menu");
	if(ImGui::IsItemClicked()){
		*show_main_menu = true;
	}
    ImGui::TableSetColumnIndex(1);
    ImGui::Text("text2");

    if (no1)
    {
		ImGui::PushID(0);
		ImGui::TableNextRow();
        ImGui::TableSetColumnIndex(0);
        ImGui::AlignTextToFramePadding();
		bool no2 = ImGui::TreeNodeEx("Propojení", otvirac, "Propojení");
		if(ImGui::IsItemClicked()){
			*show_connect = true;
		}
		
		if(no2){
			bool no3 = ImGui::TreeNodeEx("Bakaláři", polozka, "Bakaláři");
			if(no3){

			}
			if(ImGui::IsItemClicked()){
				//presunuti do bakalaru
			}
			ImGui::TreePop();//bakaláři
		}
		ImGui::TreePop();//propojení



        ImGui::TableSetColumnIndex(1);
        ImGui::SetNextItemWidth(-FLT_MIN);
		ImGui::Text("aaaaa");
    	ImGui::NextColumn();
		ImGui::PopID();

		ImGui::PushID(2);
		ImGui::TableNextRow();
        ImGui::TableSetColumnIndex(0);
        ImGui::AlignTextToFramePadding();
		bool no4 = ImGui::TreeNodeEx("Nastavení", otvirac, "Nastavení");
		if(ImGui::IsItemClicked()){
			*show_settings = true;
			*show_tools = false;
			*show_connect = false;
			*show_testing = false;
		}
		
		if(no4){
			bool no5 = ImGui::TreeNodeEx("Vzhled", polozka, "Vzhled");
			if(no5){
				if(ImGui::IsItemClicked()){
					//presunuti do vzhledu
				}
			}
			
			ImGui::TreePop();//vzhled
			bool no6 = ImGui::TreeNodeEx("Propojení", polozka, "Propojení");
			if(no6){
				if(ImGui::IsItemClicked()){
					//presunuti do Nastavení/propojení
				}
			}
			
			ImGui::TreePop();//propojeni
		}
		ImGui::TreePop();//nastavení



        ImGui::TableSetColumnIndex(1);
        ImGui::SetNextItemWidth(-FLT_MIN);
		ImGui::Text("aaaaa");
    	ImGui::NextColumn();
		ImGui::PopID();

		ImGui::PushID(3);
		ImGui::TableNextRow();
        ImGui::TableSetColumnIndex(0);
		ImGui::AlignTextToFramePadding();
		bool no7 = ImGui::TreeNodeEx("Nástroje", otvirac, "Nástroje");

		if (no7)
		{
			if (ImGui::IsItemClicked())
			{
				*show_tools = true;
				*show_connect = false;
				*show_settings = false;
				*show_testing = false;
			}
			bool no8 = ImGui::TreeNodeEx("Graf", polozka, "Graf");
			if (no8)
			{
				if (ImGui::IsItemClicked())
				{
					// presunuti do vzhledu
				}
			}
			ImGui::TreePop(); // graf

			bool no9 = ImGui::TreeNodeEx("Hledání zdrojů", polozka, "Hledání zdrojů");
			if (no9)
			{
				if (ImGui::IsItemClicked())
				{
					// presunuti do Nastavení/propojení
				}
			}
			ImGui::TreePop(); // hledani zdroju

			bool no10 = ImGui::TreeNodeEx("Kalkulačky", otvirac, "Kalkulačky");
			if (no10)
			{
				if (ImGui::IsItemClicked())
				{
					// presunuti do Nastroje/Kalkulacky
				}
				bool no11 = ImGui::TreeNodeEx("Palivo", subpolozka, "Palivo");
				if (no11)
				{
					if (ImGui::IsItemClicked())
					{
						// presunuti do Nastroje/Kalkulacky
					}
				}
				ImGui::TreePop(); // Nastroje/kalkulačky/palivo

				bool no12 = ImGui::TreeNodeEx("BMI", subpolozka, "BMI");
				if (no12)
				{
					if (ImGui::IsItemClicked())
					{
						// presunuti do Nastroje/Kalkulacky
					}
				}
				ImGui::TreePop(); // Nastroje/kalkulačky/bmi

				bool no13 = ImGui::TreeNodeEx("Mzdy a daně", subpolozka, "Mzdy a daně");
				if (no13)
				{
					if (ImGui::IsItemClicked())
					{
						// presunuti do Nastroje/Kalkulacky
					}
				}
				ImGui::TreePop(); // Nastroje/kalkulačky/dane

				bool no14 = ImGui::TreeNodeEx("Hmotnost materiálů", subpolozka, "Hmotnost materiálů");
				if (no14)
				{
					if (ImGui::IsItemClicked())
					{
						// presunuti do Nastroje/Kalkulacky
					}
				}
				ImGui::TreePop(); // Nastroje/kalkulačky/dane
			}
			ImGui::TreePop();// Nastroje/kalkulačky


			bool no15 = ImGui::TreeNodeEx("Průvodce vzorci", polozka, "Průvodce vzorci");
			if(no15){
				if(ImGui::IsItemClicked()){
					//presunuti do Nastavení/propojení
				}
			}
			ImGui::TreePop();//vzorce
		}
		ImGui::TreePop();//nástroje



        ImGui::TableSetColumnIndex(1);
        ImGui::SetNextItemWidth(-FLT_MIN);
		ImGui::Text("aaaaa");
    	ImGui::NextColumn();
		ImGui::PopID();
/*
        for (int i = 0; i < 8; i++)
        {
            ImGui::PushID(i); // Use field index as identifier.
			 ImGui::TableNextRow();
                ImGui::TableSetColumnIndex(0);
                ImGui::AlignTextToFramePadding();
                ImGuiTreeNodeFlags flags2 =  ImGuiTreeNodeFlags_NoTreePushOnOpen | ImGuiTreeNodeFlags_Bullet | ImGuiTreeNodeFlags_DefaultOpen;
                ImGui::TreeNodeEx("Field", flags2, "Field_%d", i);

                ImGui::TableSetColumnIndex(1);
                ImGui::SetNextItemWidth(-FLT_MIN);
				ImGui::Text("aaaaa");
                ImGui::NextColumn();
          //  }
            ImGui::PopID();
        }*/
        ImGui::TreePop();//menu
    }

    //ImGui::PopID();
}

ImVector<ImWchar> ranges;
ImFontGlyphRangesBuilder builder;
char path[256] = "test.xml";

struct lesson_data{
	char author[32];
    char create_date[50];//doplni se samo -> Date2Str
    char subject[16];
	char title[48];
    char text[1024*16];
	//pridat: tagy, excercises, sources, examples, solutions
};


//type must be with first big letter
//size -> 0 (title)
//     -> 1 (text)
ImFont* LoadRoboto(ImGuiIO io2, string type, bool size);
ImFont* LoadRoboto2(ImGuiIO io2, string type, float size);


void LessonData2Lesson(lesson_data* data, Lesson* lesson);


void ShowForm(bool *p_open, lesson_data* data, Lesson* thislesson);
void ShowLesson(bool *p_open, Lesson testlesson);
void ShowIconsFonts(bool *p_open, ImFont* fonts[6][4], ImFont* titlefont, ImFont* iconfont, Lesson* les);

//void ShowButtonChild(ImVec2 pos, ImTexture image, string text,int id);
//void ShowButtonChild(ImVec2 pos, ImTexture image, string text,int id,bool *sh_set, bool* sh_con, bool *sh_tool);
void ShowButtonChild2(ImVec2 pos, ImTexture image, string text,int id,int* menu_part, int go_to);

int MaxWTable(TimeTable &a);

void YTDownload(char odkaz[64]){
	string o = char2str(odkaz);
	//dodelat
	//string cmd = "python -m "
	//system()
}
void SPDownload(char odkaz[128]){
	string tmp;
	for (int x = 0; (x < (128 / sizeof(char)) + 1); x++) { 
		tmp = tmp + odkaz[x]; 
	} 
	//dodelat
	string cmd = "python -m spotdl download " + tmp;
	cout << "command send: " << cmd << endl;
	system(cmd.c_str());
}

const char*fromsp(char odkaz[128]){
	string tmp;
	for (int x = 0; (x < (128 / sizeof(char)) + 1); x++) { 
		tmp = tmp + odkaz[x]; 
	}
	return tmp.c_str();
}

int main()
{
	// Initialize GLFW
	glfwInit();

	// Tell GLFW what version of OpenGL we are using 
	// In this case we are using OpenGL 3.3
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	// Tell GLFW we are using the CORE profile
	// So that means we only have the modern functions
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// Create a GLFWwindow object of 800 by 800 pixels, naming it "YoutubeOpenGL"
	GLFWwindow* window = glfwCreateWindow(800, 800, "Lesson renderer", NULL, NULL);
	// Error check if the window fails to create
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	// Introduce the window into the current context
	glfwMakeContextCurrent(window);

	//Load GLAD so it configures OpenGL
	gladLoadGLLoader((GLADloadproc) glfwGetProcAddress);
	// Specify the viewport of OpenGL in the Window
	// In this case the viewport goes from x = 0, y = 0, to x = 800, y = 800
	glViewport(0, 0, 800, 800);



	// Create Vertex Shader Object and get its reference
	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	// Attach Vertex Shader source to the Vertex Shader Object
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	// Compile the Vertex Shader into machine code
	glCompileShader(vertexShader);

	// Create Fragment Shader Object and get its reference
	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	// Attach Fragment Shader source to the Fragment Shader Object
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	// Compile the Vertex Shader into machine code
	glCompileShader(fragmentShader);

	// Create Shader Program Object and get its reference
	GLuint shaderProgram = glCreateProgram();
	// Attach the Vertex and Fragment Shaders to the Shader Program
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	// Wrap-up/Link all the shaders together into the Shader Program
	glLinkProgram(shaderProgram);

	// Delete the now useless Vertex and Fragment Shader objects
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);



	// Vertices coordinates
	GLfloat vertices[] =
	{
		-0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f, // Lower left corner
		0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f, // Lower right corner
		0.0f, 0.5f * float(sqrt(3)) * 2 / 3, 0.0f // Upper corner
	};



   


	// Create reference containers for the Vartex Array Object and the Vertex Buffer Object
	GLuint VAO, VBO;

	// Generate the VAO and VBO with only 1 object each
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);

	// Make the VAO the current Vertex Array Object by binding it
	glBindVertexArray(VAO);

	// Bind the VBO specifying it's a GL_ARRAY_BUFFER
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	// Introduce the vertices into the VBO
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	// Configure the Vertex Attribute so that OpenGL knows how to read the VBO
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	// Enable the Vertex Attribute so that OpenGL knows to use it
	glEnableVertexAttribArray(0);

	// Bind both the VBO and VAO to 0 so that we don't accidentally modify the VAO and VBO we created
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	// Initialize ImGUI
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	ImGui::StyleColorsDark();
	ImGui_ImplGlfw_InitForOpenGL(window, true);
	ImGui_ImplOpenGL3_Init("#version 330");


	SetupMyImGuiStyle();
	SaveThisStyle("test.imstyle");

	SetupMyImGuiStyle(18, false);
	SaveThisStyle("test2.imstyle");

	//test
	ImVec4 *colors = ImGui::GetStyle().Colors;
	//colors[ImGuiCol_WindowBg].w = 0.7f;
	//colors[ImGuiCol_ChildBg].w = 0.55f;
    /*colors[ImGuiCol_ChildBg] = ImVec4(0.00f, 0.00f, 0.00f, 0.20f);*/
	
	static ImGuiWindowFlags flags = ImGuiWindowFlags_NoMove;
	
	// | ImGuiWindowFlags_NoResize;

	
	// Variables to be changed in the ImGUI window
	bool drawTriangle = true;
	float size = 1.0f;
	float color[4] = { 0.8f, 0.3f, 0.02f, 1.0f };

	// Exporting variables to shaders
	glUseProgram(shaderProgram);
	glUniform1f(glGetUniformLocation(shaderProgram, "size"), size);
	glUniform4f(glGetUniformLocation(shaderProgram, "color"), color[0], color[1], color[2], color[3]);
	
	
	ImGuiIO& io2 = ImGui::GetIO();

    //../res/fonts/ -> is font folder
    std::string luckiestguyPath = "../res/fonts/LuckiestGuy.ttf";
	std::string thinFontPath = "../res/fonts/RobotoSerif/RobotoSerif-Thin.ttf";
	string fontawesomePath = "../res/fonts/FA6.ttf";
	// Or create your own custom ranges (e.g. for a game you can feed your entire game script and only build the characters the game need)

	builder.AddText("ůěščřžňďťýáíúóéŮĚŠČŘŽŇĎŤÝÁÍÚÓÉ");                        // Add a string (here "Hello world" contains 7 unique characters)
	//builder.AddChar(0x7262);                               // Add a specific character
	builder.AddRanges(io2.Fonts->GetGlyphRangesJapanese()); // Add one of the default ranges
	builder.AddRanges(io2.Fonts->GetGlyphRangesChineseFull());
	builder.BuildRanges(&ranges);                          // Build the final result (ordered ranges with all the unique characters submitted)
	
	//sizes:
	// - title (h1)
	// - subtitle (h2)
	// - subsubtitle (h3)
	// - subsubsubtitle (h4)
	// - subsubsubsubtitle (h5)
	// - text (p)

	//types:
	// - thin
	// - light (similar to light but slightli towards to gray)
	// - regular
	// - medium (between regular and bold) 
	// - bold
	// - black (bolder than bold)

	//adder:
	// - italic

	//combinations:
	// - italic + bold
	// - italic + thin
	// - italic + light
	// - italic + medium
	// - italic + regular
	// - italic + black 

	ImFont* textfont = io2.Fonts->AddFontFromFileTTF(thinFontPath.c_str(), 16.0f, NULL, ranges.Data);
	ImFont* titlefont = io2.Fonts->AddFontFromFileTTF(thinFontPath.c_str(), 35.0f, NULL, ranges.Data);

	//     0     ,       1     ,       2    ,       3
	//normal text, normal title, italic text, italic title
	//y position - > what font(thin, regular, medium,...)
	//x position - > +1 (text) +0 (title) +2(italic)
	ImFont* fonts[6][4] = {
		/*0*/{LoadRoboto(io2, "Thin", 1), LoadRoboto(io2, "Thin", 0),LoadRoboto(io2, "ThinItalic", 1), LoadRoboto(io2, "ThinItalic", 0)},
		/*1*/{LoadRoboto(io2, "Light", 1), LoadRoboto(io2, "Light", 0),LoadRoboto(io2, "LightItalic", 1), LoadRoboto(io2, "LightItalic", 0)},
		/*2*/{LoadRoboto(io2, "Regular", 1), LoadRoboto(io2, "Regular", 0),LoadRoboto(io2, "RegularItalic", 1), LoadRoboto(io2, "RegularItalic", 0)},
		/*3*/{LoadRoboto(io2, "Medium", 1), LoadRoboto(io2, "Medium", 0),LoadRoboto(io2, "MediumItalic", 1), LoadRoboto(io2, "MediumItalic", 0)},
		/*4*/{LoadRoboto(io2, "Bold", 1), LoadRoboto(io2, "Bold", 0),LoadRoboto(io2, "BoldItalic", 1), LoadRoboto(io2, "BoldItalic", 0)},
		/*5*/{LoadRoboto(io2, "Black", 1), LoadRoboto(io2, "Black", 0),LoadRoboto(io2, "BlackItalic", 1), LoadRoboto(io2, "BlackItalic", 0)},
	};

	string path = "../lesson1.xml";
 	Lesson testlesson(path, titlefont, textfont);

	int titlex = 1;//title
	int titley = 3;//medium
	ImFont* myTitleFont = fonts[titley][titlex];

	ImFontConfig config;
	config.MergeMode = true;
	config.GlyphMinAdvanceX = 13.0f; // Use if you want to make the icon monospaced
	ImVector<ImWchar> ranges2;
	ImFontGlyphRangesBuilder builder2;
	static const ImWchar icon_ranges[] = { ICON_MIN_FA, ICON_MAX_FA, 0 };

	builder.AddRanges(icon_ranges);
	string add_text = ICON_FA_SEARCH;
	builder2.AddText(add_text.c_str());
	builder2.AddText("\uF115\uF044");
	builder2.AddText("\uF043\uF042");
	builder2.BuildRanges(&ranges2);
	
	ImFont* myIconFont = io2.Fonts->AddFontFromFileTTF(fontawesomePath.c_str(), 13.0f, &config, ranges2.Data);
	
	int *curr_item = new int(0), *curr_item2 = new int(0);
	const char* items = "Italic\0Normal", *items2 = "Thin\0Light\0Regular\0Medium\0Bold\0Black\0";

	static char text[1024 * 16] ="Sem můžete vložit nějaký text.\n může být i několikařádkový.\nDalší text...";

	//ImGuiWindowFlags window_flags = 0;
	//window_flags |= ImGuiWindowFlags_NoCollapse;




	lesson_data sample_data;

	ImConsole test;
	test.print("hi");
	test.print(5);


	//window flags
	int wwidth=0, wheight=0;
	ImGuiWindowFlags wflags =0;
	wflags |= ImGuiWindowFlags_NoMove;
	wflags |= ImGuiWindowFlags_NoTitleBar;
	wflags |= ImGuiWindowFlags_NoScrollbar;

	ImGuiWindowFlags wflags2 =0;
	wflags2 |= ImGuiWindowFlags_NoMove;
	wflags2 |= ImGuiWindowFlags_NoTitleBar;
	wflags2 |= ImGuiWindowFlags_NoScrollbar;

	ImFont* jmeno = LoadRoboto2(io2, "Bold", 21.0f), *ucet= LoadRoboto2(io2, "Medium", 14.0f), *datum= LoadRoboto2(io2, "Regular", 16.0f);

	ImVec4 norm = {0.7,0.5,0.0, 1.0f}, hov = {0.8,0.6,0.1, 1.0f};

	ImTexture con("../res/img/connect.png"), done("../res/img/done.png"), trash("../res/img/trash.png"), refresh("../res/img/refresh.png");
	ImTexture undo("../res/img/undo2.png"), teams("../res/img/teams.png"), spotify("../res/img/spotify.png"), google("../res/img/google.png");
	ImTexture tools("../res/img/tools.png"), settings("../res/img/settings.png"), bakalari("../res/img/bakalari.png"), account("../res/img/account.png");
	ImTexture backg("../res/img/background.jpg"), spotify2("../res/img/spotify2.png");
	ImTexture spotifydown("../res/img/spotifydown.png"), youtubedown("../res/img/youtubedown.jpeg"), deepl("../res/img/deepl.png");
	ImTexture bg("../res/img/lights.png");


	bool is_account_hovered = false;

	/*
	0 - main
	1- settings
	2 - connect
	3 - tools
	4 - bakalari
	5 - spotify
	6 - my account
	7 - deepl translate
	8 - spotify downloader
	9 - youtube downloader
	10 - convertor
	
	*/
	int show_menu_part = 0;


	BakalariUser ja;
	ja.Login("070401zvcj", "Pomezi77");
	TimeTable actimetable = ja.GetActTimeTable2("actimetable.json", "2022-10-14");
	int maxtimetablesize = MaxWTable(actimetable)-1;

	const char *dny[7] = {
					"Pondělí",
					"Úterý",
					"Středa",
					"Čtvrtek",
					"Pátek",
					"Sobota",
					"Neděle",
				};

	char yt_video[64] = " ", sp_pisen[128]=" ";


	

	// Main while loop
	while (!glfwWindowShouldClose(window))
	{	
		// Specify the color of the background
		glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
		// Clean the back buffer and assign the new color to it
		glClear(GL_COLOR_BUFFER_BIT);

		// Tell OpenGL a new frame is about to begin
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();

		glfwGetWindowSize(window, &wwidth, &wheight);

		//test
		ImGui::GetBackgroundDrawList()->AddImage((void *)(intptr_t)backg.GetID(), ImVec2(0,0), ImVec2(wwidth,wwidth));
		//rgba(0, 0, 28, 1)
		ImGui::GetStyle().Colors[ImGuiCol_WindowBg] = ImVec4(0,0,0.109,0);
		ImGui::GetStyle().Colors[ImGuiCol_ChildBg] = ImVec4(0,0,0.109,0);
		ImGui::GetStyle().Colors[ImGuiCol_Button] = ImVec4(0,0,0.109,255);
		ImGui::GetStyle().Colors[ImGuiCol_ButtonHovered] = ImVec4(0,0,0.109,255);
		ImGui::GetStyle().FrameRounding = 10.0f;
				//ImGui::PushStyleVar(ImGuiStyleVar_ChildRounding, ImVec2(5,5));
		//ImGuiCol_ChildBg
		if (*show_main_menu)
		{

			//main menu

			ImGui::SetNextWindowPos(ImVec2(0, 0));
			ImGui::SetNextWindowSize(ImVec2(wwidth, wheight));

			ImGui::Begin("main_menu", show_main_menu, wflags);


			//drawing the menu
			ImDrawList *drawlist = ImGui::GetForegroundDrawList(), *drawlist2 = ImGui::GetBackgroundDrawList();

			
			drawlist2->AddImage((void *)(intptr_t)bg.GetID(), ImVec2(0,0), ImVec2(1370,700));

			ImGui::SetNextWindowPos(ImVec2(0, 0));
			ImGui::SetNextWindowSize(ImVec2(wwidth+20, 90));
			ImGui::BeginChild("panel", ImVec2(wwidth+20, 90), true);
			
			ImVec2 vMin = ImGui::GetWindowContentRegionMin(); // left up corner
			ImVec2 vMax = ImGui::GetWindowContentRegionMax(); // right down corner
			vMin.x += ImGui::GetWindowPos().x;
			vMin.y += ImGui::GetWindowPos().y;
			vMax.x += ImGui::GetWindowPos().x;
			vMax.y += ImGui::GetWindowPos().y;
			//ImGui::GetForegroundDrawList()->AddRect(vMin, vMax, IM_COL32(255, 255, 0, 255));
			ImVec4 col = ImGui::GetStyle().Colors[ImGuiCol_FrameBg];
			col.x -= 0.1;
			col.y -= 0.1;
			col.z -= 0.1;
			const ImU32 color = ImColor(col);
			ImVec2 p1 = vMax;
			p1.x = 5;
			vMax.x = vMax.x - 25;
			p1.y = p1.y - 13;
			vMax.y = vMax.y - 13;

			ImVec2 ac_image_leftup =ImVec2(wwidth-55, 10), ac_image_rightdown = ImVec2((wwidth-55 )+50, 10+50);

			//drawlist->AddLine(p1,vMax, IM_COL32(255, 255, 0, 255));//zluta cara
			//rgba(0,0,28,255)
			drawlist2->AddRectFilled(ImVec2(0,0), ImVec2(wwidth, 72), IM_COL32(0,0,28,255));
			drawlist->AddImage((void *)(intptr_t)account.GetID(),ac_image_leftup, ac_image_rightdown );
			ImGui::PushFont(jmeno);
			drawlist->AddText(ImVec2(wwidth-145+10, 10+10), IM_COL32(255,255,255,255), "Mitáš Vít");
			ImGui::PopFont();
			ImGui::PushFont(ucet);
			drawlist->AddText(ImVec2(wwidth-145+10, 30+10), IM_COL32(255,255,255,255), "Můj účet");
			ImGui::PopFont();
				/*ImGui::SetNextWindowPos(ImVec2(wwidth-55, 10));
				ImGui::BeginChild(1, ImVec2(50, 50), false, wflags2);
				if (ImGui::ImageButton((void *)(intptr_t)account.GetID(), ImVec2(42, 42)))
				{
					//po kliknuti na ikonu uctu
				}
				ImGui::EndChild();
				ImGui::SetNextWindowPos(ImVec2(wwidth-145, 10));
				ImGui::BeginChild(18, ImVec2(90, 60), false, wflags2);
				ImGui::PushFont(jmeno);
				ImGui::Text("Mitáš Vít");
				ImGui::PopFont();
				ImGui::PushFont(ucet);
				//ImGui::SliderFloat("w", &colors[ImGuiCol_WindowBg].w, 0.0, 1.1);
				if(is_account_hovered){
					ImGui::TextColored(hov, "Můj účet");
				}else{
					ImGui::TextColored(norm, "Můj účet");
				}
				is_account_hovered = ImGui::IsItemHovered();
				if(is_account_hovered)
        		{
            		if(ImGui::IsMouseReleased( 0 ))
            		{
						//kliknuti na muj ucet
						show_menu_part = 6;
					}
				}
				ImGui::PopFont();
				ImGui::EndChild();*/
			ImGui::EndChild();



			//variables for computing

			int x=20, y=80, w = 80, h=560;
			double cursor_x = 0, cursor_y = 0; 

			ImVec2 image_leftup = ImVec2(x+8,53+y+20), image_rightdown = ImVec2(x+72,117+y+20);
			int image_width = (image_rightdown.x - image_leftup.x), image_height = (image_rightdown.y - image_leftup.y);
			
			ImVec2 bak_leftup = ImVec2(x+8,137+y+20), bak_rightdown = ImVec2(x+72,201+y+20);
			int bak_width = (bak_rightdown.x - bak_leftup.x), bak_height = (bak_rightdown.y - bak_leftup.y);

			ImVec2 ac_left_up = ImVec2(wwidth-145+10, 30+10), ac_rightdown = ImVec2(wwidth-145+10+30, 30+10+50);

			ImGui::PushFont(datum);

			time_t currentTime;
  			struct tm *localTime;

  			time( &currentTime );
  			localTime = localtime( &currentTime );

			string time1 = to_string(localTime->tm_hour) + ":" + to_string(localTime->tm_min);
			string time2 = to_string(localTime->tm_mday) + ". " + to_string(localTime->tm_mon)+ ". " + to_string(localTime->tm_year-100);

			drawlist->AddRectFilled(ImVec2(x,y), ImVec2(x+w, y+h), IM_COL32(0,0,28,255), 20.f);
			drawlist->AddText(ImVec2(x+23,18+y), IM_COL32(255,255,255,255), time1.c_str());//19:11
			drawlist->AddText(ImVec2(x+10,35+y), IM_COL32(255,255,255,255), time2.c_str());//21. 10. 2022
			drawlist->AddImage((void *)(intptr_t)spotify2.GetID(), image_leftup, image_rightdown);
			drawlist->AddImage((void *)(intptr_t)bakalari.GetID(), bak_leftup, bak_rightdown);

			glfwGetCursorPos(window, &cursor_x, &cursor_y);

			string c = "x: " + to_string(cursor_x) + "- y: " + to_string(cursor_y);
			drawlist->AddText(ImVec2(500, 0), IM_COL32(255,255,255,255), c.c_str());

			//menu buttons -> hovers + clicks
			if(((cursor_x >= image_leftup.x) && (cursor_y >= image_leftup.y))
			 && ((cursor_x <= image_rightdown.x) && (cursor_y <= image_rightdown.y)))
			 {
				//spotify button hover
				if(ImGui::IsMouseClicked(ImGuiMouseButton_Left)){
					//spotify button click
					show_menu_part = 5;
				}
				drawlist->AddCircle(ImVec2((image_leftup.x + image_width/2), (image_leftup.y+ image_height/2)), image_width/2, IM_COL32(255,0,0,255));
			}else if(((cursor_x >= bak_leftup.x) && (cursor_y >= bak_leftup.y))
			 && ((cursor_x <= bak_rightdown.x) && (cursor_y <= bak_rightdown.y)))
			 {
				//bakalari button hover
				if(ImGui::IsMouseClicked(ImGuiMouseButton_Left)){
					//bakalari button click
					show_menu_part = 4;
				}
				drawlist->AddCircle(ImVec2((bak_leftup.x + bak_width/2), (bak_leftup.y+ bak_height/2)), bak_width/2, IM_COL32(255,0,0,255));
			}else if(((cursor_x >= ac_left_up.x) && (cursor_y >= ac_left_up.y))
			 && ((cursor_x <= ac_rightdown.x) && (cursor_y <= ac_rightdown.y)))
			 {
				//account text
				//poc. pos: wwidth-145+10, 30+10
				//height: +-14
				ImGui::PushFont(ucet);
				drawlist->AddText(ImVec2(wwidth-145+10, 30+10), IM_COL32(255,0,0,255), "Můj účet");
				ImGui::PopFont();
				if(ImGui::IsMouseClicked(ImGuiMouseButton_Left)){
					//bakalari button click
					show_menu_part = 6;
				}
				
			}
			else if(((cursor_x >= ac_image_leftup.x) && (cursor_y >= ac_image_leftup.y))
			 && ((cursor_x <= ac_image_rightdown.x) && (cursor_y <= ac_image_rightdown.y)))
			{
				//account image
			 	if(ImGui::IsMouseClicked(ImGuiMouseButton_Left)){
					//bakalari button click
					show_menu_part = 6;
				}
			}

			ImGui::PopFont();

			/*ImGui::SetNextWindowPos(ImVec2(0, 75));
			ImGui::SetNextWindowSize(ImVec2(300, wheight));
			ImGui::BeginChild("Menu2", ImVec2(300, wheight), true);
			if (ImGui::BeginTable("split", 2, ImGuiTableFlags_BordersOuter | ImGuiTableFlags_Resizable))
    		{
            	//ShowPlaceholderObject("Menu");
            	//ImGui::Separator();
        		ImGui::EndTable();
    		}
			ImGui::EndChild();*/
			
			if (show_menu_part == 0)
			{
				//hlavni

				ImGui::SetNextWindowPos(ImVec2(500, 400));
				ImGui::BeginChild(1, ImVec2(200, 200), false, wflags2);
				if (ImGui::ImageButton((void *)(intptr_t)settings.GetID(), ImVec2(190, 190)))
				{
					show_menu_part = 1;
				}
				ImGui::EndChild();

				ImGui::SetNextWindowPos(ImVec2(500, 610));
				ImGui::BeginChild(2, ImVec2(200, 50), false, wflags2);
				ImGui::Text("Settings");
				ImGui::EndChild();

				ImGui::SetNextWindowPos(ImVec2(500, 100));
				ImGui::BeginChild(3, ImVec2(200, 200), false, wflags2);
				if (ImGui::ImageButton((void *)(intptr_t)tools.GetID(), ImVec2(190, 190)))
				{
					show_menu_part = 3;
				}
				ImGui::EndChild();

				ImGui::SetNextWindowPos(ImVec2(500, 310));
				ImGui::BeginChild(4, ImVec2(200, 50), false, wflags2);
				ImGui::Text("Nástroje");
				ImGui::EndChild();


				ImGui::SetNextWindowPos(ImVec2(800, 100));
				ImGui::BeginChild(5, ImVec2(200, 200), false, wflags2);
				if (ImGui::ImageButton((void *)(intptr_t)refresh.GetID(), ImVec2(190, 190)))
				{
					test.print("jo3");
					*show_main_menu = false;
					*show_text_editor = true;
				}
				ImGui::EndChild();

				ImGui::SetNextWindowPos(ImVec2(800, 310));
				ImGui::BeginChild(6, ImVec2(200, 50), false, wflags2);
				ImGui::Text("Refresh");
				ImGui::EndChild();

				ImGui::SetNextWindowPos(ImVec2(800, 400));
				ImGui::BeginChild(7, ImVec2(200, 200), false, wflags2);
				if (ImGui::ImageButton((void *)(intptr_t)con.GetID(), ImVec2(190, 190)))
				{
					test.print("propojeni");
					show_menu_part = 2;
				}
				ImGui::EndChild();

				ImGui::SetNextWindowPos(ImVec2(800, 610));
				ImGui::BeginChild(8, ImVec2(200, 50), false, wflags2);
				ImGui::Text("Propojení");
				ImGui::EndChild();
			}
			else if(show_menu_part == 2)
			{ 
				//propojeni
				ShowButtonChild2(ImVec2(500, 100), undo, "Zpět",9, &show_menu_part, 0);
				ImGui::SetNextWindowPos(ImVec2(500, 400));
				ImGui::BeginChild(10, ImVec2(200, 200), false, wflags2);
				if (ImGui::ImageButton((void *)(intptr_t)spotify.GetID(), ImVec2(190, 190)))
				{
					test.print("spotiufy");
					show_menu_part = 5;
				}
				ImGui::EndChild();

				ImGui::SetNextWindowPos(ImVec2(500, 610));
				ImGui::BeginChild(11, ImVec2(200, 50), false, wflags2);
				ImGui::Text("Spotify");
				ImGui::EndChild();

				ImGui::SetNextWindowPos(ImVec2(800, 100));
				ImGui::BeginChild(12, ImVec2(200, 200), false, wflags2);
				if (ImGui::ImageButton((void *)(intptr_t)bakalari.GetID(), ImVec2(190, 190)))
				{
					test.print("Bakaláři");
					show_menu_part = 4;
				}
				ImGui::EndChild();

				ImGui::SetNextWindowPos(ImVec2(800, 310));
				ImGui::BeginChild(13, ImVec2(200, 50), false, wflags2);
				ImGui::Text("Bakaláři");
				ImGui::EndChild();

				ImGui::SetNextWindowPos(ImVec2(800, 400));
				ImGui::BeginChild(14, ImVec2(200, 200), false, wflags2);
				if (ImGui::ImageButton((void *)(intptr_t)teams.GetID(), ImVec2(190, 190)))
				{
					test.print("teams");
				}
				ImGui::EndChild();

				ImGui::SetNextWindowPos(ImVec2(800, 610));
				ImGui::BeginChild(15, ImVec2(200, 50), false, wflags2);
				ImGui::Text("Teams");
				ImGui::EndChild();
				
			}
			else if(show_menu_part == 3)
			{
				//tools
				/*
					7 - deepl translate
					8 - spotify downloader
					9 - youtube downloader
					10 - convertor
				*/
				ShowButtonChild2(ImVec2(500, 100), undo, "Zpět",16, &show_menu_part, 0);

				ImGui::SetNextWindowPos(ImVec2(500, 400));
				ImGui::BeginChild(17, ImVec2(200, 200), false, wflags2);
				if (ImGui::ImageButton((void *)(intptr_t)deepl.GetID(), ImVec2(190, 190)))
				{
					show_menu_part = 7;
				}
				ImGui::EndChild();

				ImGui::SetNextWindowPos(ImVec2(500, 610));
				ImGui::BeginChild(18, ImVec2(200, 50), false, wflags2);
				ImGui::Text("DeepL Translator");
				ImGui::EndChild();

				ImGui::SetNextWindowPos(ImVec2(800, 100));
				ImGui::BeginChild(19, ImVec2(200, 200), false, wflags2);
				if (ImGui::ImageButton((void *)(intptr_t)youtubedown.GetID(), ImVec2(190, 190)))
				{
					show_menu_part = 9;
				}
				ImGui::EndChild();

				ImGui::SetNextWindowPos(ImVec2(800, 310));
				ImGui::BeginChild(20, ImVec2(200, 50), false, wflags2);
				ImGui::Text("YouTube Donwloader");
				ImGui::EndChild();

				ImGui::SetNextWindowPos(ImVec2(800, 400));
				ImGui::BeginChild(21, ImVec2(200, 200), false, wflags2);
				if (ImGui::ImageButton((void *)(intptr_t)spotifydown.GetID(), ImVec2(190, 190)))
				{
					show_menu_part = 8;
				}
				ImGui::EndChild();

				ImGui::SetNextWindowPos(ImVec2(800, 610));
				ImGui::BeginChild(22, ImVec2(200, 50), false, wflags2);
				ImGui::Text("Spotify Downloader");
				ImGui::EndChild();
			}
			else if(show_menu_part == 1)
			{
				//settings
				ShowButtonChild2(ImVec2(500, 100), undo, "Nastavení Zpět",23, &show_menu_part, 0);
			}
			else if(show_menu_part == 4)
			{
				//bakalari
				//ShowButtonChild2(ImVec2(500, 100), undo, "Zpět",18, &show_menu_part, 2);
				ImGui::SetNextWindowPos(ImVec2(300, 100));
				ImGui::BeginChild(24, ImVec2(800, 500), false, wflags2);
				drawlist->AddRect(ImVec2(300,100), ImVec2(1100, 600),IM_COL32(0,255,255,255));
				for(int i = 1; i < (maxtimetablesize+1); i++){
					//cary od shora dolu
					drawlist->AddLine(ImVec2(i*(800/maxtimetablesize)+300, 100), ImVec2(i*(800/maxtimetablesize)+300,600), IM_COL32(255,255,255,255));
					//i*(800/maxtimetablesize)+300, 100)
					
				}
				
				for(int y =1; y < 7; y++){
					//cary od leva do prava
					drawlist->AddLine(ImVec2(300,(y*(100))+ 100), ImVec2(1100, (y*(100))+ 100), IM_COL32(255,255,255,255));
				}
				for(int y = 1; y < 6; y++){
					drawlist->AddText(ImVec2(240,(y*(100))+45), IM_COL32(255,255,255,255), dny[y-1]);
				}
				for(int x =1; x < (maxtimetablesize+1);x++){
					for(int y=1;y < 6;y++){
						if(!actimetable.lessons[y-1][x-1].is_empty){
							drawlist->AddText(ImVec2(x*(800/maxtimetablesize)+250, (y*(100))+ 45), IM_COL32(255,255,255,255), actimetable.lessons[y-1][x-1].subjectabbrev.c_str());
							drawlist->AddText(ImVec2(x*(800/maxtimetablesize)+220, (y*(100))+ 15), IM_COL32(255,255,255,255), actimetable.lessons[y-1][x-1].groupabbrev.c_str());
							drawlist->AddText(ImVec2(x*(800/maxtimetablesize)+270, (y*(100))+ 15), IM_COL32(255,255,255,255), actimetable.lessons[y-1][x-1].roomabbrev.c_str());
							drawlist->AddText(ImVec2(x*(800/maxtimetablesize)+250, (y*(100)) + 45+40), IM_COL32(255,255,255,255),actimetable.lessons[y-1][x-1].teacherabbrev.c_str());
							//actimetable.lessons[y-1][x-1].teacherabbrev.c_str()
						}
					}
				}
				//ImGui::TextWrapped("zde bude prihlasovaci menu (podle promene signed), pak tlacitka na rozvrh, znamky, ucitele, ukoly,..");
				ImGui::EndChild();

			}
			else if(show_menu_part == 5)
			{
				//spotify
				ShowButtonChild2(ImVec2(500, 100), undo, "Zpět",25, &show_menu_part, 2);
				ImGui::SetNextWindowPos(ImVec2(400, 400));
				ImGui::BeginChild(26, ImVec2(600, 400), false, wflags2);
				ImGui::TextWrapped("zde bude prihlasovaci menu (podle promene signed_spotify), pak tlacitka na pusteni hudby, nastveni playlistu...");
				ImGui::EndChild();

			}
			else if(show_menu_part == 6)
			{
				//muj ucet
				ShowButtonChild2(ImVec2(500, 100), undo, "Zpět",27, &show_menu_part, 0);
				ImGui::SetNextWindowPos(ImVec2(400, 400));
				ImGui::BeginChild(28, ImVec2(600, 400), false, wflags2);
				ImGui::PushFont(fonts[1][1]);
				ImGui::Text("Můj účet");
				ImGui::PopFont();
				ImGui::TextWrapped("zde bude nastveni a informace, prihlaseni uctu(meho vlastniho, bakalari, spotify, google)...");
				ImGui::EndChild();

			}
			else if(show_menu_part == 8){
				//youtube downloader
				ImGui::SetNextWindowPos(ImVec2(400, 400));
				ImGui::BeginChild(28, ImVec2(600, 400), false, wflags2);
				ImGui::Text("Stahovač Spotify hudby");
				ImGui::InputText("Odkaz na Spotify video: ", sp_pisen, 128);
				if(ImGui::Button("stáhnout")){
					SPDownload(sp_pisen);
				}
				ImGui::EndChild();
			}
			else if(show_menu_part == 9){
				//youtube downloader
				ImGui::SetNextWindowPos(ImVec2(400, 400));
				ImGui::BeginChild(28, ImVec2(600, 400), false, wflags2);
				ImGui::Text("Stahovač YouTube Videí");
				ImGui::InputText("Odkaz na YouTube video: ", yt_video, 64);
				if(ImGui::Button("stáhnout")){
					YTDownload(yt_video);
				}
				ImGui::EndChild();
			}
			ImGui::End();
		}

		/*ImGui::Begin("lolsuprise");
		ImGui::PushItemWidth(-ImGui::GetFontSize() * 15);
		ImDrawList *draw_list = ImGui::GetWindowDrawList();

		static ImVec4 colf = ImVec4(1.0f, 1.0f, 0.4f, 1.0f);
		const ImU32 col = ImColor(colf);
		ImVec2 vMin = ImGui::GetWindowContentRegionMin(); // left up corner
		ImVec2 vMax = ImGui::GetWindowContentRegionMax(); // right down corner
		vMin.x += ImGui::GetWindowPos().x;
		vMin.y += ImGui::GetWindowPos().y;
		vMax.x += ImGui::GetWindowPos().x;
		vMax.y += ImGui::GetWindowPos().y;
		// size, spacing, x, y, num of sides, thikness
		float set[6] = {300.f, 10.f, (vMin.x), (vMin.x), 6.f, 2.15f};
		draw_list->AddNgon(ImVec2(set[2] + set[0] * 0.5f, set[2] + set[0] * 0.5f), set[0] * 0.5f, col, set[4], set[5]);
		ImGui::GetForegroundDrawList()->AddRect(vMin, vMax, IM_COL32(255, 255, 0, 255));
		ImGui::Dummy(ImVec2((set[0] + set[1]) * 10.2f, (set[0] + set[1]) * 3.0f));
		ImGui::PopItemWidth();

		ImGui::End();*/

		if (*show_main)
		{
			ShowLesson(show_main, testlesson);
		}

		if (*show_testing)
		{
			ShowIconsFonts(show_testing, fonts, myTitleFont, myIconFont, &testlesson);
		}

		if (*test.opened)
		{
			test.DrawWindow();
		}

		if(*show_text_editor){
			ImGui::Begin("Text Editor", show_text_editor);
			ImGui::InputTextMultiline("##source", text, IM_ARRAYSIZE(text), ImVec2(-FLT_MIN, ImGui::GetTextLineHeight() * 16));
			if(ImGui::Combo("Font style ", curr_item, items)){
				ImGui::Text("Value chnaged");
			}

			ImGui::Combo("Font ", curr_item2, items2);
			ImGui::Text(to_string(*curr_item).c_str());

			ImGui::Separator();
			if(ImGui::Button("Save")){
				cout << "saving..." << endl;
				*show_form = true;
				cout << "copying data (text)" << endl;
				strcpy(sample_data.text, text);
				//cout << "generating date" << endl;
				//char *date = Date2Char();
				cout << "copying data (date)" << endl;
				//strcpy(sample_data.create_date, date);
				char date2[50] = "16.9.2022\0";
				strcpy(sample_data.create_date, date2);
				cout << "everything is copied -> showing form" << endl;
			}

			ImGui::End();
		}

		if(*show_form){
			cout << "showing form" << endl;
			ShowForm(show_form, &sample_data, &testlesson);
			cout << "author: " << testlesson.author.c_str() << endl;
		}


		// Export variables to shader
		glUseProgram(shaderProgram);
		glUniform1f(glGetUniformLocation(shaderProgram, "size"), size);
		glUniform4f(glGetUniformLocation(shaderProgram, "color"), color[0], color[1], color[2], color[3]);

		// Renders the ImGUI elements
		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
		
		// Swap the back buffer with the front buffer
		glfwSwapBuffers(window);
		// Take care of all GLFW events
		glfwPollEvents();
	}

	// Deletes all ImGUI instances
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();

	// Delete all the objects we've created
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteProgram(shaderProgram);
	// Delete window before ending the program
	glfwDestroyWindow(window);
	// Terminate GLFW before ending the program
	glfwTerminate();
	return 0;
}



ImFont* LoadRoboto(ImGuiIO io2, string type, bool size){
	cout << "Loading roboto font" << endl;
	string path = "../res/fonts/Roboto/Roboto-" + type + ".ttf"; 
	//cout << endl << "loading: " << path << endl;
	if(size){
		//cout << endl << "loading text sized font" <<  endl;
		return io2.Fonts->AddFontFromFileTTF(path.c_str(), 16.0f, NULL, ranges.Data);
	}
	//cout << endl << "loading title sized font" <<  endl;
	return io2.Fonts->AddFontFromFileTTF(path.c_str(), 35.0f, NULL, ranges.Data);	
}

ImFont* LoadRoboto2(ImGuiIO io2, string type, float size){
	cout << "Loading roboto font" << endl;
	string path = "../res/fonts/Roboto/Roboto-" + type + ".ttf"; 
	//cout << endl << "loading: " << path << endl;
	return io2.Fonts->AddFontFromFileTTF(path.c_str(), size, NULL, ranges.Data);
}


void ShowLesson(bool *p_open, Lesson testlesson)
{
	cout << "Showing lesson" << endl;
	if(!ImGui::Begin(testlesson.title.c_str(), p_open))
    {
        ImGui::End();
    } 
    else
    {
        testlesson.Draw();  
        ImGui::End();
    }
}


void ShowForm(bool *p_open, lesson_data * data, Lesson* thislesson){
	cout << "Showing form" << endl;
	if(!ImGui::Begin("Create a lesson form", p_open))
    {
        ImGui::End();
    } 
    else
    {
		ImGui::InputText("Author: ", data->author, 32);
		ImGui::InputText("Subject: ", data->subject, 16);
		ImGui::InputText("Title: ", data->title, 48);
		if(ImGui::Button("Done")){
			cout << "Done" << endl;
			cout << "LessonData2Lesson" << endl;
			LessonData2Lesson(data, thislesson);
			cout << "thislesson->SaveToFile(\"test.xml\");" << endl;
			thislesson->SaveToFile("test.xml");
			*p_open = false;
		}
        ImGui::End();
    }
	
}

void ShowIconsFonts(bool *p_open, ImFont* fonts[6][4], ImFont* titlefont, ImFont* iconfont, Lesson* les){
	if(!ImGui::Begin("Iam begin", p_open))
    {
        ImGui::End();
    } 
    else
    {
        // na ikony potrebujeme nacist font awesome .otf + zmenit ranges
		//ImGui::Button(ICON_FA_SEARCH, ImVec2(4,4));
		//ImGui::Text("%s hledatko", ICON_FA_SEARCH);
		ImGui::InputText("path", path, IM_ARRAYSIZE(path));
		if(ImGui::Button("Save lesson to file")){
			les->SaveToFile(char2str(path));
		}
		for(int y = 0; y < 6; y++){
			for(int x = 0; x < 4;x++){
				ImGui::PushFont(fonts[y][x]);
				string text = to_string(y+x) + " (" + to_string(y)+ ", "+  to_string(x) +")";
				ImGui::Text(text.c_str());
				ImGui::PopFont();
			}
		}

		ImGui::PushFont(titlefont);
		ImGui::Text("my title font:");
		ImGui::TextWrapped("aábcčdďeěéfghchiíjklmnňoópqrřsštťuúůwxyýzžaábcčdďeěéfghchiíjklmnňoópqrřsštťuúůwxyýzž");
		ImGui::PopFont();
		

		ImGui::PushFont(iconfont);
		ImGui::Text("\uF115");
		ImGui::Button("\uF044");
		ImGui::Text("\uF044 hledatko");
		ImGui::PopFont();
        ImGui::End();
    }
}

void LessonData2Lesson(lesson_data* data, Lesson * lesson){
	/*char2str(data->author, &lesson->author);
	char2str(data->subject, &lesson->subject);
	char2str(data->create_date, &lesson->create_date);
	char2str(data->text, &lesson->text);
	char2str(data->title, &lesson->title);*/
	lesson->author = char2str(data->author);
	lesson->subject = char2str(data->subject);
	lesson->create_date = char2str(data->create_date);
	lesson->text = char2str(data->text);
	lesson->title = char2str(data->title);
	lesson->SaveToFile("test2.xml");
}

void ShowButtonChild(ImVec2 pos, ImTexture image, string text,int id){
	ImGuiWindowFlags wflags2 =0;
	wflags2 |= ImGuiWindowFlags_NoMove;
	wflags2 |= ImGuiWindowFlags_NoTitleBar;
	wflags2 |= ImGuiWindowFlags_NoScrollbar;
	ImGui::SetNextWindowPos(pos);
	ImGui::BeginChild(id, ImVec2(200, 200), false, wflags2);
	if (ImGui::ImageButton((void *)(intptr_t)image.GetID(), ImVec2(190, 190)))
	{
	}
	ImGui::EndChild();

	ImGui::SetNextWindowPos(ImVec2(pos.x, pos.y+10));
	ImGui::BeginChild(id+20, ImVec2(200, 50), false, wflags2);
	ImGui::Text(text.c_str());
	ImGui::EndChild();
}
void ShowButtonChild(ImVec2 pos, ImTexture image, string text,int id,bool* sh_set, bool *sh_con, bool *sh_tool){
	ImGuiWindowFlags wflags2 =0;
	wflags2 |= ImGuiWindowFlags_NoMove;
	wflags2 |= ImGuiWindowFlags_NoTitleBar;
	wflags2 |= ImGuiWindowFlags_NoScrollbar;
	ImGui::SetNextWindowPos(pos);
	ImGui::BeginChild(id, ImVec2(200, 200), false, wflags2);
	if (ImGui::ImageButton((void *)(intptr_t)image.GetID(), ImVec2(190, 190)))
	{
		*sh_con = false;
		*sh_set = false;
		*sh_tool = false;
	}
	ImGui::EndChild();

	ImGui::SetNextWindowPos(ImVec2(pos.x, pos.y+10));
	ImGui::BeginChild(id+20, ImVec2(200, 50), false, wflags2);
	ImGui::Text(text.c_str());
	ImGui::EndChild();
}

void ShowButtonChild2(ImVec2 pos, ImTexture image, string text,int id,int* menu_part, int go_to){
	ImGuiWindowFlags wflags2 =0;
	wflags2 |= ImGuiWindowFlags_NoMove;
	wflags2 |= ImGuiWindowFlags_NoTitleBar;
	wflags2 |= ImGuiWindowFlags_NoScrollbar;
	ImGui::SetNextWindowPos(pos);
	ImGui::BeginChild(id, ImVec2(200, 200), false, wflags2);
	if (ImGui::ImageButton((void *)(intptr_t)image.GetID(), ImVec2(190, 190)))
	{
		*menu_part = go_to;
	}
	ImGui::EndChild();

	ImGui::SetNextWindowPos(ImVec2(pos.x, pos.y+10));
	ImGui::BeginChild(id+40, ImVec2(200, 50), false, wflags2);
	ImGui::Text(text.c_str());
	ImGui::EndChild();
}

int MaxWTable(TimeTable &a){
	//5*15
	int max = 0;
	for(int y =0; y < 5;y++){
		int t = 0;
		for(int x = 0; x < 15; x++){
			if(!(a.lessons[y][x].is_empty)){
				t++;
			}
			else{
				if(!a.lessons[y][x+1].is_empty){
					t++;
				}
			}
		}
		if(t > max){
			max = t;
		}
	}
	return max;
}