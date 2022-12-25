#include <iostream>

using namespace std;

int main(){
    int n,m;//n - velikost policek(n*n), m - velikost sachovnice(m*m)

    cout << "Zadejte n: ";
    cin >> n;

    cout << "Zadejte m: ";
    cin >> m;

    //tisk horniho radku
    cout << "+";
    for(int i = 0; i < (m*n); i++){
        cout << "-";
    }
    cout << "+" << endl;

    bool tento = false; // 0-cerny, 1-bily
    for (int i = 0; i < n; i++)
    {
        for (int x = 0; x < m; x++)
        {
            cout << "|";
            for (int z = 0; z < m; z++)
            {
                for (int y = 0; y < n; y++)
                {
                    if (tento == false)
                    {
                        cout << "A";
                    }
                    else
                    {
                        cout << "X";
                    }
                }
                if (tento == false)
                {
                    tento = true;
                }
                else
                {
                    tento = false;
                }
            }
            cout << "|" << endl;
            if ((x % n) == 0)
            {
                if (tento == false)
                {
                    tento = true;
                }
                else
                {
                    tento = false;
                }
            }
        }
    }

    //tisk dolniho radku
    cout << "+";
    for(int i = 0; i < (m*n); i++){
        cout << "-";
    }
    cout << "+" << endl;
}