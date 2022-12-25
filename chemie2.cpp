#include <iostream>
#include <cmath>

using namespace std;

int main(){
    float aktivita0 = 0, aktivita=0, polocas =0;
    
    cout << "zadjte momentalni aktivitu: ";
    cin >> aktivita;
    cout << "zadjte pocatecni aktivitu: ";
    cin >> aktivita0;
    cout << "zadjte polocas rozpadu: ";
    cin >> polocas;
    cout << "log(aktivita/aktivita0): " << log((float)aktivita/(float)aktivita0) << endl;
    float doba = (float)polocas * ((log((float)aktivita/(float)aktivita0))/(-1 * (log(2))));
    cout << "doba: " << doba << endl;
     return 0;
}