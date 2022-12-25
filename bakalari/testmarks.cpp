#include <iostream>

#include <cstdlib>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <vector>
#include <rapidjson/rapidjson.h>
#include <rapidjson/document.h>
#include <rapidjson/writer.h>
#include <rapidjson/reader.h>
#include <rapidjson/stringbuffer.h>
#include <rapidjson/error/error.h>

using namespace std;
using namespace rapidjson;

#define RAPIDJSON_PARSE_ERROR_NORETURN(parseErrorCode,offset) \
   throw ParseException(parseErrorCode, #parseErrorCode, offset)
 
#include <stdexcept>               // std::runtime_error
#include "rapidjson/error/error.h" // rapidjson::ParseResult
 
struct ParseException : std::runtime_error, rapidjson::ParseResult {
  ParseException(rapidjson::ParseErrorCode code, const char* msg, size_t offset)
    : std::runtime_error(msg), ParseResult(code, offset) {}
};

/*
inc_dir="../../../../../../../../../../home/mitas/Bureau/programming/game/00build/lib/"
inc_dir2="../../../../../../../../../../home/mitas/Bureau/programming/game/00build/"
inc_dir3="../../../../../../../../../../home/mitas/Bureau/programming/game/00build/inc/"
inc_dir4="../../../../../../../../../../home/mitas/Bureau/programming/game/00build/bakalari/"

*/
//g++ -I $inc_dir -I $inc_dir2 -I $inc_dir3 -I $inc_dir4 testmarks.cpp -o tmark.out

class Subject
{
public:
};
class Mark
{
public:
    Mark(){

    }
};

/*
/api/3/marks
"Content-Type: application/x-www-form-urlencoded"

*/

int main()
{
    try
    {
        Document d;
        ParseResult pr = d.Parse("marks.json");
        if(pr.IsError()){
            cout << "ERRRORRRR" << endl;
            cout << pr.Code() << endl;
            cout << "offset: " << pr.Offset() << endl;
        }
        //todo here: pridat nacitace predmetu + id znamek 
        /*cout << endl << "2" << endl;
        const Value &MarkOptions = d["MarkOptions"];
                assert(MarkOptions.IsArray());

        //predmety
        cout << endl << "1" << endl;
        const Value &subjects = d["Subjects"];
               cout << endl << "1" << endl;
        assert(subjects.IsArray());
               cout << endl << "1" << endl;
        int nthsubject = 0; // nth - subject
        int tmark = 0;      // nth - lesson
               cout << endl << "1" << endl;
        for (Value::ConstValueIterator itr = subjects.Begin(); itr != subjects.End(); ++itr)
        {
                   cout << endl << "1" << endl;
            // pro vsechny dny
            const Value &subject = *itr;
                   cout << endl << "1" << endl;
            const Value &thismark = subject["Marks"];
                   cout << endl << "1" << endl;
            assert(thismark.IsArray()); // each attribute is an object
                   cout << endl << "1" << endl;
            for (Value::ConstValueIterator itr2 = thismark.Begin(); itr2 != thismark.End(); ++itr2)
            {
                Mark *lesson = new Mark();

                const Value &atom = *itr2;
                assert(atom.IsObject()); // each attribute is an object

                for (Value::ConstMemberIterator itr3 = atom.MemberBegin(); itr3 != atom.MemberEnd(); ++itr3)
                {
                    if (itr3->name.IsString())
                    {
                        // cout << "je str" << endl;
                        string a(itr3->name.GetString());
                        if (a == "MarkDate")
                        {
                            //datum pridani znamky
                            //2022-09-23T00:00:00+02:00
                            //YYYY-MM-DDTHH:MM:--------
                            //-- = mezajima
                            cout << "MarkDate: " << itr3->value.GetString();
                        }else if(a == "EditDate"){
                            //datum zmeny znamky
                            cout << "EditDate: " << itr3->value.GetString();
                        }else if(a == "Theme"){
                            //tema
                            cout << "Theme: " << itr3->value.GetString();
                        }
                        else if(a == "TypeNote"){
                            //poznamka k znamce - pr vaha
                            cout << "TypeNote: " << itr3->value.GetString();
                        }
                    }
                }
                tmark++;
            }
            nthsubject++;
        }*/
    }
    catch(ParseException &e){
        cout << e.what() << endl;
    }
    catch (exception &e)
    {
        cout << e.what() << endl;
    }
}