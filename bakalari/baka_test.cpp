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
