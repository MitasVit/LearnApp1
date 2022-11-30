#ifndef UTILS_H
#define UTILS_H

#include <iostream>
#include <ctime>
#include <cstring>
#include <clocale>
#include <codecvt>
#include <stdexcept>
#include <vector>

using namespace std;

void char2str(char * buf, string* to);
string char2str(char* buf);

char* string2char(string s);

u32string string2u32string(string ustr);

string Date2Str();
char* Date2Char();


#endif