# LearnToEarnPrivate

Learn to earn is an app which helps you with learning, improve your learning methos, planning and time saving.

# Build

## Linux

### Preparing dependecies

```bash
sudo apt-get install libpthread-dev
sudo apt-get install libmesa-dev
sudo apt-get install libfreeglut-dev
sudo apt-get install libxorg-dev
sudo apt-get install libcurl-dev
sudo apt-get install libcurlpp-dev
```

### Download + build + run

```sh
git clone https://github.com/MitasVit/LearnToEarnPrivate.git
cd LearnToEarnPrivate
sh compile_run_lesbak.sh
```

## Windows

### Preparing dependecies

```cmd
curl https://github.com/msys2/msys2-installer/releases/download/2022-06-03/msys2-x86_64-20220603.exe >> msys2.exe
start msys2.exe

```

Run this in msys2 console

```cmd
pacman -S --needed base-devel mingw-w64-x86_64-toolchain
pacman -S --needed base-devel mingw-w64-x86_64-mesa
pacman -S --needed base-devel mingw-w64-x86_64-freeglut
pacman -S --needed base-devel mingw-w64-x86_64-glfw
pacman -S --needed base-devel mingw-w64-x86_64-curl
pacman -S mingw-w64-x86_64-cairo


```

Add the path to your Mingw-w64 bin folder to the Windows PATH environment variable by using the following steps:

- In the Windows search bar, type 'settings' to open your Windows Settings.
- Search for Edit environment variables for your account.
- Choose the Path variable in your User variables and then select Edit.
- Select New and add the Mingw-w64 destination folder path to the system path. The exact path depends on which version of Mingw-w64 you have installed and where you installed it.
- If you used the settings above to install Mingw-w64, then add this to the path:  `C:\msys64\mingw64\bin`.
- Select OK to save the updated PATH. You will need to reopen any console windows for the new PATH location to be available.
- Check your MinGW installation with command:  `g++ --version`

```cmd
git clone https://github.com/MitasVit/LearnToEarnPrivate.git
git clone https://github.com/jpbarrette/curlpp.git
cd curlpp 
mkdir build
cd build
cmake -G "MinGW Makefiles"
mingw32-make -f Makefile
copy libcurlpp.dll ../../LearnToEarnPrivate/
cd ..
cd ..
cd LearnToEarnPrivate
```

### Build

Precompiled objects - it's nesseseary to run it once:

```cmd
start windows_pre.bat
```

Final compile + linking precompiled objects:

```cmd
start windows.bat
```

### Running

Go to `LearnToEarnPrivate/win` directory and open main.exe.




# How to use Bakaláři module

See: https://github.com/bakalari-api/bakalari-api-v3

## Dependencies

 - `curl` -> for POST and GET transfer data from web
 - `curlpp` -> c++ wrapper for curl
 - `rapidjson` -> json parser and genrator

## Example code: `example.cpp:`

```c++
#include <bakalari.h>

int main(){

    
    BakalariUser ja;

    //setup school bakalari
    //this means that login to our bakalari will be something like: 
    //https://bakalari.gympolicka.cz/login.aspx
    ja.SetSchoolUrl("bakalari.gympolicka.cz");

    //login + write acces_token and login info into login.json
    ja.WriteLogin("YOUR_NAME", "YOUR_PASSWORD", "login.json");
    
    //gets info about user
    ja.LoadWriteUserInfo("info.json");

    //gets active timetable and saves it to variable and actimetable.json
    TimeTable a = ja.GetActTimeTable2("actimetable.json", "2022-10-14");

    //teacher from 3. lesson from 3. day
    cout << "ucitel: " << a.lessons[2][2].teacherfull << endl;
    
    //displaying user info
    cout << ja.fullname << " is from class: " << ja.classname << "(" << ja.classabbrev << ")" << endl;
    return 0;

}
```
Running this example:

```cmd
git clone https://github.com/MitasVit/LearnToEarnPrivate.git
g++ -c LearnToEarnPrivate/bakalari/bakalari.cpp -I "LearnToEarnPrivate/bakalari" -I "LearnToEarnPrivate/lib" -o bakalari.o
g++ -c example.cpp -I "LearnToEarnPrivate/bakalari" -I "LearnToEarnPrivate/lib" -o example.o
g++ bakalari.o example.o -lcurl -lcurlpp -o example.exe
```
Note: You will need to have installed the curl and curlpp libraries.

## Use bakalari module for login

1. Get city list - you can do it with function: `GetCityList(city_list.json)` 
2. Select school from city - `GetSchools(schools.json, cityname)`
3. Get school url from the `schools.json` + extract the school url example for: `https://bakalari.gympolicka.cz/login.aspx ` the school url will be: `bakalari.gympolicka.cz` -> `SetSchoolUrl("bakalari.gympolicka.cz");`
4. Create `BakalariUser` class object
5. Login with `BakalariUser::Login(username, password)` function
6. Use bakalari data
   

## Use power state module

Note: this module is only for windows and works only on notebooks because of batery.

### Example use:

```c++
#include "PowerState.h"
#include <iostream>

using namespace std;

int main(){
    //creating power manager
    WindowsPower powrman;

    //getting some info from manager:
    cout << "The power state of batery is: " << PowerStateToString(powrman.GetPowerState()) << endl;
    cout << "The percentage of batery is: " << powrman.GetPowerPercentageLeft() << endl;
    cout << "The batery will unload after: " << powrman.GetPowerSecondsLeft() << " seconds" << endl;
    cout << "The batery will unload after: " << powrman.GetPowerSecondsLeft()/60 << " minutes" << endl;
    cout << "The batery will unload after: " << powrman.GetPowerSecondsLeft()/3600 << " hours" << endl;
    return 0;
}
```

Example output if the batery is charging:
Note: the -1 means that the batery will never unload while charging.
```txt
The power state of batery is: Charging
The percentage of batery is: 41                                                                                         
The batery will unload after: -1 seconds                                                                         
The batery will unload after: 0 minutes                                                                          
The batery will unload after: 0 hours
```

# Old code for drawing toppanel eg.: with logs and notes

```c++
int wheight2=0, wwidth2=0;
	glfwGetWindowSize(window, &wwidth2, &wheight2);
	ImVec2 size2 = get_text_size(panel_name.font, panel_name.text.c_str());
	int zprava = (wheight2 / 100) * 11 + (wwidth2 / 100) * 3;//rightmargin
	ImVec2 pos1 = ImVec2((wwidth2 - size2.x) - zprava, (wheight2/100) * 4);
	ImVec2 pos2 = ImVec2((wwidth2 - size2.x) - zprava, (wheight2/100) * 8);
	ImVec2 pos3 = ImVec2(wwidth2-55, 10);

	cout << "POSITIONS:" <<endl;
	cout << "pos1: (" << pos1.x << ", " << pos1.y << ")" << endl;
	cout << "pos2: (" << pos2.x << ", " << pos2.y << ")" << endl;
	cout << "pos3: (" << pos3.x << ", " << pos3.y << ")" << endl <<endl;
	ImVec2 tsi = get_text_size(ucet, panel_acc.text.c_str());
	ImVec2 tsi2 = ucet->CalcTextSizeA(ucet->FontSize, FLT_MAX, 0.0f, panel_acc.text.c_str(), NULL, NULL);
	ImVec2 tsi3 = account_font->CalcTextSizeA(account_font->FontSize, FLT_MAX, 0.0f, panel_name.text.c_str(), NULL, NULL);
	cout << "Text size: (" << tsi.x << ", " << tsi.y << ")" <<endl;
	cout << "Text size: (" << tsi2.x << ", " << tsi2.y << ")" <<endl;
	cout << "Text size: (" << tsi3.x << ", " << tsi3.y << ")" <<endl;
	
	cout << "Text: " << panel_acc.text << endl;
	cout << "Text: " <<  panel_name.text << endl;
	cout << "color: " << panel_name.col <<endl;
```
in loop:
```c++
//drawlist->AddLine(p1,vMax, IM_COL32(255, 255, 0, 255));//zluta cara
//rgba(0,0,28,255)


//drawlist2->AddRectFilled(ImVec2(0,0), ImVec2(wwidth, 72), IM_COL32(0,0,28,255));
//drawlist->AddImage((void *)(intptr_t)account.GetID(),ac_image_leftup, ac_image_rightdown );


//computing responsive sizes + positions
int zprava = (wheight / 100) * 11 + (wwidth / 100) * 3;//rightmargin
ImVec2 size = get_text_size(panel_name.font, panel_name.text.c_str());

log << endl << endl << "zprava: " << zprava  << endl;
log << "wwidth: " << wwidth << endl;
log << "wheight: " << wheight << endl;
log << "Text size for panel_name: (" << size.x << "," << size.y << ")" << endl;
log << "LOG: setting panel_name[" << panel_name.text << "] position to: (" << ((wwidth - size.x) - zprava) << ", " << ( (wheight/100) * 4) << ")" << endl;
panel_name.SetPos(ImVec2((wwidth - size.x) - zprava, (wheight/100) * 4));
//x: width - (size.width + zprava)
//y: 4% z height

log << "LOG: setting panel_acc[" << panel_acc.text << "] position to: (" << ((wwidth - size.x) - zprava) << ", " << ( (wheight/100) * 8) << ")" << endl;
panel_acc.SetPos(ImVec2((wwidth - size.x) - zprava, (wheight/100) * 8));
//x: width - (size.width + zprava)
//y: 8% z height

log << "LOG: setting panel size to: (" << (wwidth) << ", " << ((wheight/100) * 15) << ")" << endl;
panel.SetSize(ImVec2(wwidth, (wheight/100) * 15));
//width: width, height: 15% z height

log << "LOG: setting panel position to: (" << (wwidth-55) << ", " << (10) << ")" << endl;
panel_account_img.SetPos(ImVec2(wwidth-55, 10));

log <<"LOG: cursor position: (" <<  curx << ", " <<cury << ")" << endl;

if(panel_acc.IsHovered(ImVec2(curx, cury), ImVec2(wwidth -50 , 0), ImVec2(wwidth, 50))){
	//log << "LOG: panel_acc was hovered" <<endl;
	//cout << "Hovered" <<endl;
	panel_acc.SetCol(IM_COL32(255,0,0,255));
}else{
	//log << "LOG: panel_acc is NOT hovered" <<endl;
	panel_acc.SetCol(IM_COL32(255,255,255,255));
}

if(panel_account_img.IsHovered(ImVec2(curx, cury))){
	//log << "LOG: panel_account_img was hovered" <<endl;
}else{
	//log << "LOG: panel_account_img is NOT hovered" <<endl;
}

log <<"Drawing all things from toppanel" <<endl;
panel.Draw(drawlist);
panel_account_img.Draw(drawlist);
panel_name.Draw(drawlist);
panel_acc.Draw(drawlist);

log << endl << "Barvy jako IM_COL32:" <<endl;
log << "Cervena: " << IM_COL32(255,0,0,255) << endl;
log << "Bila: " << IM_COL32(255,255,255,255) << endl;
log << "Zelena: " << IM_COL32(0,255,0,255) << endl;
log << "Modra: " << IM_COL32(0,0,255,255) << endl;
log << "Cerna: " << IM_COL32(0,0,0,255) << endl;

color32 extract = ExtractIM_COL32(panel_name.col);
ImVec2 rucne = account_font->CalcTextSizeA(account_font->FontSize, FLT_MAX, 0, panel_name.text.c_str(), NULL, NULL);
ImVec2 zetridy = panel_name.font->CalcTextSizeA(panel_name.font->FontSize, FLT_MAX, 0, panel_name.text.c_str(), NULL, NULL);
ImVec2 fc = get_text_size(panel_name.font, panel_name.text.c_str());
log << endl<< "kontrola dat[panel_name]: " <<endl;
log << "Definovana jako: ImVec2(1243, 20), \"Mitas Vit\", account_font, IM_COL32(255,0,0,255)" <<endl;
log << "Barva:  " << panel_name.col << "(" << extract.r << ", "<< extract.g << ", "<< extract.b << ", "<< extract.a << ")" <<endl;
log << "Pozice: (" << panel_name.pos.x << ", " << panel_name.pos.y << ")" << endl; 
log << "Text: " << panel_name.text << "(" << panel_name.text.c_str() << ")" << endl;
log << "Velikost rucne: [" << rucne.x << "," << rucne.y << "]" <<endl;
log << "Velikost funkce: [" << fc.x << "," << fc.y << "]" <<endl;
log << "Velikost ze tridy: [" << zetridy.x << "," << zetridy.y << "]"<<endl << endl;

color32 extract2 = ExtractIM_COL32(panel_acc.col);
ImVec2 rucne2 = ucet->CalcTextSizeA(ucet->FontSize, FLT_MAX, 0, panel_acc.text.c_str(), NULL, NULL);
ImVec2 zetridy2 = panel_acc.font->CalcTextSizeA(panel_acc.font->FontSize, FLT_MAX, 0, panel_acc.text.c_str(), NULL, NULL);
ImVec2 fc2 = get_text_size(panel_acc.font, panel_acc.text.c_str());
log << endl<< "kontrola dat[panel_acc]: " <<endl;
log << "Definovana jako: panel_acc(ImVec2(1243, 20), \"My account\", ucet, IM_COL32(255,255,255,255))" <<endl;
log << "Barva:  " << panel_acc.col << "(" << extract2.r << ", "<< extract2.g << ", "<< extract2.b << ", "<< extract2.a << ")" <<endl;
log << "Pozice: (" << panel_acc.pos.x << ", " << panel_acc.pos.y << ")" << endl; 
log << "Text: " << panel_acc.text << "(" << panel_acc.text.c_str() << ")" << endl;
log << "Velikost rucne: [" << rucne2.x << "," << rucne2.y << "]" <<endl;
log << "Velikost funkce: [" << fc2.x << "," << fc2.y << "]" <<endl;
log << "Velikost ze tridy: [" << zetridy2.x << "," << zetridy2.y << "]"<<endl << endl;

ImGui::EndChild();



//variables for computing

log <<"LOG: leftwidget" << endl;
```

## for lesson_win - rendering toppanel

```c++
ImVec2 ac_image_leftup =ImVec2(wwidth-55, 10), ac_image_rightdown = ImVec2((wwidth-55 )+50, 10+50);
    drawlist2->AddRectFilled(ImVec2(0,0), ImVec2(wwidth, 72),   IM_COL32(0,0,28,255));
	drawlist->AddImage((void *)(intptr_t)account.GetID(),ac_image_leftup, ac_image_rightdown );
	
	ImGui::PushFont(jmeno);
	drawlist->AddText(ImVec2(wwidth-145+10, 10+10), IM_COL32(255,255,255,255), "Mitáš Vít");
	ImGui::PopFont();
	ImGui::PushFont(ucet);
	drawlist->AddText(ImVec2(wwidth-145+10, 30+10)IM_COL32(255,255,255,255), "Můj účet");
    ImGui::PopFont();

    else if(((cursor_x >= ac_image_leftup.x) && (cursor_y >= ac_image_leftup.y))
			 && ((cursor_x <= ac_image_rightdown.x) && (cursor_y <= ac_image_rightdown.y)))
			{
				log <<"LOG: OLD account image hovered" << endl;
				//account image
			 	if(ImGui::IsMouseClicked(ImGuiMouseButton_Left)){
					//bakalari button click
					show_menu_part = 6;
				}
			}
```


Super old code:
```c++
    ImGui::SetNextWindowPos(ImVec2(wwidth-55, 10));
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
    ImGui::EndChild();
```

Drawing background:

```c++
drawlist2->AddImage((void *)(intptr_t)bg.GetID(), ImVec2(0,0), ImVec2(1370,700));
```


### Some random old code
```c++
ImGui::Begin("lolsuprise");
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
ImGui::Dummy(ImVec2((set[0] + set[1]) * 10.2f, (set[0] + se[1]) * 3.0f));
ImGui::PopItemWidth();

ImGui::End();
```

### Treeview menu
```c++
ImGui::SetNextWindowPos(ImVec2(0, 75));
ImGui::SetNextWindowSize(ImVec2(300, wheight));
ImGui::BeginChild("Menu2", ImVec2(300, wheight), true);
if (ImGui::BeginTable("split", 2, ImGuiTableFlags_BordersOuter | ImGuiTableFlags_Resizable))
{
    //ShowPlaceholderObject("Menu");
    //ImGui::Separator();
    ImGui::EndTable();
}
ImGui::EndChild();,
```