#include <cstdlib>
#include <cstdio>
#include <cstring>

#include <curlpp/cURLpp.hpp>
#include <curlpp/Easy.hpp>
#include <curlpp/Options.hpp>
#include <curlpp/Exception.hpp>
#include <curlpp/Infos.hpp>

#include <rapidjson/rapidjson.h>
#include <rapidjson/document.h>
#include <rapidjson/writer.h>
#include <rapidjson/stringbuffer.h>

#include <fstream>
#include <sstream>

using namespace std;
using namespace placeholders;
using namespace curlpp;
using namespace Options;
using namespace rapidjson;

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


int main(){
    string login = "https://bakalari.gympolicka.cz/api/login", about_me = " https://bakalari.gympolicka.cz/api/3/user";
    string bearer_token = "";


    try{
		Easy request2;

        request2.setOpt(new options::WriteStream(&cout));
	//	request2.setOpt(new Verbose(true));


        string query = "client_id=ANDR&grant_type=password&username=070401zvcj&password=Pomezi77";
        request2.setOpt(new options::PostFields(query)); 

        request2.setOpt(new Url(login.c_str()));
        ofstream response("out.json");
        request2.setOpt(new options::WriteStream(&response));

        list<string> headers2;
        headers2.push_back("Connection: close");
        headers2.push_back("Keep-Alive: 60");
        request2.setOpt(new HttpHeader(headers2));

        request2.perform();
        cout <<  endl << endl << "[48;5;19m dont know what to do, styl finding, dont know what to do[0m" << endl << endl;
        request2.reset();
        
    }catch ( LogicError & e )
	{
		cout << "[48;5;19m" << e.what() << "[0m" << endl;
	}

	catch ( RuntimeError & e )
	{
		cout  << "[48;5;19m" << e.what() << "[0m" << endl;
	}

    try{
		Easy request;

        string out = File2Str("out.json");

        Document d;
        d.Parse(out.c_str());
        // 2. Modify it by DOM.
        Value& s = d["access_token"];
        bearer_token = s.GetString();

        list<string> headers;
        string full = "Authorization: " + bearer_token;
		headers.push_back(full);
        headers.push_back("Connection: close");


        request.setOpt(new options::WriteStream(&cout));
//		request.setOpt(new Verbose(true));

        request.setOpt(new HttpHeader(headers));
		request.setOpt(new Url(about_me.c_str()));

		request.perform();

    }catch ( LogicError & e )
	{
		cout << "[48;5;19m" << e.what() << "[0m" << endl;
	}

	catch ( RuntimeError & e )
	{
		cout  << "[48;5;19m" << e.what() << "[0m" << endl;
	}

	return 0;
}