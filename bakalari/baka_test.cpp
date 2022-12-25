#include <bakalari.h>

int main(){
    /*TimeTable t;
    t.Load("actimetable.json");
    cout << "konec";*/

    BakalariUser ja;
    ja.WriteLogin("070401zvcj", "Pomezi77", "login.json");
    ja.LoadWriteUserInfo("info.json");
    TimeTable a = ja.GetActTimeTable2("actimetable.json", "2022-10-14");
    cout << "ucitel: " << a.lessons[2][2].teacherfull << endl;
    if(a.lessons[2][2].is_empty){
        cout<< "a.lessons[2][2] je PRAZDNY" <<endl;
    }else{
        cout<< "a.lessons[2][2] je V PORADKU" <<endl;
    }
    cout << ja.fullname << " chodí do třídy: " << ja.classname << "(" << ja.classabbrev << ")" << endl;
    //seg. fault
    //cout << endl << a.lessons[2][2]->subjectfull <<endl;
    return 0;

}