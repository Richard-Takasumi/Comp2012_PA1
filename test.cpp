#include <iostream>


using namespace std;

int main () {

   
    int* x = new int[5]{1,2,3,4};

    x[4] = 69;

    for (int i = 0; i < 5; i++) {
        cout << x[i] << endl;
    }


}