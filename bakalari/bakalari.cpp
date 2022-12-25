#include <bakalari.h>

using namespace std;
using namespace curlpp;
using namespace curlpp::options;
using namespace placeholders;
using namespace Options;
using namespace rapidjson;

string ReplaceAll(string str, const string &from, const string &to)
{
  size_t start_pos = 0;
  while ((start_pos = str.find(from, start_pos)) != string::npos)
  {
    str.replace(start_pos, from.length(), to);
    start_pos += to.length();
  }
  return str;
}
string StringToHttpRequest(string text)
{
  // viz https://www.w3schools.com/tags/ref_urlencode.asp
  string tmp = text;
  tmp = ReplaceAll(tmp, " ", "%20");
  tmp = ReplaceAll(tmp, "\n", "%0D%0A"); // CRLF
  tmp = ReplaceAll(tmp, "\t", "%09");
  return tmp;
}

string File2Str(string path)
{
  ifstream t(path.c_str());
  stringstream buffer;
  buffer << t.rdbuf();
  return buffer.str();
}

bool isTimeTableLEmpty(TimeTableLesson &a){
  if((a.teacherabbrev !="") && (a.teacherfull != "") && (a.from != "") && (a.to != "")){
    return false;
  } 
  return true;
}

map<string, string> mapForAttributeThatMatchesName(const Value &attributes, const string &findMemberName, const string &findMemberValue, const vector<string> &keysToRetrieve)
{

  map<string, string> result;
  for (Value::ConstValueIterator itr = attributes.Begin(); itr != attributes.End(); ++itr)
  {

    const Value::ConstMemberIterator currentAttribute = itr->FindMember(findMemberName.c_str());
    if (currentAttribute != itr->MemberEnd() && currentAttribute->value.IsString())
    {

      if (currentAttribute->value == findMemberValue.c_str())
      {

        for (auto &keyToRetrieve : keysToRetrieve)
        {

          const Value::ConstMemberIterator currentAttributeToReturn = itr->FindMember(keyToRetrieve.c_str());
          if (currentAttributeToReturn != itr->MemberEnd() && currentAttributeToReturn->value.IsString())
          {

            result[keyToRetrieve] = currentAttributeToReturn->value.GetString();
          }
        }
        return result;
      }
    }
  }
  return result;
}

int FindVal(string *arr, int arr_size, string what)
{
  for (int i = 0; i < arr_size; i++)
  {
    if (arr[i] == what)
    {
      return i;
    }
  }
  return -1;
}

int FindVal(int *arr, int arr_size, int what)
{
  for (int i = 0; i < arr_size; i++)
  {
    if (arr[i] == what)
    {
      return i;
    }
  }
  return -1;
}

template <typename T>
int FindVal(T *arr, int arr_size, T what)
{
  for (int i = 0; i < arr_size; i++)
  {
    if (arr[i] == what)
    {
      return i;
    }
  }
  return -1;
}

struct ParseException : runtime_error, ParseResult
{
  ParseException(ParseErrorCode code, const char *msg, size_t offset)
      : runtime_error(msg), ParseResult(code, offset) {}
};

TimeTableLesson::TimeTableLesson(string _teacherfull, string _teacherabbrev, string _from, string _to, string _cycles, string _subjectfull, string _subjectabbrev, string _gropufull, string _groupabbrev, string _roomabbrev, string _roomfull)
{
  teacherfull = _teacherfull;
  teacherabbrev = _teacherabbrev;
  from = _from;
  to = _to;
  cycles = _cycles;
  subjectabbrev = _subjectabbrev;
  subjectfull = _subjectfull;
  groupabbrev = _groupabbrev;
  gropufull = _gropufull;
  roomabbrev = _roomabbrev;
  roomfull = _roomfull;
  is_empty = true;
}

TimeTableLesson::TimeTableLesson()
{
  teacherfull = "";
  teacherabbrev = "";
  from = "";
  to = "";
  cycles = "";
  subjectabbrev = "";
  subjectfull = "";
  groupabbrev = "";
  gropufull = "";
  roomabbrev = "";
  roomfull = "";
    is_empty = true;
}

void TimeTableLesson::Setup(string _teacherfull, string _teacherabbrev, string _from, string _to, string _cycles, string _subjectfull, string _subjectabbrev, string _gropufull, string _groupabbrev, string _roomabbrev, string _roomfull)
{
  teacherfull = _teacherfull;
  teacherabbrev = _teacherabbrev;
  from = _from;
  to = _to;
  cycles = _cycles;
  subjectabbrev = _subjectabbrev;
  subjectfull = _subjectfull;
  groupabbrev = _groupabbrev;
  gropufull = _gropufull;
  roomabbrev = _roomabbrev;
  roomfull = _roomfull;
  is_empty = true;
}

void TimeTableLesson::Setup(TimeTableLesson a)
{
  teacherfull = a.teacherfull;
  teacherabbrev = a.teacherabbrev;
  from = a.from;
  to = a.to;
  cycles = a.cycles;
  subjectabbrev = a.subjectabbrev;
  subjectfull = a.subjectfull;
  groupabbrev = a.groupabbrev;
  gropufull = a.gropufull;
  roomabbrev = a.roomabbrev;
  roomfull = a.roomfull;
}

TimeTable::TimeTable()
{
}

TimeTable::TimeTable(int ndays, int nlessons)
{
}

void TimeTable::Load(string path)
{
  try
  {
    Document d;
    ParseResult pr = d.Parse(File2Str(path.c_str()).c_str());

    /*

    Section: hours layout load

    */

    int *h_id;
    string *h_caption, *h_begin, *h_end;

    const Value &hours = d["Hours"];
    assert(hours.IsArray());

    h_id = new int[hours.Size()];
    h_caption = new string[hours.Size()];
    h_begin = new string[hours.Size()];
    h_end = new string[hours.Size()];

    int i = 0;
    for (Value::ConstValueIterator itr = hours.Begin(); itr != hours.End(); ++itr)
    {
      const Value &hour = *itr;
      assert(hour.IsObject()); // each attribute is an object
      for (Value::ConstMemberIterator itr2 = hour.MemberBegin(); itr2 != hour.MemberEnd(); ++itr2)
      {
        if (itr2->name.IsString())
        {
          string a(itr2->name.GetString());
          if (a == "Id")
          {
            // cout << itr2->name.GetString() << ":" << itr2->value.GetInt() << endl;
            h_id[i] = itr2->value.GetInt();
          }
          else if (a == "Caption")
          {
            // cout << itr2->name.GetString() << ":" << itr2->value.GetString() << endl;
            h_caption[i] = itr2->value.GetString();
          }
          else if (a == "BeginTime")
          {
            // cout << itr2->name.GetString() << ":" << itr2->value.GetString() << endl;
            h_begin[i] = itr2->value.GetString();
          }
          else if (a == "EndTime")
          {
            // cout << itr2->name.GetString() << ":" << itr2->value.GetString() << endl;
            h_end[i] = itr2->value.GetString();
          }
        }
      }
      i++;
    }


    /*

    Section: class load

    */
    string *c_id, *c_abbrev, *c_name;

    const Value &classes = d["Classes"];
    assert(classes.IsArray());

    c_id = new string[classes.Size()];
    c_abbrev = new string[classes.Size()];
    c_name = new string[classes.Size()];

    i = 0;

    for (Value::ConstValueIterator itr = classes.Begin(); itr != classes.End(); ++itr)
    {
      const Value &classs = *itr;
      assert(classs.IsObject()); // each attribute is an object
      for (Value::ConstMemberIterator itr2 = classs.MemberBegin(); itr2 != classs.MemberEnd(); ++itr2)
      {
        if (itr2->name.IsString())
        {
          string a(itr2->name.GetString());
          if (a == "Id")
          {
            c_id[i] = itr2->value.GetString();
          }
          else if (a == "Name")
          {
            c_name[i] = itr2->value.GetString();
          }
          else if (a == "Abbrev")
          {
            c_abbrev[i] = itr2->value.GetString();
          }
        }
      }
      i++;
    }

    /*

    Section: groups load

    */

    string *g_id, *g_abbrev, *g_name, *g_classid; // g_classid jeste nevim co je

    const Value &groups = d["Groups"];
    assert(groups.IsArray());

    g_id = new string[groups.Size()];
    g_classid = new string[groups.Size()];
    g_abbrev = new string[groups.Size()];
    g_name = new string[groups.Size()];

    i = 0;

    for (Value::ConstValueIterator itr = groups.Begin(); itr != groups.End(); ++itr)
    {
      const Value &group = *itr;
      assert(group.IsObject()); // each attribute is an object
      for (Value::ConstMemberIterator itr2 = group.MemberBegin(); itr2 != group.MemberEnd(); ++itr2)
      {
        if (itr2->name.IsString())
        {
          string a(itr2->name.GetString());
          if (a == "Id")
          {
            g_id[i] = itr2->value.GetString();
          }
          else if (a == "Name")
          {
            g_name[i] = itr2->value.GetString();
          }
          else if (a == "ClassId")
          {
            g_classid[i] = itr2->value.GetString();
          }
          else if (a == "Abbrev")
          {
            g_abbrev[i] = itr2->value.GetString();
          }
        }
      }
      i++;
    }

    /*

    Section: subjects load

    */

    string *s_id, *s_abbrev, *s_name;

    const Value &subjects = d["Subjects"];
    assert(subjects.IsArray());

    s_id = new string[subjects.Size()];
    s_abbrev = new string[subjects.Size()];
    s_name = new string[subjects.Size()];

    i = 0;

    for (Value::ConstValueIterator itr = subjects.Begin(); itr != subjects.End(); ++itr)
    {
      const Value &subject = *itr;
      assert(subject.IsObject()); // each attribute is an object
      for (Value::ConstMemberIterator itr2 = subject.MemberBegin(); itr2 != subject.MemberEnd(); ++itr2)
      {
        if (itr2->name.IsString())
        {
          string a(itr2->name.GetString());
          if (a == "Id")
          {
            s_id[i] = itr2->value.GetString();
            // cout << "new s_id[]: " << itr2->value.GetString() << "| i: " << i << endl;
          }
          else if (a == "Name")
          {
            s_name[i] = itr2->value.GetString();
            // cout << "new s_name[]: " << itr2->value.GetString() << "| i: " << i  << endl;
          }
          else if (a == "Abbrev")
          {
            s_abbrev[i] = itr2->value.GetString();
            // cout << "new s_abbrev[]: " << itr2->value.GetString() << "| i: " << i  << endl;
          }
        }
      }
      i++;
    }

    /*

    Section: teachers load

    */

    string *t_id, *t_abbrev, *t_name;

    const Value &teachers = d["Teachers"];
    assert(teachers.IsArray());

    t_id = new string[teachers.Size()];
    t_abbrev = new string[teachers.Size()];
    t_name = new string[teachers.Size()];

    i = 0;

    for (Value::ConstValueIterator itr = teachers.Begin(); itr != teachers.End(); ++itr)
    {
      const Value &teacher = *itr;
      assert(teacher.IsObject()); // each attribute is an object
      for (Value::ConstMemberIterator itr2 = teacher.MemberBegin(); itr2 != teacher.MemberEnd(); ++itr2)
      {
        if (itr2->name.IsString())
        {
          string a(itr2->name.GetString());
          if (a == "Id")
          {
            t_id[i] = itr2->value.GetString();
          }
          else if (a == "Name")
          {
            t_name[i] = itr2->value.GetString();
          }
          else if (a == "Abbrev")
          {
            t_abbrev[i] = itr2->value.GetString();
          }
        }
      }
      i++;
    }

    /*

    Section: rooms load

    */

    string *r_id, *r_abbrev, *r_name;

    const Value &rooms = d["Rooms"];
    assert(rooms.IsArray());

    r_id = new string[rooms.Size()];
    r_abbrev = new string[rooms.Size()];
    r_name = new string[rooms.Size()];

    i = 0;

    for (Value::ConstValueIterator itr = rooms.Begin(); itr != rooms.End(); ++itr)
    {
      const Value &room = *itr;
      assert(room.IsObject()); // each attribute is an object
      for (Value::ConstMemberIterator itr2 = room.MemberBegin(); itr2 != room.MemberEnd(); ++itr2)
      {
        if (itr2->name.IsString())
        {
          string a(itr2->name.GetString());
          if (a == "Id")
          {
            r_id[i] = itr2->value.GetString();
          }
          else if (a == "Name")
          {
            r_name[i] = itr2->value.GetString();
          }
          else if (a == "Abbrev")
          {
            r_abbrev[i] = itr2->value.GetString();
          }
        }
      }
      i++;
    }

    /*

    Section: cycles load

    */

    string *cy_id, *cy_abbrev, *cy_name;

    const Value &cycles = d["Cycles"];
    assert(cycles.IsArray());

    cy_id = new string[cycles.Size()];
    cy_abbrev = new string[cycles.Size()];
    cy_name = new string[cycles.Size()];

    i = 0;

    for (Value::ConstValueIterator itr = cycles.Begin(); itr != cycles.End(); ++itr)
    {
      const Value &cycle = *itr;
      assert(cycle.IsObject()); // each attribute is an object
      for (Value::ConstMemberIterator itr2 = cycle.MemberBegin(); itr2 != cycle.MemberEnd(); ++itr2)
      {
        if (itr2->name.IsString())
        {
          string a(itr2->name.GetString());
          if (a == "Id")
          {
            cy_id[i] = itr2->value.GetString();
          }
          else if (a == "Name")
          {
            cy_name[i] = itr2->value.GetString();
          }
          else if (a == "Abbrev")
          {
            cy_abbrev[i] = itr2->value.GetString();
          }
        }
      }
      i++;
    }

    const Value &days = d["Days"];
    assert(days.IsArray());
    int nthday = 0; // nth - day
    int l = 0;      // nth - lesson
    bool first = false;
    bool firstest = true;
    int this_hourid = -1, prev_hourid = -1;
    for (Value::ConstValueIterator itr = days.Begin(); itr != days.End(); ++itr)
    {
      // pro vsechny dny
      const Value &day = *itr;
      const Value &atoms = day["Atoms"];
      assert(atoms.IsArray()); // each attribute is an object
      for (Value::ConstValueIterator itr2 = atoms.Begin(); itr2 != atoms.End(); ++itr2)
      {
        TimeTableLesson *lesson = new TimeTableLesson();

        const Value &atom = *itr2;
        assert(atom.IsObject()); // each attribute is an object

        for (Value::ConstMemberIterator itr3 = atom.MemberBegin(); itr3 != atom.MemberEnd(); ++itr3)
        {
          if (itr3->name.IsString())
          {
            // cout << "je str" << endl;
            string a(itr3->name.GetString());
            if (a == "HourId")
            {
              // kolikata hodina
              int nth = FindVal(h_id, 15, itr3->value.GetInt());
              this_hourid = itr3->value.GetInt()-2;
              lesson->from = h_begin[nth];
              lesson->to = h_end[nth];
              cout << h_caption[nth] << ". hodina je od: " << h_begin[nth] << " do: " << h_end[nth] << endl;
              if (h_caption[nth] == "1")
              {
                l = 0;
                prev_hourid = -1;
              }
              if (!first)
              {
                // nebyl prvni
                l = h_id[nth] - 2;
                first = true;
              }
              if(firstest){
                l = 0;
                firstest = false;
              }
            }
            else if (a == "SubjectId")
            {
              // cout << "sid: " << itr3->value.GetString() << endl;
              int nth = FindVal(s_id, subjects.Size(), itr3->value.GetString());
              // cout<<"nth: " << nth << endl;
              lesson->subjectabbrev = s_abbrev[nth];
              lesson->subjectfull = s_name[nth];
              cout << "[" << s_abbrev[nth] << "]predmet: " << s_name[nth] << endl;
            }
            else if (a == "TeacherId")
            {
              int nth = FindVal(t_id, teachers.Size(), itr3->value.GetString());
              lesson->teacherabbrev = t_abbrev[nth];
              lesson->teacherfull = t_name[nth];
              cout << "[" << t_abbrev[nth] << "]ucitel: " << t_name[nth] << endl;
            }
            else if (a == "RoomId")
            {
              int nth = FindVal(r_id, rooms.Size(), itr3->value.GetString());
              if (r_name[nth] == "")
              {
                lesson->roomfull = "";
                lesson->roomabbrev = r_abbrev[nth];
                cout << "mistnost: " << r_abbrev[nth] << endl;
              }
              else
              {
                lesson->roomfull = r_name[nth];
                lesson->roomabbrev = r_abbrev[nth];
                cout << "[" << r_abbrev[nth] << "]mistnost: " << r_name[nth] << endl;
              }
            }
            else if (a == "Change")
            {
            }
            else if (a == "Theme")
            {
              lesson->theme = itr3->value.GetString();
              cout << "tema: " << itr3->value.GetString() << endl;
            }
          }
        }
        cout << "[34m adding lesson on[" + to_string(nthday) + "]]" + to_string(l) + "][0m" << endl;
        bool empty = isTimeTableLEmpty(*lesson);
        lesson->is_empty = empty;
        if(empty){
          cout << "[34m JE PRAZDNA [0m" << endl;
        }else{
          cout << "[34m NENI PRAZDNA [0m" << endl;
        }
        if(prev_hourid != -1){
          if((this_hourid - prev_hourid) > 1){
            TimeTableLesson *volnahodina = new TimeTableLesson();
            volnahodina->is_empty = true;
            lessons[nthday][l] = *volnahodina;
            l++;
          }
        }
        lessons[nthday][l] = *lesson;
        prev_hourid = this_hourid;
        // cout << "mistnost: " << t.lessons[nthday][l].teacherfull << "/" << lesson->teacherfull << endl;
        l++;
      }
      nthday++;
    }

    /* for(int y = 0; y < i; y++){
         cout << "id, " << y << ": " << h_id[y] << endl;
     }*/
  }
  catch (ParseException &e)
  {
    cout << e.what() << endl;
  }
}

void BakalariUser::GetSchools(string path, string cityname)
{
  try
  {
    Easy uireq;
    ofstream response(path.c_str());
    list<string> headers;
    // string full = "Authorization: Bearer " + atoken;
    headers.push_back("Content-Type: application/x-www-form-urlencoded");
    headers.push_back("Accept: application/json");
    //	headers.push_back(full);

    string url = "https://sluzby.bakalari.cz/api/v1/municipality/" + cityname;

    uireq.setOpt(new Url(url.c_str()));
    uireq.setOpt(new WriteStream(&response));
    uireq.setOpt(new HttpHeader(headers));
    uireq.perform();
    response.close();
  }
  catch (LogicError &e)
  {
    cout << e.what() << endl;
  }
  catch (RuntimeError &e)
  {
    cout << e.what() << endl;
  }
}

void BakalariUser::GetCityList(string path)
{
  try
  {
    Easy uireq;
    ofstream response(path.c_str());
    list<string> headers;
    // string full = "Authorization: Bearer " + atoken;
    headers.push_back("Content-Type: application/x-www-form-urlencoded");
    headers.push_back("Accept: application/json");
    //	headers.push_back(full);

    uireq.setOpt(new Url("https://sluzby.bakalari.cz/api/v1/municipality"));
    uireq.setOpt(new WriteStream(&response));
    uireq.setOpt(new HttpHeader(headers));
    uireq.perform();
    response.close();
  }
  catch (LogicError &e)
  {
    cout << e.what() << endl;
  }
  catch (RuntimeError &e)
  {
    cout << e.what() << endl;
  }
}

void BakalariUser::GetActTimeTable(string path, string date)
{
  try
  {
    Easy uireq;
    ofstream response(path.c_str());
    list<string> headers;
    string full = "Authorization: Bearer " + atoken;
    headers.push_back("Content-Type: application/x-www-form-urlencoded");
    headers.push_back(full);
    // headers.push_back("Connection: close");
    string url = "https://bakalari.gympolicka.cz/api/3/timetable/actual?date=" + date;
    uireq.setOpt(new Url(url.c_str()));
    uireq.setOpt(new WriteStream(&response));
    uireq.setOpt(new HttpHeader(headers));
    uireq.perform();
    response.close();
  }
  catch (LogicError &e)
  {
    cout << e.what() << endl;
  }
  catch (RuntimeError &e)
  {
    cout << e.what() << endl;
  }
}

void BakalariUser::GetPerTimeTable(string path)
{
  try
  {
    Easy uireq;
    ofstream response(path.c_str());
    list<string> headers;
    string full = "Authorization: Bearer " + atoken;
    headers.push_back("Content-Type: application/x-www-form-urlencoded");
    headers.push_back(full);
    // headers.push_back("Connection: close");

    uireq.setOpt(new Url("https://bakalari.gympolicka.cz/api/3/timetable/permanent"));
    uireq.setOpt(new WriteStream(&response));
    uireq.setOpt(new HttpHeader(headers));
    uireq.perform();
    response.close();
  }
  catch (LogicError &e)
  {
    cout << e.what() << endl;
  }
  catch (RuntimeError &e)
  {
    cout << e.what() << endl;
  }
}

TimeTable BakalariUser::GetActTimeTable2(string path, string date)
{
  try
  {
    Easy uireq;
    ofstream response(path.c_str());
    list<string> headers;
    string full = "Authorization: Bearer " + atoken;
    headers.push_back("Content-Type: application/x-www-form-urlencoded");
    headers.push_back(full);
    // headers.push_back("Connection: close");
    string url = "https://bakalari.gympolicka.cz/api/3/timetable/actual?date=" + date;
    uireq.setOpt(new Url(url.c_str()));
    uireq.setOpt(new WriteStream(&response));
    uireq.setOpt(new HttpHeader(headers));
    uireq.perform();
    response.close();

    cout << "----------LOADING TIMETABLE-----------" << endl;

    TimeTable test;
    test.Load(path.c_str());
    cout << "----------LOADED-----------" << endl;

    cout << "aaa: " << test.lessons[1][1].teacherfull << endl;
    return test;
  }
  catch (LogicError &e)
  {
    cout << e.what() << endl;
  }
  catch (RuntimeError &e)
  {
    cout << e.what() << endl;
  }
}

TimeTable BakalariUser::GetPerTimeTable2(string path)
{
  try
  {
    Easy uireq;
    ofstream response(path.c_str());
    list<string> headers;
    string full = "Authorization: Bearer " + atoken;
    headers.push_back("Content-Type: application/x-www-form-urlencoded");
    headers.push_back(full);
    // headers.push_back("Connection: close");

    uireq.setOpt(new Url("https://bakalari.gympolicka.cz/api/3/timetable/permanent"));
    uireq.setOpt(new WriteStream(&response));
    uireq.setOpt(new HttpHeader(headers));
    uireq.perform();
    response.close();

    TimeTable *test = new TimeTable();
    test->Load(path.c_str());
    return *test;
  }
  catch (LogicError &e)
  {
    cout << e.what() << endl;
  }
  catch (RuntimeError &e)
  {
    cout << e.what() << endl;
  }
}

void BakalariUser::LoadWriteUserInfo(string path)
{
  try
  {
    Easy uireq;
    ofstream response(path.c_str());
    list<string> headers;
    string full = "Authorization: Bearer " + atoken;
    headers.push_back(full);
    // headers.push_back("Connection: close");

    uireq.setOpt(new Url("https://bakalari.gympolicka.cz/api/3/user"));
    uireq.setOpt(new WriteStream(&response));
    uireq.setOpt(new HttpHeader(headers));
    uireq.perform();
    response.close();
    Document d;
    ParseResult pr = d.Parse(File2Str(path.c_str()).c_str());
    fullname = d["FullName"].GetString();
    classname = d["Class"]["Name"].GetString();
    classabbrev = d["Class"]["Abbrev"].GetString();
    usertype = d["UserType"].GetString();
    usertypetext = d["UserTypeText"].GetString();
  }
  catch (LogicError &e)
  {
    cout << e.what() << endl;
  }
  catch (RuntimeError &e)
  {
    cout << e.what() << endl;
  }
}

void BakalariUser::LoadUserInfo(string path)
{
  try
  {
    Document d;
    ParseResult pr = d.Parse(File2Str(path.c_str()).c_str());
    fullname = d["FullName"].GetString();
    classname = d["Class"]["Name"].GetString();
    classabbrev = d["Class"]["Abbrev"].GetString();
    usertype = d["UserType"].GetString();
    usertypetext = d["UserTypeText"].GetString();
  }
  catch (LogicError &e)
  {
    cout << e.what() << endl;
  }
  catch (RuntimeError &e)
  {
    cout << e.what() << endl;
  }
  catch (ParseException &e)
  {
    cout << e.what() << endl;
  }
}

string BakalariUser::GetAccesToken()
{
  return atoken;
}

void BakalariUser::Login(string _uname, string _upass)
{
  try
  {
    Easy loginreq;
    stringstream response;
    string query = "client_id=ANDR&grant_type=password&username=" + _uname + "&password=" + _upass + "";
    loginreq.setOpt(new Url("https://bakalari.gympolicka.cz/api/login"));
    loginreq.setOpt(new PostFields(query));
    loginreq.setOpt(new WriteStream(&response));
    loginreq.perform();
    // load the response json and read the access token
    Document d;
    ParseResult pr = d.Parse(response.str().c_str());
    Value &s = d["access_token"];
    atoken = s.GetString();
  }
  catch (LogicError &e)
  {
    cout << e.what() << endl;
  }
  catch (RuntimeError &e)
  {
    cout << e.what() << endl;
  }
  catch (ParseException &e)
  {
    cout << e.what() << endl;
  }
}

void BakalariUser::WriteLogin(string _uname, string _upass, string path)
{
  try
  {
    Easy loginreq;
    string query = "client_id=ANDR&grant_type=password&username=" + _uname + "&password=" + _upass + "";
    ofstream response(path.c_str());
    loginreq.setOpt(new Url("https://bakalari.gympolicka.cz/api/login"));
    loginreq.setOpt(new PostFields(query));
    loginreq.setOpt(new WriteStream(&response));
    loginreq.perform();
    response.close();
    Document d;
    ParseResult pr = d.Parse(File2Str(path.c_str()).c_str());
    Value &s = d["access_token"];
    atoken = s.GetString();
  }
  catch (LogicError &e)
  {
    cout << e.what() << endl;
  }
  catch (RuntimeError &e)
  {
    cout << e.what() << endl;
  }
  catch (ParseException &e)
  {
    cout << e.what() << endl;
  }
}
void BakalariUser::WriteUserInfo(string path)
{
  try
  {
    Easy uireq;
    ofstream response(path.c_str());
    list<string> headers;
    string full = "Authorization: Bearer " + atoken;
    headers.push_back(full);
    // headers.push_back("Connection: close");

    uireq.setOpt(new Url("https://bakalari.gympolicka.cz/api/3/user"));
    uireq.setOpt(new WriteStream(&response));
    uireq.setOpt(new HttpHeader(headers));
    uireq.perform();
    response.close();
  }
  catch (LogicError &e)
  {
    cout << e.what() << endl;
  }
  catch (RuntimeError &e)
  {
    cout << e.what() << endl;
  }
  catch (ParseException &e)
  {
    cout << e.what() << endl;
  }
  catch (exception &e)
  {
    cout << e.what() << endl;
  }
}

// fpath - path to file, which will be crated
school *GetSchoolsByCity(string fpath, string cityname)
{
  try
  {
    Easy uireq;
    ofstream response(fpath.c_str());
    list<string> headers;
    string full = "Accept: application/json";
    headers.push_back(full);
    // headers.push_back("Connection: close");

    string url = "https://sluzby.bakalari.cz/api/v1/municipality/" + cityname;

    uireq.setOpt(new Url(url.c_str()));
    uireq.setOpt(new WriteStream(&response));
    uireq.setOpt(new HttpHeader(headers));
    uireq.perform();
    response.close();

    Document d;
    d.Parse(fpath.c_str());
    const Value &schools = d["schools"];
    assert(schools.IsArray()); // each attribute is an object

    school *_schools = new school[schools.Size()];

    for (Value::ConstValueIterator itr2 = schools.Begin(); itr2 != schools.End(); ++itr2)
    {
      const Value &_school = *itr2;
      assert(_school.IsObject()); // each attribute is an object

      for (Value::ConstMemberIterator itr3 = _school.MemberBegin(); itr3 != _school.MemberEnd(); ++itr3)
      {
        if (itr3->name.IsString())
        {
          string a(itr3->name.GetString());
          if (a == "id")
          {
            _schools->id = itr3->value.GetString();
          }
          else if (a == "name")
          {
            _schools->name = itr3->value.GetString();
          }
          else if (a == "schoolUrl")
          {
            _schools->school_url = itr3->value.GetString();
          }
        }
      }
    }
    return _schools;
  }
  catch (LogicError &e)
  {
    cout << e.what() << endl;
  }
  catch (RuntimeError &e)
  {
    cout << e.what() << endl;
  }
  return NULL;
}

// fpath - path to file, which will be crated
school *GetSchoolsByCity(string fpath, city c)
{
  try
  {
    Easy uireq;
    ofstream response(fpath.c_str());
    list<string> headers;
    string full = "Accept: application/json";
    headers.push_back(full);
    // headers.push_back("Connection: close");
    string name(c.name);
    string url = "https://sluzby.bakalari.cz/api/v1/municipality/" + name;

    uireq.setOpt(new Url(url.c_str()));
    uireq.setOpt(new WriteStream(&response));
    uireq.setOpt(new HttpHeader(headers));
    uireq.perform();
    response.close();

    Document d;
    d.Parse(fpath.c_str());
    const Value &schools = d["schools"];
    assert(schools.IsArray()); // each attribute is an object

    school *_schools = new school[schools.Size()];

    for (Value::ConstValueIterator itr2 = schools.Begin(); itr2 != schools.End(); ++itr2)
    {
      const Value &_school = *itr2;
      assert(_school.IsObject()); // each attribute is an object

      for (Value::ConstMemberIterator itr3 = _school.MemberBegin(); itr3 != _school.MemberEnd(); ++itr3)
      {
        if (itr3->name.IsString())
        {
          string a(itr3->name.GetString());
          if (a == "id")
          {
            _schools->id = itr3->value.GetString();
          }
          else if (a == "name")
          {
            _schools->name = itr3->value.GetString();
          }
          else if (a == "schoolUrl")
          {
            _schools->school_url = itr3->value.GetString();
          }
        }
      }
    }
    return _schools;
  }
  catch (LogicError &e)
  {
    cout << e.what() << endl;
  }
  catch (RuntimeError &e)
  {
    cout << e.what() << endl;
  }
  return NULL;
}