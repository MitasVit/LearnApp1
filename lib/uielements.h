#include <imgui/imgui.h>
#include <iostream>
#include <GLFW/glfw3.h>
#include <glad/glad.h>
#include <stb/stb_image.h>
using namespace std;

// glfwGetCursorPos(window, &cursor_x, &cursor_y);

class Rect
{
public:
    ImVec2 size, pos;
    ImU32 col;
    float rounding;
    bool is_filled;
    Rect(ImVec2 size_, ImVec2 pos_, ImU32 col_, float rounding_, bool is_filed_)
    {
        size = size_;
        pos = pos_;
        col = col_;
        rounding = rounding_;
        is_filled = is_filed_;
    }
    void SetSize(ImVec2 size_)
    {
        size = size_;
    }
    void SetPos(ImVec2 pos_)
    {
        pos = pos_;
    }
    void SetPos(double x, double y)
    {
        pos = ImVec2(x, y);
    }
    void SetSize(double w, double h){
        size = ImVec2(w, h);
    }
    void SetColor(ImU32 col_)
    {
        col = col_;
    }
    void SetRounding(float rounding_)
    {
        rounding = rounding_;
    }
    void SetIsFilled(bool is_filled_)
    {
        is_filled = is_filled_;
    }
    void Draw(ImDrawList *dx)
    {
        if (is_filled)
        {
            dx->AddRectFilled(pos, ImVec2(pos.x + size.x, pos.y + size.y), col, rounding);
        }
        else
        {
            dx->AddRect(pos, ImVec2(pos.x + size.x, pos.y + size.y), col, rounding);
        }
    }
    bool IsHovered(ImVec2 cursorpos)
    {
        if ((cursorpos.x >= pos.x) && (cursorpos.y >= pos.y) && (cursorpos.x <= (pos.x + size.x)) && (cursorpos.y <= (pos.y + size.y)))
        {
            return true;
        }
        return false;
    }
    bool IsClicked(ImVec2 cursorpos)
    {
        if ((cursorpos.x >= pos.x) && (cursorpos.y >= pos.y) && (cursorpos.x <= (pos.x + size.x)) && (cursorpos.y <= (pos.y + size.y)))
        {
            if (ImGui::IsMouseClicked(ImGuiMouseButton_Left))
            {
                return true;
            }
        }
        return false;
    }
};

class ImTexture
{
public:
    int width, height;
    GLuint id;

    ImTexture()
    {
    }

    ImTexture(string path)
    {
        // Assigns the type of the texture ot the texture object

        // Stores the width, height, and the number of color channels of the image
        int widthImg, heightImg, numColCh;
        // Flips the image so it appears right side up
        // stbi_set_flip_vertically_on_load(true);

        // Reads the image from a file and stores it in bytes
        unsigned char *bytes = stbi_load(path.c_str(), &widthImg, &heightImg, &numColCh, 0);
        width = widthImg;
        height = heightImg;
        // Generates an OpenGL texture object
        glGenTextures(1, &id);
        // Assigns the texture to a Texture Unit
        glActiveTexture(GL_TEXTURE0 + 1);
        glBindTexture(GL_TEXTURE_2D, id);

        // Configures the type of algorithm that is used to make the image smaller or bigger
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        // Configures the way the texture repeats (if it does at all)
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

        // Extra lines in case you choose to use GL_CLAMP_TO_BORDER
        // float flatColor[] = {1.0f, 1.0f, 1.0f, 1.0f};
        // glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, flatColor);

        // Check what type of color channels the texture has and load it accordingly
        if (numColCh == 4)
            glTexImage2D(
                GL_TEXTURE_2D,
                0,
                GL_RGBA,
                widthImg,
                heightImg,
                0,
                GL_RGBA,
                GL_UNSIGNED_BYTE,
                bytes);
        else if (numColCh == 3)
            glTexImage2D(
                GL_TEXTURE_2D,
                0,
                GL_RGBA,
                widthImg,
                heightImg,
                0,
                GL_RGB,
                GL_UNSIGNED_BYTE,
                bytes);
        else if (numColCh == 1)
            glTexImage2D(
                GL_TEXTURE_2D,
                0,
                GL_RGBA,
                widthImg,
                heightImg,
                0,
                GL_RED,
                GL_UNSIGNED_BYTE,
                bytes);
        else
            throw std::invalid_argument("Automatic Texture type recognition failed");

        // Generates MipMaps
        glGenerateMipmap(GL_TEXTURE_2D);

        // Deletes the image data as it is already in the OpenGL Texture object
        stbi_image_free(bytes);

        // Unbinds the OpenGL Texture object so that it can't accidentally be modified
        glBindTexture(GL_TEXTURE_2D, 0);
    }

    void Load(string path)
    {
        // Assigns the type of the texture ot the texture object

        // Stores the width, height, and the number of color channels of the image
        int widthImg, heightImg, numColCh;
        // Flips the image so it appears right side up
        // stbi_set_flip_vertically_on_load(true);

        // Reads the image from a file and stores it in bytes
        unsigned char *bytes = stbi_load(path.c_str(), &widthImg, &heightImg, &numColCh, 0);
        width = widthImg;
        height = heightImg;
        // Generates an OpenGL texture object
        glGenTextures(1, &id);
        // Assigns the texture to a Texture Unit
        glActiveTexture(GL_TEXTURE0 + 1);
        glBindTexture(GL_TEXTURE_2D, id);

        // Configures the type of algorithm that is used to make the image smaller or bigger
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        // Configures the way the texture repeats (if it does at all)
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

        // Extra lines in case you choose to use GL_CLAMP_TO_BORDER
        // float flatColor[] = {1.0f, 1.0f, 1.0f, 1.0f};
        // glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, flatColor);

        // Check what type of color channels the texture has and load it accordingly
        if (numColCh == 4)
            glTexImage2D(
                GL_TEXTURE_2D,
                0,
                GL_RGBA,
                widthImg,
                heightImg,
                0,
                GL_RGBA,
                GL_UNSIGNED_BYTE,
                bytes);
        else if (numColCh == 3)
            glTexImage2D(
                GL_TEXTURE_2D,
                0,
                GL_RGBA,
                widthImg,
                heightImg,
                0,
                GL_RGB,
                GL_UNSIGNED_BYTE,
                bytes);
        else if (numColCh == 1)
            glTexImage2D(
                GL_TEXTURE_2D,
                0,
                GL_RGBA,
                widthImg,
                heightImg,
                0,
                GL_RED,
                GL_UNSIGNED_BYTE,
                bytes);
        else
            throw std::invalid_argument("Automatic Texture type recognition failed");

        // Generates MipMaps
        glGenerateMipmap(GL_TEXTURE_2D);

        // Deletes the image data as it is already in the OpenGL Texture object
        stbi_image_free(bytes);

        // Unbinds the OpenGL Texture object so that it can't accidentally be modified
        glBindTexture(GL_TEXTURE_2D, 0);
    }

    int GetWidth()
    {
        return width;
    }

    int GetHeight()
    {
        return height;
    }

    GLuint GetID()
    {
        return id;
    }
};

class Img
{
public:
    ImVec2 size, pos;
    ImTexture tex;
    Img(ImVec2 size_, ImVec2 pos_, ImTexture tex_)
    {
        size = size_;
        pos = pos_;
        tex = tex_;
    }
    Img(ImVec2 size_, ImVec2 pos_, string path)
    {
        size = size_;
        pos = pos_;
        tex.Load(path);
    }
    void SetSize(ImVec2 size_)
    {
        size = size_;
    }
    void SetPos(ImVec2 pos_)
    {
        pos = pos_;
    }
    void SetPos(double x, double y)
    {
        pos = ImVec2(x, y);
    }
    void SetSize(double w, double h){
        size = ImVec2(w, h);
    }
    void SetTex(ImTexture tex_){
        tex = tex_;
    }
    void LoadTex(string path){
        tex.Load(path);
    }
    //(void *)(intptr_t)teams.GetID()
    void Draw(ImDrawList *dx)
    {
        dx->AddImage((void *)(intptr_t)tex.GetID(), pos, ImVec2(pos.x + size.x, pos.y + size.y));
    }
    bool IsHovered(ImVec2 cursorpos)
    {
        if ((cursorpos.x >= pos.x) && (cursorpos.y >= pos.y) && (cursorpos.x <= (pos.x + size.x)) && (cursorpos.y <= (pos.y + size.y)))
        {
            return true;
        }
        return false;
    }
    bool IsClicked(ImVec2 cursorpos)
    {
        if ((cursorpos.x >= pos.x) && (cursorpos.y >= pos.y) && (cursorpos.x <= (pos.x + size.x)) && (cursorpos.y <= (pos.y + size.y)))
        {
            if (ImGui::IsMouseClicked(ImGuiMouseButton_Left))
            {
                return true;
            }
        }
        return false;
    }
};

class ImgRect : public Rect
{
public:
    ImTexture tex;
    ImgRect(ImVec2 size_, ImVec2 pos_, ImTexture tex_, ImU32 col_, float rounding_, bool is_filed_) : Rect(size_, pos_, col_, rounding_, is_filed_)
    {
        size = size_;
        pos = pos_;
        tex = tex_;
    }
    ImgRect(ImVec2 size_, ImVec2 pos_, ImU32 col_, float rounding_, bool is_filed_, string path) : Rect(size_, pos_, col_, rounding_, is_filed_)
    {
        size = size_;
        pos = pos_;
        tex.Load(path);
    }
    void LoadTex(string path){
        tex.Load(path);
    }
    //(void *)(intptr_t)teams.GetID()
    void Draw(ImDrawList *dx)
    {
        if (is_filled)
        {
            dx->AddRectFilled(pos, ImVec2(pos.x + size.x, pos.y + size.y), col, rounding);
        }
        else
        {
            dx->AddRect(pos, ImVec2(pos.x + size.x, pos.y + size.y), col, rounding);
        }
        dx->AddImage((void *)(intptr_t)tex.GetID(), pos, ImVec2(pos.x + size.x, pos.y + size.y));
    }
    bool IsHovered(ImVec2 cursorpos)
    {
        if ((cursorpos.x >= pos.x) && (cursorpos.y >= pos.y) && (cursorpos.x <= (pos.x + size.x)) && (cursorpos.y <= (pos.y + size.y)))
        {
            return true;
        }
        return false;
    }
    bool IsClicked(ImVec2 cursorpos)
    {
        if ((cursorpos.x >= pos.x) && (cursorpos.y >= pos.y) && (cursorpos.x <= (pos.x + size.x)) && (cursorpos.y <= (pos.y + size.y)))
        {
            if (ImGui::IsMouseClicked(ImGuiMouseButton_Left))
            {
                return true;
            }
        }
        return false;
    }
};

ImVec2 get_text_size(ImFont *font, const char *text) {
  return font->CalcTextSizeA(font->FontSize, FLT_MAX, 0.0f, text, NULL, NULL);
}

class Text
{
public:
    ImVec2 pos;
    string text;
    ImFont* font;
    ImU32 col;
    Text(ImVec2 pos_, string text_, ImFont* font_, ImU32 col_)
    {
        pos = pos_;
        text = text_;
        font = font_;
        col = col_;
    }
    void SetPos(ImVec2 pos_)
    {
        pos = pos_;
    }
    void SetPos(double x, double y)
    {
        pos = ImVec2(x, y);
    }
    void SetFont(ImFont* font_){
        font = font_;
    }
    void SetCol(ImU32 col_){
        col = col_;
    }
    void SetText(string text_){
        text = text_;
    }
    void Draw(ImDrawList *dx)
    {
        ImGui::PushFont(font);
        dx->AddText(pos, col, text.c_str());
        ImGui::PopFont();
    }
    bool IsHovered(ImVec2 cursorpos)
    {
        ImVec2 size = get_text_size(font, text.c_str());
        if ((cursorpos.x >= pos.x) && (cursorpos.y >= pos.y) && (cursorpos.x <= (pos.x + size.x)) && (cursorpos.y <= (pos.y + size.y)))
        {
            return true;
        }
        return false;
    }
    //is hovered but seting the colision rect
    bool IsHovered(ImVec2 cursorpos, ImVec2 leftup, ImVec2 rightdown)
    {
        if ((cursorpos.x >= leftup.x) && (cursorpos.y >= leftup.y) && (cursorpos.x <= (leftup.x + rightdown.x)) && (cursorpos.y <= (leftup.y + rightdown.y)))
        {
            return true;
        }
        return false;
    }
    bool IsClicked(ImVec2 cursorpos)
    {
        ImVec2 size = get_text_size(font, text.c_str());
        if ((cursorpos.x >= pos.x) && (cursorpos.y >= pos.y) && (cursorpos.x <= (pos.x + size.x)) && (cursorpos.y <= (pos.y + size.y)))
        {
            if (ImGui::IsMouseClicked(ImGuiMouseButton_Left))
            {
                return true;
            }
        }
        return false;
    }
};

/*
template<typename T>
class UI_element{
    public:

    static ImVec2 cursorpos;
    static void SetCursorPos(ImVec2 cursorpos_){
        cursorpos = cursorpos_;
    }
    static void SetCursorPos(GLFWwindow *window){
        glfwGetCursorPos(window, &cursorpos.x, &cursorpos.y);
    }
    static void SetCursorPos(int x, int y){
        cursorpos.x = x;
        cursorpos.y = y;
    }

    ImVec2 size, position;
    T content;

    virtual void Draw() = 0;
    virtual void Create() = 0;

    UI_element() :cursorpos(0,0), size(0,0), position(0,0){}

    void SetSize(ImVec2 size_){
        size.x = size_.x;
        size.y = size_.y;
    }
    void SetPosition(ImVec2 position_){
        position.x = position_.x;
        position.y = position_.y;
    }
    void SetContent(T content_){
        content = content_;
    }
    bool IsHovered(){
        if((cursorpos.x >= position.x) && (cursorpos.y >= position.y) && (cursorpos.x >= (position.x + size.x)) && (cursorpos.y >= (position.y + size.y)) ){
            return true;
        }
        return false;
    }
    bool IsClicked(){
        if((cursorpos.x >= position.x) && (cursorpos.y >= position.y) && (cursorpos.x >= (position.x + size.x)) && (cursorpos.y >= (position.y + size.y)) ){
            if(ImGui::IsMouseClicked(ImGuiMouseButton_Left)){
                return true;
            }
        }
        return false;
    }
};
*/