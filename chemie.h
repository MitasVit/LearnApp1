#pragma once

#include <iostream>

using namespace std;

struct prvek {
    string znacka="";//znacka prvku
    float eleneg=0.0;//elektronegativita
    bool operator==(prvek& prv) {
        if ((prv.znacka == this->znacka)&& (prv.eleneg == this->eleneg)) {
            return true;
        }
        else {
            return false;
        }
    }
};

extern prvek null_prvek = { "", -1 };//chybny prvek pro vraceni funkci

string PTP[7][18] = { {"H", "He"},
{"Li", "Be", "B", "C", "N", "O", "F", "Ne"},
{"Na", "Mg", "Al", "Si", "P", "S", "Cl", "Ar"},
{"K", "Ca", "Sc", "Ti", "V", "Cr", "Mn", "Fe", "Co", "Ni", "Cu", "Zn", "Ga", "Ge", "As", "Se", "Br", "Kr"},
{"Rb", "Sr", "Y", "Zr", "Nb", "Mo", "Tc", "Ru", "Rh", "Pd", "Ag", "Cd", "In", "Sn", "Sb", "Te", "I", "Xe"},
{"Cs", "Ba", "Lu", "Hf", "Ta", "W", "Re", "Os", "Ir", "Pt", "Au", "Hg", "Tl", "Pb", "Bi", "Po", "At", "Rn"},
{"Fr", "Ra", "Lr", "Rf", "Db", "Sg", "Bh", "Hs"} };


float EleNeg[7][18] = { {2.2, 0},
{0.98, 1.57, 2.04, 2.55, 3.04, 3.44, 3.98, 4},
{0.93, 1.31, 1.61, 1.9, 2.19, 2.58, 3.16, 3.9},
{0.82, 1, 1.36, 1.54, 1.63, 1.66, 1.55, 1.83, 1.88, 1.91, 1.95, 1.65, 1.81, 2.01, 2.18, 2.55, 2.96, 3},
{0.82, 0.95, 1.22, 1.33, 1.6, 2.16, 1.9, 2.2, 2.28, 2.2, 1.93, 1.69, 1.78, 1.96, 2.05, 2.1, 2.66, 2.6},
{0.79, 0.89, 1.27, 1.3, 1.5, 2.36, 1.9, 2.2, 2.2, 2.28, 2.54, 2, 1.62, 1.88, 2.02, 2, 2.2, 2.2},
{0.79, 0.89, 1.3, 0, 0, 0, 0, 0} };

//Kolik Sloupcu je dostupnych podle periody
int DostupneSloupce(int perioda) {
    switch (perioda) {
    case 0:
        return 2;
        break;
    case 1:
        return 7;
        break;
    case 2:
        return 7;
        break;
    case 3:
        return 17;
        break;
    case 4:
        return 17;
        break;
    case 5:
        return 17;
        break;
    case 6:
        return 7;
        break;
    default:
        return -1;
    }

}

//vrati prvek v ptp podle periody a sloupce - zadavejte realnou periodu a skupinu ( indexovani probehne precislovanim)
prvek DostanPrvek(int perioda, int sloupec) {
    //kontrola nezname elektronegativity
    if (EleNeg[perioda-1][sloupec-1] < 0.79) {//-1 -> precislovani, pr. 1. sloupec je 0. index
        return null_prvek;
    }
    //kontrola chybne periody
    if ((perioda > 7) || (perioda < 1)) {
        return null_prvek;
    }
    //kontrola chybneho sloupce
    if ((sloupec > 18) || (sloupec < 1)) {
        return null_prvek;
    }
    prvek tmp = { PTP[perioda-1][sloupec-1], EleNeg[perioda - 1][sloupec - 1]};
    return tmp;
}

//maximalni elektronegativita
float MaxEle() {
    float Max = EleNeg[0][0];
    float Min = EleNeg[0][0];
    for (int i = 0; i < 2; i++)
    {
        for (int j = 0; j < 2; j++)
        {
            if (EleNeg[i][j] > Max)
            {
                Max = EleNeg[i][j];
            }
            if (EleNeg[i][j] < Min)
            {
                Min = EleNeg[i][j];
            }
        }
    }
    return Max;
}

//minimalni elektronegativita
float MinEle() {
    float Min = EleNeg[0][0];
    for (int i = 0; i < 2; i++)
    {
        for (int j = 0; j < 2; j++)
        {
            if ((EleNeg[i][j] < Min) &&(EleNeg[i][j] =! 0)) // nepocitat chybnou elektronegativitu
            {
                Min = EleNeg[i][j];
            }
        }
    }
    return Min;
}

void VypisPtp() {
    for (int i = 0; i < 18; i++) {
        for (int y = 0; y < 7; y++) {
            cout << "prvek: " << PTP[y][i] << ", elektronegativita: " << EleNeg[y][i] << ", sloupec: " << y + 1 << ", perioda:" << i + 1 << endl;
        }
    }
}