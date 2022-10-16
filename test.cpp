#include <iostream>
#include <cstring>


using namespace std;



int main () {

    char** c_arr = new char*[2];

    const char* s1{"hello"};
    const char* s2{"world2"};


    s1 = s2;

    cout << s1 << endl;;
}