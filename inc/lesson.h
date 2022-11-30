#ifndef LESSON_H
#define LESSON_H

#include <pugixml/pugixml.hpp>
#include <iostream>
#include <fstream>
#include <imgui/imgui.h>

#include "utils.h"

using namespace std;
using namespace pugi;

//doc.child("..")
//.atribute("").value
//.child_value("")


class Lesson{
public:
    //info
    string author;
    string create_date;
    string subject;
    string *tags;//latky
    size_t count;
    string *sources;
    size_t count2;

    //body
    string title;
    string text;
    string *examples;//every x
    size_t count3;
    string *solutions;
    size_t count4;

    //lesson check
    string *excercises;

    bool *are_they_hovered;

    ImFont *titlefont, *textfont;

    //path - path to xml file with lesson
    Lesson(string path, ImFont *_titlefont, ImFont *_textfont);

    

    void Draw();

    void SaveToFile(string path);
    void LoadfromFile(string path);
};

#endif