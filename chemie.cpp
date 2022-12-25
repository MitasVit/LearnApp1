#include <iostream>
#include "chemie.h"

using namespace std;

string PTP_cislo[126] = { "H", "He","Li", "Be", "B", "C", "N", "O", "F", "Ne","Na", "Mg", "Al", "Si", "P", "S", "Cl", "Ar","K", "Ca", "Sc", "Ti", "V", "Cr", "Mn", "Fe", "Co", "Ni", "Cu", "Zn", "Ga", "Ge", "As", "Se", "Br", "Kr","Rb", "Sr", "Y", "Zr","Nb", "Mo", "Tc", "Ru", "Rh", "Pd", "Ag", "Cd", "In", "Sn", "Sb", "Te", "I", "Xe","Cs", "Ba", "La", "Ce", "Pr", "Nd", "Pm", "Sm", "Eu", "Gd", "Tb", "Dy", "Ho", "Er", "Tm", "Yb", "Lu", "Hf", "Ta", "W", "Re", "Os", "Ir", "Pt", "Au", "Hg", "Tl", "Pb", "Bi", "Po", "At", "Rn","Fr", "Ra", "Ac", "Th", "Pa", "U", "Np", "Pu", "Am", "Cm", "Bk", "Cf", "Es", "Fm", "Md", "No", "Lr", "Rf", "Db", "Sg", "Bh", "Hs" };


int main(){
    int poc_nukleonu = 0, poc_protonu = 0;
    int pr_n = 0, pr_p = 0;
    cout << "typy zreni:" << endl;
    cout << "1. alfa" << endl;
    cout << "2. beta" << endl;
    cout << "3. gamma" << endl;
    cout << "4. pozitronove" << endl;
    cout << "5. e. zachyt" << endl;
    cout << endl << "Zadejte poc. protonu: ";
    cin >> poc_protonu;
    cout << endl << "Zadejte poc. nukleonu: ";
    cin >> poc_nukleonu;
    cout << endl << "Zadejte typ zareni: ";
    int typ = 1;
    pr_n = poc_nukleonu;
    pr_p = poc_protonu;
    cin >> typ;
    if(typ == 1){
        cout << "1. alfa" << endl;
        poc_protonu -= 2;
        poc_nukleonu -= 4;
        cout << "poc_protonu: " << poc_protonu << endl;
        cout << "poc_nukleonu: " << poc_nukleonu << endl;
    }else if(typ == 2){
        cout << "2. beta" << endl;
        poc_protonu += 1;
        cout << "poc_protonu: " << poc_protonu << endl;
        cout << "poc_nukleonu: " << poc_nukleonu << endl;
    }else if(typ == 3){
        cout << "3. gamma" << endl;
        cout << "poc_protonu: " << poc_protonu << endl;
        cout << "poc_nukleonu: " << poc_nukleonu << endl;
    }else if(typ == 4){
        cout << "4. pozitronove" << endl;
        poc_protonu -= 1;
        cout << "poc_protonu: " << poc_protonu << endl;
        cout << "poc_nukleonu: " << poc_nukleonu << endl;
    }else if(typ == 5){
        cout << "5. e. zachyt" << endl;
        poc_protonu -= 1;
        cout << "poc_protonu: " << poc_protonu << endl;
        cout << "poc_nukleonu: " << poc_nukleonu << endl;
    }else{
        cout << "nezname zareni " << endl;
    }


    if(typ != 5){
        cout << "prvek: " << PTP_cislo[pr_p-1]<<  "(" << pr_n << ", " << pr_p << ")" << "- se premenil na: " << PTP_cislo[poc_protonu-1] << "(" << poc_nukleonu << ", " << poc_protonu << ")";
    }
    
    
    if(typ == 1){
        cout << " + He(4, 2)" << endl;
    }else if(typ == 2){
        cout << " + e(0, -1)" << endl;
    }else if(typ == 3){
        cout << " + e(0, 0)" << endl;
    }else if(typ == 4){
        cout << " + e(0, 1)" << endl;
    }else if(typ == 5){
        cout << "prvek: " << PTP_cislo[pr_p-1]<<  "(" << pr_n << ", " << pr_p << ")" << " + e(0, -1) - se premenil na: " << PTP_cislo[poc_protonu-1] << "(" << poc_nukleonu << ", " << poc_protonu << ")" << " + neutrino" << endl;
    }else{
        cout << endl << "nezname zareni " << endl;
    }
    //for(int i =0; i < 107;i++){
        //cout << "i: " << i << endl;
        //cout << "pcislo: " << PTP_cislo[i] <<endl;
        //cout << "p: " << PTP[i] << endl;
   // }
    return 0;
} 