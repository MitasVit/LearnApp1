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

using namespace std;
using namespace curlpp;
using namespace curlpp::options;
using namespace placeholders;
using namespace Options;

void perform(int id){
    Easy uireq;
    string path = "https://www.ibobr.cz/test/blockly/get/" + to_string(id);
    list<string> headers;
   // string full = "Authorization: Bearer " + atoken;
    headers.push_back("Content-Type: application/x-www-form-urlencoded");
    headers.push_back("Accept: application/json");
	//	headers.push_back(full);

    uireq.setOpt(new Url(path.c_str()));
    uireq.setOpt(new WriteStream(&cout));
    uireq.setOpt(new HttpHeader(headers));
    uireq.perform();
}

int main(){
    for(int i =0; i < 3000;i++){
        cout << "i: " << i << "|: ";perform(i);cout << endl;
    }
    return 0;
}