#include <iostream>

#include <cstdlib>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <vector>

#include <curlpp/cURLpp.hpp>
#include <curlpp/Easy.hpp>
#include <curlpp/Multi.hpp>
#include <curlpp/Options.hpp>
#include <curlpp/Exception.hpp>

#include <rapidjson/rapidjson.h>
#include <rapidjson/document.h>
#include <rapidjson/writer.h>
#include <rapidjson/stringbuffer.h>
#include <rapidjson/error/error.h>

using namespace std;
using namespace curlpp;
using namespace curlpp::options;
using namespace placeholders;
using namespace Options;
using namespace rapidjson;

string ReplaceAll(string str, const string& from, const string& to);
string StringToHttpRequest(string text);
string File2Str(string path);

map<string, string> mapForAttributeThatMatchesName(const Value& attributes, const string& findMemberName, const string& findMemberValue, const vector<string>& keysToRetrieve);

int FindVal(string *arr, int arr_size, string what);
int FindVal(int *arr, int arr_size, int what);
template<typename T>
int FindVal(T *arr, int arr_size, T what);

class TimeTableLesson{
public:
    string teacherfull, teacherabbrev, from, to, cycles;
    string subjectfull, subjectabbrev, gropufull, groupabbrev;
    string roomfull, roomabbrev, theme;

    bool is_empty;

    //room, teacher, date, homework, theme, subject, group, cycles[lichy/sudy]
    void Setup(string _teacherfull, string  _teacherabbrev, string  _from, string  _to, string _cycles, string _subjectfull, string _subjectabbrev, string _gropufull, string _groupabbrev, string _roomabbrev, string _roomfull);
    void Setup(TimeTableLesson a);

    TimeTableLesson();
    TimeTableLesson(string _teacherfull, string  _teacherabbrev, string  _from, string  _to, string _cycles, string _subjectfull, string _subjectabbrev, string _gropufull, string _groupabbrev, string _roomabbrev, string _roomfull);
};

bool isTimeTableLEmpty(TimeTableLesson &a);

class TimeTable{
public:
    TimeTableLesson lessons[5][15];
    TimeTable();
    //ndays - number of days
    //nlessons - number of lessons
    TimeTable(int ndays, int nlessons);
    void Load(string path);
};

struct city{
  const char*name;//city name
  int count;//count of schools there
};

struct school{
  const char*id, *name, *school_url;
};
/*
/api/3/marks
"Content-Type: application/x-www-form-urlencoded"

*/
class BakalariUser
{
public:
  //viz https://github.com/bakalari-api/bakalari-api-v3

  //podle seznamu mest z curl https://sluzby.bakalari.cz/api/v1/municipality -H "Accept: application/json" 
  // pak muzeme nazev mesta dosasdit do: curl https://sluzby.bakalari.cz/api/v1/municipality/$NAZEV_MESTA -H "Accept: application/json"
  // cimz ziskame vsechny skoly v danem meste + jejich bakalari url adresy
  //pr.: curl https://sluzby.bakalari.cz/api/v1/municipality/Poli&#269;ka -H "Accept: application/json"

  //ziskani ukolu curl -H "Content-Type: application/x-www-form-urlencoded" -H "Authorization: Bearer " https://bakalari.gympolicka.cz/api/3/homeworks

  //ziskani akt. rozvrhu curl -H "Content-Type: application/x-www-form-urlencoded" -H "Authorization: Bearer ACCESS_TOKEN" https://bakalari.gympolicka.cz/api/3/timetable/actual?date=YYYY-MM-dd
  string schoolurl;
  string username, password, atoken;//atoken - bearer
  string fullname, classname, classabbrev, usertype, usertypetext;

  bool Login(string _uname, string _upass, string *error=NULL, string *errordes=NULL);
  void WriteUserInfo(string path);
  void WriteLogin(string _uname, string _upass, string path);
  void LoadUserInfo(string path);
  void LoadWriteUserInfo(string path);

  //pernament timetable as a json to file with path
  void GetPerTimeTable(string path);
  //actual timetable as a json to file with path
  // date has format: YYYY-MM-dd
  void GetActTimeTable(string path, string date);

  //pernament timetable as a json to file with path
  TimeTable GetPerTimeTable2(string path);
  //actual timetable as a json to file with path
  // date has format: YYYY-MM-dd
  TimeTable GetActTimeTable2(string path, string date);


  void SaveMarksToFile(string path);

  void GetCityList(string path);

  //cityname must be a html string
  void GetSchools(string path, string cityname);

  void SetSchoolUrl(string schoolurl_);
  string GetAccesToken();

};

//fpath - path to file, which will be crated 
school *GetSchoolsByCity(string fpath, string cityname);

//fpath - path to file, which will be crated 
school *GetSchoolsByCity(string fpath, city c);
