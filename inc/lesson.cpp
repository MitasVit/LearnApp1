#include "lesson.h"

using namespace std;

Lesson::Lesson(string path, ImFont *_titlefont, ImFont *_textfont)
{
    // test read + open + is empty
    ifstream test(path.c_str());
    bool _end = false;
    if (!test)
    {
        // file dont exist/cant open
        cout << "file " << path << " dont exist/cant open" << endl;
        test.close();
        _end = true;
    }
    else
    {
        if (test.peek() == std::ifstream::traits_type::eof())
        {
            // file is empty
            cout << "file " << path << " is empty" << endl;
            test.close();
            _end = true;
        }
        else
        {
            // ok
            test.close();
        }
    }
    if (!_end)
    {
        xml_document doc;
        xml_parse_result result = doc.load_file(path.c_str());
        cout << "error: " << result.description();

        // info
        author = (doc.child("lesson").child("info").child_value("author"));
        create_date = doc.child("lesson").child("info").child_value("create_date");
        subject = doc.child("lesson").child("info").child_value("subject");

        // load tags
        xml_node tagsnodes = doc.child("lesson").child("info").child("tags");
        count = std::distance(tagsnodes.begin(), tagsnodes.end());
        tags = new string[count];

        for (int i = 1; i < (count + 1); i++)
        {
            string tmp = "tag" + to_string(i);
            tags[i - 1] = tagsnodes.child_value(tmp.c_str());
        }

        // load sources
        xml_node tagssources = doc.child("lesson").child("info").child("sources");
        count2 = std::distance(tagssources.begin(), tagssources.end());
        sources = new string[count2];

        for (int i = 1; i < (count2 + 1); i++)
        {
            string tmp = "source" + to_string(i);
            sources[i - 1] = tagssources.child_value(tmp.c_str());
        }

        // body
        title = doc.child("lesson").child("body").child_value("title");
        text = doc.child("lesson").child("body").child_value("text");

        // load examples
        xml_node tagsexamples = doc.child("lesson").child("info").child("examples");
        count3 = std::distance(tagsexamples.begin(), tagsexamples.end());
        examples = new string[count3];
        solutions = new string[count3];

        for (int i = 1; i < (count3 + 1); i++)
        {
            string tmp = "example" + to_string(i);
            examples[i - 1] = tagssources.child(tmp.c_str()).child_value("text");
            solutions[i - 1] = tagssources.child(tmp.c_str()).child_value("solution");
        }

        // load excercises
        xml_node tagsexcercises = doc.child("lesson").child("info").child("excercises");
        count4 = std::distance(tagsexcercises.begin(), tagsexcercises.end());
        excercises = new string[count4];

        for (int i = 1; i < (count4 + 1); i++)
        {
            string tmp = "excercise" + to_string(i);
            excercises[i - 1] = tagsexcercises.child_value(tmp.c_str());
        }
    }

    are_they_hovered = new bool[count2];
    for(int i = 0; i < count2; i++){
        are_they_hovered[i] = false;
    }

    titlefont = _titlefont;
    textfont = _textfont;

}

void Lesson::Draw()
{
    ImGui::PushFont(titlefont);
    ImGui::Text(title.c_str());
    ImGui::PopFont();

    ImGui::PushFont(textfont);
    ImGui::BulletText("Author: %s", author.c_str());
    ImGui::BulletText("Created: %s", create_date.c_str());
    ImGui::BulletText("Subject: %s", subject.c_str());
    ImGui::Separator();
    ImGui::Text("Tags: ");
    for (int i = 0; i < count; i++)
    {
        ImGui::BulletText(tags[i].c_str());
        ImGui::SameLine();
    }
    ImGui::Separator();
    ImGui::Text("Sources: ");
    
    for (int i = 0; i < count2; i++)
    {
        
        //ImGui::PushTextWrapPos( -1.0f );
        //ImGui::TextUnformatted(sources[i].c_str());
        //ImGui::PopTextWrapPos();
        if(are_they_hovered[i]){
            ImGui::PushStyleColor(ImGuiCol_Text, IM_COL32(0,150,0,255));
            ImGui::TextUnformatted(sources[i].c_str());
            ImGui::PopStyleColor();
        }else{
            ImGui::PushStyleColor(ImGuiCol_Text, IM_COL32(0,255,0,255));
            ImGui::TextUnformatted(sources[i].c_str());
            ImGui::PopStyleColor();
        }
        
        are_they_hovered[i] = ImGui::IsItemHovered();
        if(are_they_hovered[i])
        {
            if(ImGui::IsMouseReleased( 0 ))
            {
                string cmd = "open " + sources[i];
                system(cmd.c_str());
            }
        }
        
        //ImGui::BulletText();
        ImGui::SameLine();
    }
    ImGui::Separator();
    ImGui::TextWrapped(text.c_str());
    ImGui::Separator();
    ImGui::Text("Examples:");
    for (int i = 0; i < count3; i++)
    {
        ImGui::BulletText(examples[i].c_str());
        ImGui::SameLine();
    }
    ImGui::Separator();
    ImGui::Text("solutions:");
    for (int i = 0; i < count3; i++)
    {
        ImGui::BulletText(solutions[i].c_str());
        ImGui::SameLine();
    }
    ImGui::PopFont();
}

void Lesson::SaveToFile(string path){
   /* string full = "<lesson><info><author>" + author + "</author><create_date>" + create_date + "</create_date><subject>" + subject + "</subject><tags>";
    for(int i = 0; i < count; i++){
        full = full + "<tag" + to_string(i+1) + ">" + tags[i] + "</tag" + to_string(i+1) + ">";
    }
    full = full + "</tags><sources>";
    for(int i = 0; i < count2; i++){
        full = full + "<source" + to_string(i+1) + ">" + sources[i] + "</source" + to_string(i+1) + ">";
    }
    full = full + "</sources></info><body><title>" + title + "</title><text>"+ text + "</text><examples><example1><text>Příklad: 1+1</text><solution>1 + 1 = 2Ok.</solution></example1></examples><excercises><excercise1>Solve 1 + 2</excercise1></excercises></body></lesson>";
    ofstream out(path.c_str());
    out << full;
    out.close();*/
    ofstream out(path.c_str());
    out << "<lesson><info><author>" << author.c_str() <<  "</author><create_date>" << create_date.c_str() << "</create_date><subject>" << subject.c_str() << "</subject><tags>";
     for(int i = 0; i < count; i++){
        out<< "<tag" << to_string(i+1) << ">" << tags[i].c_str() << "</tag" << to_string(i+1) << ">";
    }
    out << "</tags><sources>";
    for(int i = 0; i < count2; i++){
        out << "<source" << to_string(i+1) << ">" << sources[i].c_str() << "</source" << to_string(i+1) << ">";
    }
    out << "</sources></info><body><title>" << title.c_str() << "</title><text>"<< text.c_str() << "</text><examples>";
     for(int i = 0; i < count3; i++){
        out << "<example" << to_string(i+1) << ">" << "<text>" << examples[i].c_str() <<  "</text>"<< "<solution>" << solutions[i].c_str() <<  "</solution>" << "</example" << to_string(i+1) << ">";
    }
    out << "</examples><excercises>";
    for(int i = 0; i < count4; i++){
        out << "<excercise" << to_string(i+1) << ">" << excercises[i].c_str() << "</excercise" << to_string(i+1) << ">";
    }
    out << "</excercises></body></lesson>";
    out.close();
}

void Lesson::LoadfromFile(string path){
    // test read + open + is empty
    ifstream test(path.c_str());
    bool _end = false;
    if (!test)
    {
        // file dont exist/cant open
        cout << "file " << path << " dont exist/cant open" << endl;
        test.close();
        _end = true;
    }
    else
    {
        if (test.peek() == std::ifstream::traits_type::eof())
        {
            // file is empty
            cout << "file " << path << " is empty" << endl;
            test.close();
            _end = true;
        }
        else
        {
            // ok
            test.close();
        }
    }
    if (!_end)
    {
        xml_document doc;
        xml_parse_result result = doc.load_file(path.c_str());
        cout << "error: " << result.description();

        // info

        author = (doc.child("lesson").child("info").child_value("author"));
        create_date = doc.child("lesson").child("info").child_value("create_date");
        subject = doc.child("lesson").child("info").child_value("subject");

        // load tags
        xml_node tagsnodes = doc.child("lesson").child("info").child("tags");
        count = std::distance(tagsnodes.begin(), tagsnodes.end());
        tags = new string[count];

        for (int i = 1; i < (count + 1); i++)
        {
            string tmp = "tag" + to_string(i);
            tags[i - 1] = tagsnodes.child_value(tmp.c_str());
        }

        // load sources
        xml_node tagssources = doc.child("lesson").child("info").child("sources");
        count2 = std::distance(tagssources.begin(), tagssources.end());
        sources = new string[count2];

        for (int i = 1; i < (count2 + 1); i++)
        {
            string tmp = "source" + to_string(i);
            sources[i - 1] = tagssources.child_value(tmp.c_str());
        }

        // body
        title = doc.child("lesson").child("body").child_value("title");
        text = doc.child("lesson").child("body").child_value("text");

        // load examples
        xml_node tagsexamples = doc.child("lesson").child("info").child("examples");
        count3 = std::distance(tagsexamples.begin(), tagsexamples.end());
        examples = new string[count3];
        solutions = new string[count3];

        for (int i = 1; i < (count3 + 1); i++)
        {
            string tmp = "example" + to_string(i);
            examples[i - 1] = tagssources.child(tmp.c_str()).child_value("text");
            solutions[i - 1] = tagssources.child(tmp.c_str()).child_value("solution");
        }

        // load excercises
        xml_node tagsexcercises = doc.child("lesson").child("info").child("excercises");
        count4 = std::distance(tagsexcercises.begin(), tagsexcercises.end());
        excercises = new string[count4];

        for (int i = 1; i < (count4 + 1); i++)
        {
            string tmp = "excercise" + to_string(i);
            excercises[i - 1] = tagsexcercises.child_value(tmp.c_str());
        }
    }

    are_they_hovered = new bool[count2];
    for(int i = 0; i < count2; i++){
        are_they_hovered[i] = false;
    }
}

//unicode: ůěščřžňďťýáíúóéŮĚŠČŘŽŇĎŤÝÁÍÚÓÉ
// ů - 016F, ě - 011B, š - 0161, č - 010D, ř - 0159, ž - 017E, ň - 0148