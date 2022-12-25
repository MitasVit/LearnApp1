#include <iostream>
#include <cmath>

using namespace std;

int main(){
    float castic = 0, castic0=0, polocas =0;
    
    cout << "zadejte polocas rozpadu: ";
    cin >> polocas;
    cout << "zadejte cast pocatecnich castic -x, pricemz (N = x * N0): ";
    cin >> castic;
    float doba = (polocas*(log(castic)))/(-1*log(2));
    cout << "doba: " << doba << endl;
     return 0;
}