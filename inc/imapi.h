#ifndef IMAPI_H
#define IMAPI_H

#include <imgui/imgui.h>
#include <imgui/imgui_impl_glfw.h>
#include <imgui/imgui_impl_opengl3.h>

#define STB_IMAGE_IMPLEMENTATION
#include <stb/stb_image.h>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <vector>
#include <ctime>
#include <math.h>

#include <inc/lesson.h>
#include <inc/imgui_style.h>

using namespace std;

template<typename T>
string Stringify(T var);

bool IsEmptyDir(string path);
int DirSize(string path);
int FileSize(string path);
string *ListDir(string path);

int Percent(int s, int from);
int Percent(ImVec2 s, ImVec2 from);
float Percent(float s, float from);
/*
class Window;
class ImWindow;
class ImConsole;
class ImObject;
class ImFont;
class ImImage;
class ImButton;
class Imtext;
class ImCombo;
class ImTreeView;
class ImPopup;
class ImWindowChild;

class Window{
public:
    ImVec2 size, position, mousepos;
    string name;
    Window(string _name, ImVec2 _size=ImVec2(300.f,300.f), ImVec2 _position=ImVec2(0.f,0.f));
};

typedef float (*showcallback)(ImWindow* win);

class ImWindow{
public:
    ImVec2 size, position;
    Window* parent;
    ImGuiWindowFlags flags;
    bool *opened;
    string name;
    ImWindow(string _name);
};


class ImConsole{
public:
    vector<string> history;
    bool *opened;
    ImConsole();
    void print(string s);
    template<typename T>
    void print(T t);
    void DrawWindow();
    void DrawContext();

};

class ImFont{
public: 
    int size;
    string path;
};

class ImObject{
public:
    ImWindow* parent;
    //bool dragable;
    bool hovered, disabled, clicked, visible, autops;//autops-automatic size and position
    ImVec2 position, size;
};
*/
/*
class ImConsole{
public:
    vector<string> history;
    bool *opened ;
    ImConsole(){
        opened = new bool(true);
    }
    void print(string s){
        history.push_back(s);
    }
    template<typename T>
    void print(T t){
        stringstream s;
        s << t;
        history.push_back(s.str());
    }
    void DrawWindow(){
        ImGui::Begin("Console", opened);
        for(int i =0; i < history.size();i++){
            ImGui::TextWrapped(history.at(i).c_str());
        }
        ImGui::End();
    }

};
*/
 
#endif