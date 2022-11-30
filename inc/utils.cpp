#include "utils.h"

using namespace std;

void char2str(char * buf, string* to){
	cout << "Char2Str" << endl;
	for (int x = 0; x < (sizeof(buf) / sizeof(char)); x++) { 
		to = to + buf[x]; 
	} 
}

string char2str(char* buf){
	cout << "Char2Str2" << endl;
	string tmp;
	for (int x = 0; (x < (sizeof(buf) / sizeof(char)) + 1); x++) { 
		tmp = tmp + buf[x]; 
	} 
	return tmp;
}

string Date2Str(){
	cout << "Date2Str" << endl;
	time_t curr_time;
	tm * curr_tm;
	char date_string[100];
	
	time(&curr_time);
	curr_tm = localtime(&curr_time);
	
	strftime(date_string, 50, "%T %D", curr_tm);
	string tmp;
	char2str(date_string, &tmp);
	return tmp;
}

char* Date2Char(){
	cout << "Date2Char" << endl;
	cout << "time_t curr_time;" << endl;
	time_t curr_time;
	cout << "tm * curr_tm;" << endl;
	tm * curr_tm;
	cout << "char date_string[50];" << endl;
	char *date_string =new char[50];
	
	cout << "time(&curr_time);" << endl;
	time(&curr_time);
	cout << "curr_tm = localtime(&curr_time);" << endl;
	curr_tm = localtime(&curr_time);
	cout << "strftime(date_string, 50, \"%T %D\", curr_tm);" << endl;
	strftime(date_string, 48, "%T %D", curr_tm);
	cout << "return date_string;" << endl;
	return date_string;
}

char* string2char(string s, int* lenght = nullptr){
    int n = s.length();
    *lenght = n;
 
    // declaring character array
    char *char_array = new char[n + 1];
 
    // copying the contents of the
    // string to char array
    strcpy(char_array, s.c_str());
 
    return char_array;
}

u32string string2u32string(string str){
    u32string s32(str.begin(), str.end());
    return s32;
}
