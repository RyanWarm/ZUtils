#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <boost/algorithm/string/split.hpp>
#include <boost/algorithm/string/classification.hpp>
using namespace std;

int main() {
    string fName = "com_only_prob";
    ifstream ifs(fName.c_str());
    if( !ifs.is_open() ) return 0;
    string str;
    while( getline(ifs,str) ) {
        vector<string> tokens;
        boost::split(tokens, str, boost::is_any_of("\t"));
        for( vector<string>::iterator it = tokens.begin(); it != tokens.end(); ++it ) cout << *it << endl;
    }
    return 0;
}