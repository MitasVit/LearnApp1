#ifndef IMGUI_STYLE
#define IMGUI_STYLE

#include <iostream>
#include <imgui/imgui.h>
#include <fstream>
#include <vector>
#include <sstream>

using namespace std;

struct ImVec3 { float x, y, z; ImVec3(float _x = 0.0f, float _y = 0.0f, float _z = 0.0f) { x = _x; y = _y; z = _z; } };

void imgui_easy_theming(ImVec3 color_for_text, ImVec3 color_for_head, ImVec3 color_for_area, ImVec3 color_for_body, ImVec3 color_for_pops)
{
    ImGuiStyle& style = ImGui::GetStyle();
    
    style.Colors[ImGuiCol_Text] = ImVec4( color_for_text.x, color_for_text.y, color_for_text.z, 1.00f );
    style.Colors[ImGuiCol_TextDisabled] = ImVec4( color_for_text.x, color_for_text.y, color_for_text.z, 0.58f );
    style.Colors[ImGuiCol_WindowBg] = ImVec4( color_for_body.x, color_for_body.y, color_for_body.z, 0.95f );
  //  style.Colors[ImGuiCol_ChildWindowBg] = ImVec4( color_for_area.x, color_for_area.y, color_for_area.z, 0.58f );
    style.Colors[ImGuiCol_Border] = ImVec4( color_for_body.x, color_for_body.y, color_for_body.z, 0.00f );
    style.Colors[ImGuiCol_BorderShadow] = ImVec4( color_for_body.x, color_for_body.y, color_for_body.z, 0.00f );
    style.Colors[ImGuiCol_FrameBg] = ImVec4( color_for_area.x, color_for_area.y, color_for_area.z, 1.00f );
    style.Colors[ImGuiCol_FrameBgHovered] = ImVec4( color_for_head.x, color_for_head.y, color_for_head.z, 0.78f );
    style.Colors[ImGuiCol_FrameBgActive] = ImVec4( color_for_head.x, color_for_head.y, color_for_head.z, 1.00f );
    style.Colors[ImGuiCol_TitleBg] = ImVec4( color_for_area.x, color_for_area.y, color_for_area.z, 1.00f );
    style.Colors[ImGuiCol_TitleBgCollapsed] = ImVec4( color_for_area.x, color_for_area.y, color_for_area.z, 0.75f );
    style.Colors[ImGuiCol_TitleBgActive] = ImVec4( color_for_head.x, color_for_head.y, color_for_head.z, 1.00f );
    style.Colors[ImGuiCol_MenuBarBg] = ImVec4( color_for_area.x, color_for_area.y, color_for_area.z, 0.47f );
    style.Colors[ImGuiCol_ScrollbarBg] = ImVec4( color_for_area.x, color_for_area.y, color_for_area.z, 1.00f );
    style.Colors[ImGuiCol_ScrollbarGrab] = ImVec4( color_for_head.x, color_for_head.y, color_for_head.z, 0.21f );
    style.Colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4( color_for_head.x, color_for_head.y, color_for_head.z, 0.78f );
    style.Colors[ImGuiCol_ScrollbarGrabActive] = ImVec4( color_for_head.x, color_for_head.y, color_for_head.z, 1.00f );
 //   style.Colors[ImGuiCol_ComboBg] = ImVec4( color_for_area.x, color_for_area.y, color_for_area.z, 1.00f );
    style.Colors[ImGuiCol_CheckMark] = ImVec4( color_for_head.x, color_for_head.y, color_for_head.z, 0.80f );
    style.Colors[ImGuiCol_SliderGrab] = ImVec4( color_for_head.x, color_for_head.y, color_for_head.z, 0.50f );
    style.Colors[ImGuiCol_SliderGrabActive] = ImVec4( color_for_head.x, color_for_head.y, color_for_head.z, 1.00f );
    style.Colors[ImGuiCol_Button] = ImVec4( color_for_head.x, color_for_head.y, color_for_head.z, 0.50f );
    style.Colors[ImGuiCol_ButtonHovered] = ImVec4( color_for_head.x, color_for_head.y, color_for_head.z, 0.86f );
    style.Colors[ImGuiCol_ButtonActive] = ImVec4( color_for_head.x, color_for_head.y, color_for_head.z, 1.00f );
    style.Colors[ImGuiCol_Header] = ImVec4( color_for_head.x, color_for_head.y, color_for_head.z, 0.76f );
    style.Colors[ImGuiCol_HeaderHovered] = ImVec4( color_for_head.x, color_for_head.y, color_for_head.z, 0.86f );
    style.Colors[ImGuiCol_HeaderActive] = ImVec4( color_for_head.x, color_for_head.y, color_for_head.z, 1.00f );
 //   style.Colors[ImGuiCol_Column] = ImVec4( color_for_head.x, color_for_head.y, color_for_head.z, 0.32f );
//    style.Colors[ImGuiCol_ColumnHovered] = ImVec4( color_for_head.x, color_for_head.y, color_for_head.z, 0.78f );
 //   style.Colors[ImGuiCol_ColumnActive] = ImVec4( color_for_head.x, color_for_head.y, color_for_head.z, 1.00f );
    style.Colors[ImGuiCol_ResizeGrip] = ImVec4( color_for_head.x, color_for_head.y, color_for_head.z, 0.15f );
    style.Colors[ImGuiCol_ResizeGripHovered] = ImVec4( color_for_head.x, color_for_head.y, color_for_head.z, 0.78f );
    style.Colors[ImGuiCol_ResizeGripActive] = ImVec4( color_for_head.x, color_for_head.y, color_for_head.z, 1.00f );
   // style.Colors[ImGuiCol_CloseButton] = ImVec4( color_for_text.x, color_for_text.y, color_for_text.z, 0.16f );
  //  style.Colors[ImGuiCol_CloseButtonHovered] = ImVec4( color_for_text.x, color_for_text.y, color_for_text.z, 0.39f );
  //  style.Colors[ImGuiCol_CloseButtonActive] = ImVec4( color_for_text.x, color_for_text.y, color_for_text.z, 1.00f );
    style.Colors[ImGuiCol_PlotLines] = ImVec4( color_for_text.x, color_for_text.y, color_for_text.z, 0.63f );
    style.Colors[ImGuiCol_PlotLinesHovered] = ImVec4( color_for_head.x, color_for_head.y, color_for_head.z, 1.00f );
    style.Colors[ImGuiCol_PlotHistogram] = ImVec4( color_for_text.x, color_for_text.y, color_for_text.z, 0.63f );
    style.Colors[ImGuiCol_PlotHistogramHovered] = ImVec4( color_for_head.x, color_for_head.y, color_for_head.z, 1.00f );
    style.Colors[ImGuiCol_TextSelectedBg] = ImVec4( color_for_head.x, color_for_head.y, color_for_head.z, 0.43f );
    style.Colors[ImGuiCol_PopupBg] = ImVec4( color_for_pops.x, color_for_pops.y, color_for_pops.z, 0.92f );
    //style.Colors[ImGuiCol_ModalWindowDarkening] = ImVec4( color_for_area.x, color_for_area.y, color_for_area.z, 0.73f );

}

void theming2()
{
    ImVec4 *colors = ImGui::GetStyle().Colors;
   colors[ImGuiCol_Text] = ImVec4(0.75f, 0.75f, 0.75f, 1.00f);
    colors[ImGuiCol_TextDisabled] = ImVec4(0.35f, 0.35f, 0.35f, 1.00f);
    colors[ImGuiCol_WindowBg] = ImVec4(0.00f, 0.00f, 0.00f, 0.94f);
    colors[ImGuiCol_ChildBg] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
    colors[ImGuiCol_PopupBg] = ImVec4(0.08f, 0.08f, 0.08f, 0.94f);
    colors[ImGuiCol_Border] = ImVec4(0.00f, 0.00f, 0.00f, 0.50f);
    colors[ImGuiCol_BorderShadow] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
   // colors[ImGuiCol_FrameBg] = ImVec4(0.36f, 0.37f,0.36f, 1.00f);
   colors[ImGuiCol_FrameBg] = ImVec4(0.0f, 0.0f,0.0f, 1.00f);
    colors[ImGuiCol_FrameBgHovered] = ImVec4(0.37f, 0.14f, 0.14f, 0.67f);
    colors[ImGuiCol_FrameBgActive] = ImVec4(0.39f, 0.20f, 0.20f, 0.67f);
    colors[ImGuiCol_TitleBg] = ImVec4(0.04f, 0.04f, 0.04f, 1.00f);
    colors[ImGuiCol_TitleBgActive] = ImVec4(0.48f, 0.16f, 0.16f, 1.00f);
    colors[ImGuiCol_TitleBgCollapsed] = ImVec4(0.48f, 0.16f, 0.16f, 1.00f);
    colors[ImGuiCol_MenuBarBg] = ImVec4(0.14f, 0.14f, 0.14f, 1.00f);
    colors[ImGuiCol_ScrollbarBg] = ImVec4(0.02f, 0.02f, 0.02f, 0.53f);
    colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.31f, 0.31f, 0.31f, 1.00f);
    colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.41f, 0.41f, 0.41f, 1.00f);
    colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.51f, 0.51f, 0.51f, 1.00f);
    colors[ImGuiCol_CheckMark] = ImVec4(0.56f, 0.10f, 0.10f, 1.00f);
    colors[ImGuiCol_SliderGrab] = ImVec4(1.00f, 0.19f, 0.19f, 0.40f);
    colors[ImGuiCol_SliderGrabActive] = ImVec4(0.89f, 0.00f, 0.19f, 1.00f);
    colors[ImGuiCol_Button] = ImVec4(1.00f, 0.19f, 0.19f, 0.40f);
    colors[ImGuiCol_ButtonHovered] = ImVec4(0.80f, 0.17f, 0.00f, 1.00f);
    colors[ImGuiCol_ButtonActive] = ImVec4(0.89f, 0.00f, 0.19f, 1.00f);
    colors[ImGuiCol_Header] = ImVec4(0.33f, 0.35f, 0.36f, 0.53f);
    colors[ImGuiCol_HeaderHovered] = ImVec4(0.76f, 0.28f, 0.44f, 0.67f);
    colors[ImGuiCol_HeaderActive] = ImVec4(0.47f, 0.47f, 0.47f, 0.67f);
    colors[ImGuiCol_Separator] = ImVec4(0.32f, 0.32f, 0.32f, 1.00f);
    colors[ImGuiCol_SeparatorHovered] = ImVec4(0.32f, 0.32f, 0.32f, 1.00f);
    colors[ImGuiCol_SeparatorActive] = ImVec4(0.32f, 0.32f, 0.32f, 1.00f);
    colors[ImGuiCol_ResizeGrip] = ImVec4(1.00f, 1.00f, 1.00f, 0.85f);
    colors[ImGuiCol_ResizeGripHovered] = ImVec4(1.00f, 1.00f, 1.00f, 0.60f);
    colors[ImGuiCol_ResizeGripActive] = ImVec4(1.00f, 1.00f, 1.00f, 0.90f);
    colors[ImGuiCol_Tab] = ImVec4(0.07f, 0.07f, 0.07f, 0.51f);
    colors[ImGuiCol_TabHovered] = ImVec4(0.86f, 0.23f, 0.43f, 0.67f);
    colors[ImGuiCol_TabActive] = ImVec4(0.19f, 0.19f, 0.19f, 0.57f);
    colors[ImGuiCol_TabUnfocused] = ImVec4(0.05f, 0.05f, 0.05f, 0.90f);
    colors[ImGuiCol_TabUnfocusedActive] = ImVec4(0.13f, 0.13f, 0.13f, 0.74f);
  //  colors[ImGuiCol_DockingPreview] = ImVec4(0.47f, 0.47f, 0.47f, 0.47f);
  //  colors[ImGuiCol_DockingEmptyBg] = ImVec4(0.20f, 0.20f, 0.20f, 1.00f);
    colors[ImGuiCol_PlotLines] = ImVec4(0.61f, 0.61f, 0.61f, 1.00f);
    colors[ImGuiCol_PlotLinesHovered] = ImVec4(1.00f, 0.43f, 0.35f, 1.00f);
    colors[ImGuiCol_PlotHistogram] = ImVec4(0.90f, 0.70f, 0.00f, 1.00f);
    colors[ImGuiCol_PlotHistogramHovered] = ImVec4(1.00f, 0.60f, 0.00f, 1.00f);
    colors[ImGuiCol_TableHeaderBg] = ImVec4(0.19f, 0.19f, 0.20f, 1.00f);
    colors[ImGuiCol_TableBorderStrong] = ImVec4(0.31f, 0.31f, 0.35f, 1.00f);
    colors[ImGuiCol_TableBorderLight] = ImVec4(0.23f, 0.23f, 0.25f, 1.00f);
    colors[ImGuiCol_TableRowBg] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
    colors[ImGuiCol_TableRowBgAlt] = ImVec4(1.00f, 1.00f, 1.00f, 0.07f);
    colors[ImGuiCol_TextSelectedBg] = ImVec4(0.26f, 0.59f, 0.98f, 0.35f);
    colors[ImGuiCol_DragDropTarget] = ImVec4(1.00f, 1.00f, 0.00f, 0.90f);
    colors[ImGuiCol_NavHighlight] = ImVec4(0.26f, 0.59f, 0.98f, 1.00f);
    colors[ImGuiCol_NavWindowingHighlight] = ImVec4(1.00f, 1.00f, 1.00f, 0.70f);
    colors[ImGuiCol_NavWindowingDimBg] = ImVec4(0.80f, 0.80f, 0.80f, 0.20f);
    colors[ImGuiCol_ModalWindowDimBg] = ImVec4(0.80f, 0.80f, 0.80f, 0.35f);
}

//setup imgui paddings/spacings/sizes/borders/aligments/rounding
//note: fontname is without font path -> it's setted automaticly
void imgui_main_styles_theming(/*std::string fontname = "LuckiestGuy.ttf", */float size_pixels = 10){
    ImGuiStyle& style = ImGui::GetStyle();
    //paddings/spacings/sizes
    style.WindowPadding     = ImVec2(8,8);
    style.FramePadding      = ImVec2(3,3);
    style.CellPadding       = ImVec2(3,3);
    style.ItemSpacing       = ImVec2(7,4);
    style.ItemInnerSpacing  = ImVec2(4,4);
    style.TouchExtraPadding = ImVec2(0,0);
    style.IndentSpacing     = 12.f;
    style.ScrollbarSize     = 11.f;
    style.GrabMinSize       = 8.f;

    //borders
    style.WindowBorderSize  = 1.f;
    style.ChildBorderSize   = 1.f;
    style.PopupBorderSize   = 1.f;
    style.FrameBorderSize   = 0.f;
    style.TabBorderSize     = 0.f;

    //rounding
    style.WindowRounding    = 7.5f;
    style.ChildRounding     = 7.5f;
    style.FrameRounding     = 7.5f;
    style.PopupRounding     = 7.5f;
    style.ScrollbarRounding = 10.f;
    style.GrabRounding      = 7.5f;
    style.LogSliderDeadzone = 4.f;
    style.TabRounding       = 7.5f;

    //aligment
    style.WindowTitleAlign         = ImVec2(0.5f,0.5f);
    style.ButtonTextAlign          = ImVec2(0.5f,0.5f);
    style.SelectableTextAlign      = ImVec2(0.5f,0.5f);
    style.WindowMenuButtonPosition = ImGuiDir_Right;
    style.ColorButtonPosition      = ImGuiDir_Right;
/*
    ImGuiIO& io = ImGui::GetIO();
    //../res/fonts/ -> is font folder
    io.Fonts->ClearFonts();
    std::string fontname_ful = "../res/fonts/" + fontname;
    io.Fonts->AddFontFromFileTTF(fontname_ful.c_str(), size_pixels);*/
}

//note: fontname is without font path -> it's setted automaticly
void set_imgui_font(std::string fontname, float size_pixels){
    ImGuiIO& io = ImGui::GetIO();
    //../res/fonts/ -> is font folder
    io.Fonts->ClearFonts();
    std::string fontname_ful = "../res/fonts/" + fontname;
    io.Fonts->AddFontFromFileTTF(fontname_ful.c_str(), size_pixels);
}

void SetupMyImGuiStyle(int font_size = 18, bool use_theme2 = true)
{
    static ImVec3 color_for_text = ImVec3(236.f / 255.f, 240.f / 255.f, 241.f / 255.f);
    static ImVec3 color_for_head = ImVec3(41.f / 255.f, 128.f / 255.f, 185.f / 255.f);
    static ImVec3 color_for_area = ImVec3(57.f / 255.f, 79.f / 255.f, 105.f / 255.f);
    static ImVec3 color_for_body = ImVec3(44.f / 255.f, 62.f / 255.f, 80.f / 255.f);
    static ImVec3 color_for_pops = ImVec3(33.f / 255.f, 46.f / 255.f, 60.f / 255.f);
    // imgui_main_styles_theming("SourceCodePro-Regular.ttf", 18);
    imgui_main_styles_theming(font_size);
    if(use_theme2){
        theming2();
    }else{
        imgui_easy_theming(color_for_text, color_for_head, color_for_area, color_for_body, color_for_pops);
    }
    //imgui_easy_theming(color_for_text, color_for_head, color_for_area, color_for_body, color_for_pops);
}

ofstream & operator<<(ofstream &s, ImVec2 &v){
    s << v.x << " " << v.y;
    return s;
}

ifstream & operator >>(ifstream &s, ImVec2 &v){
    s >> v.x ; s >> v.y;
    return s;
}

ofstream & operator<<(ofstream &s, ImVec3 &v){
    s << v.x << " " << v.y << " " << v.z;
    return s;
}

ifstream & operator >>(ifstream &s, ImVec3 &v){
    s >> v.x ; s >> v.y; s>> v.z;
    return s;
}

ofstream & operator<<(ofstream &s, ImVec4 &v){
    s << v.x << " " << v.y << " " << v.z << " " << v.w;
    return s;
}

ifstream & operator >>(ifstream &s, ImVec4 &v){
    s >> v.x ; s >> v.y; s>> v.z; s>> v.w;
    return s;
}

//saves styles + colors to path file
void SaveThisStyle(string path){
    ImGuiStyle& style = ImGui::GetStyle();
    ImVec4 *colors = ImGui::GetStyle().Colors;
    ofstream out(path.c_str());
    out << style.WindowPadding << " ";
    out << style.FramePadding << " ";
    out << style.CellPadding << " ";
    out << style.ItemSpacing << " ";
    out << style.ItemInnerSpacing << " ";
    out << style.TouchExtraPadding << " ";
    out << style.IndentSpacing << " ";
    out << style.ScrollbarSize << " ";
    out << style.GrabMinSize << " ";

    out << style.WindowBorderSize << " ";
    out << style.ChildBorderSize << " ";
    out << style.PopupBorderSize << " ";
    out << style.FrameBorderSize << " ";
    out << style.TabBorderSize << " ";

    out << style.WindowRounding << " ";
    out << style.ChildRounding << " ";
    out << style.FrameRounding << " ";
    out << style.PopupRounding << " ";
    out << style.ScrollbarRounding << " ";
    out << style.GrabRounding << " ";
    out << style.LogSliderDeadzone << " ";
    out << style.TabRounding << " ";

    out << style.WindowTitleAlign << " ";
    out << style.ButtonTextAlign << " ";
    out << style.SelectableTextAlign << " ";
    out << style.WindowMenuButtonPosition << " ";
    out << style.ColorButtonPosition << " ";


    out << colors[ImGuiCol_Text] << " ";
    out << colors[ImGuiCol_TextDisabled] << " ";
    out << colors[ImGuiCol_WindowBg] << " ";
    out << colors[ImGuiCol_ChildBg] << " ";
    out << colors[ImGuiCol_PopupBg] << " ";
    out << colors[ImGuiCol_Border] << " ";
    out << colors[ImGuiCol_BorderShadow] << " ";
    out << colors[ImGuiCol_FrameBg] << " ";
    out << colors[ImGuiCol_FrameBgHovered] << " ";
    out << colors[ImGuiCol_FrameBgActive] << " ";
    out << colors[ImGuiCol_TitleBg] << " ";
    out << colors[ImGuiCol_TitleBgActive] << " ";
    out << colors[ImGuiCol_TitleBgCollapsed] << " ";
    out << colors[ImGuiCol_MenuBarBg] << " ";
    out << colors[ImGuiCol_ScrollbarBg] << " ";
    out << colors[ImGuiCol_ScrollbarGrab] << " ";
    out << colors[ImGuiCol_ScrollbarGrabHovered] << " ";
    out << colors[ImGuiCol_ScrollbarGrabActive] << " ";
    out << colors[ImGuiCol_CheckMark] << " ";
    out << colors[ImGuiCol_SliderGrab] << " ";
    out << colors[ImGuiCol_SliderGrabActive] << " ";
    out << colors[ImGuiCol_Button] << " ";
    out << colors[ImGuiCol_ButtonHovered] << " ";
    out << colors[ImGuiCol_HeaderActive] << " ";
    out << colors[ImGuiCol_Separator] << " ";
    out << colors[ImGuiCol_SeparatorHovered] << " ";
    out << colors[ImGuiCol_SeparatorActive] << " ";
    out << colors[ImGuiCol_ResizeGrip] << " ";
    out << colors[ImGuiCol_ResizeGripHovered] << " ";
    out << colors[ImGuiCol_ResizeGripActive] << " ";
    out << colors[ImGuiCol_Tab] << " ";
    out << colors[ImGuiCol_TabHovered] << " ";
    out << colors[ImGuiCol_TabActive] << " ";
    out << colors[ImGuiCol_TabUnfocused] << " ";
    out << colors[ImGuiCol_TabUnfocusedActive] << " ";
    out << colors[ImGuiCol_PlotLines] << " ";
    out << colors[ImGuiCol_PlotLinesHovered] << " ";
    out << colors[ImGuiCol_PlotHistogram] << " ";
    out << colors[ImGuiCol_PlotHistogramHovered] << " ";
    out << colors[ImGuiCol_TableHeaderBg] << " ";
    out << colors[ImGuiCol_TableBorderStrong] << " ";
    out << colors[ImGuiCol_TableBorderLight] << " ";
    out << colors[ImGuiCol_TableRowBg] << " ";
    out << colors[ImGuiCol_TableRowBgAlt] << " ";
    out << colors[ImGuiCol_TextSelectedBg] << " ";
    out << colors[ImGuiCol_DragDropTarget] << " ";
    out << colors[ImGuiCol_NavHighlight] << " ";
    out << colors[ImGuiCol_NavWindowingHighlight] << " ";
    out << colors[ImGuiCol_NavWindowingDimBg] << " ";
    out << colors[ImGuiCol_ModalWindowDimBg] << " ";
    out << colors[ImGuiCol_ButtonActive] << " ";
    out << colors[ImGuiCol_Header] << " ";
    out << colors[ImGuiCol_HeaderHovered] << " ";
    out << colors[ImGuiCol_HeaderActive] << " ";
    out << colors[ImGuiCol_Separator] << " ";
    out << colors[ImGuiCol_SeparatorHovered] << " ";
    out << colors[ImGuiCol_SeparatorHovered] << " ";
    out << colors[ImGuiCol_SeparatorHovered] << " ";
    out << colors[ImGuiCol_SeparatorHovered] << " ";
    out.close();
}

//loads styles + colors to path file
void LoadThisStyle(string path){
    ImGuiStyle& style = ImGui::GetStyle();
    ImVec4 *colors = ImGui::GetStyle().Colors;
    ifstream out(path.c_str());
    out >> style.WindowPadding;
    out >> style.FramePadding;
    out >> style.CellPadding;
    out >> style.ItemSpacing;
    out >> style.ItemInnerSpacing;
    out >> style.TouchExtraPadding;
    out >> style.IndentSpacing;
    out >> style.ScrollbarSize;
    out >> style.GrabMinSize;

    out >> style.WindowBorderSize;
    out >> style.ChildBorderSize;
    out >> style.PopupBorderSize;
    out >> style.FrameBorderSize;
    out >> style.TabBorderSize;

    out >> style.WindowRounding;
    out >> style.ChildRounding;
    out >> style.FrameRounding;
    out >> style.PopupRounding;
    out >> style.ScrollbarRounding;
    out >> style.GrabRounding;
    out >> style.LogSliderDeadzone;
    out >> style.TabRounding;

    out >> style.WindowTitleAlign;
    out >> style.ButtonTextAlign;
    out >> style.SelectableTextAlign;
    out >> style.WindowMenuButtonPosition;
    out >> style.ColorButtonPosition;


    out >> colors[ImGuiCol_Text];
    out >> colors[ImGuiCol_TextDisabled];
    out >> colors[ImGuiCol_WindowBg];
    out >> colors[ImGuiCol_ChildBg];
    out >> colors[ImGuiCol_PopupBg];
    out >> colors[ImGuiCol_Border];
    out >> colors[ImGuiCol_BorderShadow];
    out >> colors[ImGuiCol_FrameBg];
    out >> colors[ImGuiCol_FrameBgHovered];
    out >> colors[ImGuiCol_FrameBgActive];
    out >> colors[ImGuiCol_TitleBg];
    out >> colors[ImGuiCol_TitleBgActive];
    out >> colors[ImGuiCol_TitleBgCollapsed];
    out >> colors[ImGuiCol_MenuBarBg];
    out >> colors[ImGuiCol_ScrollbarBg];
    out >> colors[ImGuiCol_ScrollbarGrab];
    out >> colors[ImGuiCol_ScrollbarGrabHovered];
    out >> colors[ImGuiCol_ScrollbarGrabActive];
    out >> colors[ImGuiCol_CheckMark];
    out >> colors[ImGuiCol_SliderGrab];
    out >> colors[ImGuiCol_SliderGrabActive];
    out >> colors[ImGuiCol_Button];
    out >> colors[ImGuiCol_ButtonHovered];
    out >> colors[ImGuiCol_HeaderActive];
    out >> colors[ImGuiCol_Separator];
    out >> colors[ImGuiCol_SeparatorHovered];
    out >> colors[ImGuiCol_SeparatorActive];
    out >> colors[ImGuiCol_ResizeGrip];
    out >> colors[ImGuiCol_ResizeGripHovered];
    out >> colors[ImGuiCol_ResizeGripActive];
    out >> colors[ImGuiCol_Tab];
    out >> colors[ImGuiCol_TabHovered];
    out >> colors[ImGuiCol_TabActive];
    out >> colors[ImGuiCol_TabUnfocused];
    out >> colors[ImGuiCol_TabUnfocusedActive];
    out >> colors[ImGuiCol_PlotLines];
    out >> colors[ImGuiCol_PlotLinesHovered];
    out >> colors[ImGuiCol_PlotHistogram];
    out >> colors[ImGuiCol_PlotHistogramHovered];
    out >> colors[ImGuiCol_TableHeaderBg];
    out >> colors[ImGuiCol_TableBorderStrong];
    out >> colors[ImGuiCol_TableBorderLight];
    out >> colors[ImGuiCol_TableRowBg];
    out >> colors[ImGuiCol_TableRowBgAlt];
    out >> colors[ImGuiCol_TextSelectedBg];
    out >> colors[ImGuiCol_DragDropTarget];
    out >> colors[ImGuiCol_NavHighlight];
    out >> colors[ImGuiCol_NavWindowingHighlight];
    out >> colors[ImGuiCol_NavWindowingDimBg];
    out >> colors[ImGuiCol_ModalWindowDimBg];
    out >> colors[ImGuiCol_ButtonActive];
    out >> colors[ImGuiCol_Header];
    out >> colors[ImGuiCol_HeaderHovered];
    out >> colors[ImGuiCol_HeaderActive];
    out >> colors[ImGuiCol_Separator];
    out >> colors[ImGuiCol_SeparatorHovered];
    out >> colors[ImGuiCol_SeparatorHovered];
    out >> colors[ImGuiCol_SeparatorHovered];
    out >> colors[ImGuiCol_SeparatorHovered];
    out.close();
}


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
#endif
