#include <iostream>

#include <cstdlib>
#include <fstream>
#include <sstream>
#include <stdexcept>

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

struct ParseException : std::runtime_error, rapidjson::ParseResult {
  ParseException(rapidjson::ParseErrorCode code, const char* msg, size_t offset)
    : std::runtime_error(msg), ParseResult(code, offset) {}
};

string ReplaceAll(string str, const string& from, const string& to) {
    size_t start_pos = 0;
    while ((start_pos = str.find(from, start_pos)) != string::npos) {
        str.replace(start_pos, from.length(), to);
        start_pos += to.length();
    }
    return str;
}
string StringToHttpRequest(string text) {
    //viz https://www.w3schools.com/tags/ref_urlencode.asp
    string tmp = text;
    tmp = ReplaceAll(tmp, " ", "%20");
    tmp = ReplaceAll(tmp, "\n", "%0D%0A");//CRLF
    tmp = ReplaceAll(tmp, "\t", "%09");
    return tmp;
}

string File2Str(string path){
    ifstream t(path.c_str());
    stringstream buffer;
    buffer << t.rdbuf();
    return buffer.str();
}

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

  string username, password, atoken;//atoken - bearer
  string fullname, classname, classabbrev, usertype, usertypetext;

  void Login(string _uname, string _upass);
  void WriteUserInfo(string path);
  void WriteLogin(string _uname, string _upass, string path);
  void LoadUserInfo(string path);
  void LoadWriteUserInfo(string path);

  //peranment timetable as a json to file with path
  void GetPerTimeTable(string path);
  //actual timetable as a json to file with path
  // date has format: YYYY-MM-dd
  void GetActTimeTable(string path, string date);

  void GetCityList(string path);

  //cityname must be a html string
  void GetSchools(string path, string cityname);

  string GetAccesToken();

};


void BakalariUser::GetSchools(string path, string cityname){
  try{
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

void BakalariUser::GetCityList(string path){
  try{
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

void BakalariUser::GetActTimeTable(string path, string date){
  try{
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

void BakalariUser::GetPerTimeTable(string path){
  try{
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

void BakalariUser::LoadWriteUserInfo(string path){
try{
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

void BakalariUser::LoadUserInfo(string path){
  try{
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
  catch (ParseException &e){
    cout << e.what() << endl;
  }
}

string BakalariUser::GetAccesToken(){
  return atoken;
}

void BakalariUser::Login(string _uname, string _upass){
  try{
    Easy loginreq;
    stringstream response;
    string query = "client_id=ANDR&grant_type=password&username="+_uname+"&password="+_upass+"";
    loginreq.setOpt(new Url("https://bakalari.gympolicka.cz/api/login"));
    loginreq.setOpt(new PostFields(query));
    loginreq.setOpt(new WriteStream(&response));
    loginreq.perform();
    //load the response json and read the access token
    Document d;
    ParseResult pr = d.Parse(response.str().c_str());
    Value& s = d["access_token"];
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
  catch (ParseException &e){
    cout << e.what() << endl;
  }
  
}

void BakalariUser::WriteLogin(string _uname, string _upass, string path){
  try{
    Easy loginreq;
    string query = "client_id=ANDR&grant_type=password&username="+_uname+"&password="+_upass+"";
    ofstream response(path.c_str());
    loginreq.setOpt(new Url("https://bakalari.gympolicka.cz/api/login"));
    loginreq.setOpt(new PostFields(query));
    loginreq.setOpt(new WriteStream(&response));
    loginreq.perform();
    response.close();
    Document d;
    ParseResult pr = d.Parse(File2Str(path.c_str()).c_str());
    Value& s = d["access_token"];
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
  catch (ParseException &e){
    cout << e.what() << endl;
  }
}
void BakalariUser::WriteUserInfo(string path){
  try{
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
}

int main(int argc, char *argv[])
{
  BakalariUser ja;
  ja.WriteLogin("070401zvcj", "Pomezi77", "login.json");
  //cout << ja.GetAccesToken();
  ja.LoadWriteUserInfo("info.json");
  ja.GetActTimeTable("actimetable.json", "2022-10-14");
  cout << ja.fullname << " chodí do třídy: " << ja.classname << "(" << ja.classabbrev << ")" << endl;
  return 0;
}
