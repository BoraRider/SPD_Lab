//Maciej Osak i Dominik Brzezina

#include <iostream>
#include "RandomNumberGenerator.h"
#include <algorithm>
#include <vector>
#include <queue>

#define PRZEDZIAL 29

using namespace std;

class problem
{
    public:
        int j;
        int p;
        int w;
        int d;
};
struct sort_deadline //czas d
{
    bool operator ()(const problem p1, const problem p2)
    {
        return p1.d > p2.d;
    }
};

void show_data(vector<problem> zadanie, int tmp[]){

    cout<<"j [";
    for(int i=0; i<zadanie.size() ; i++){ cout<<zadanie[ tmp[i] ].j<<", ";} cout<<"]"<<endl;
    cout<<"p [";
    for(int i=0; i<zadanie.size() ; i++){ cout<<zadanie[ tmp[i] ].p<<", ";} cout<<"]"<<endl;
    cout<<"w [ ";
    for(int i=0; i<zadanie.size(); i++){  cout<<zadanie[ tmp[i] ].w<<", ";} cout<<"]"<<endl;
    cout<<"d [ ";
    for(int i=0; i<zadanie.size(); i++){  cout<<zadanie[ tmp[i] ].d<<", ";} cout<<"]"<<endl;
}

int F_min(vector<problem> zd){

    int C=0;
    int F1=0;
    int F2=0;
    int F=0;
    int temp[zd.size()];
    int f_perm[zd.size()];

    vector<int> tymczasowa;

    for(int i=0; i<zd.size(); i++)
    {
        temp[i] = i;
    }

//pierwsze przypisanie
    for(int i=0; i<zd.size(); i++){
        C = C + zd[ temp[i] ].p;

        if(C-zd[ temp[i] ].d > 0)
        {
            F1 = F1 + (C-zd[ temp[i] ].d)*zd[ temp[i] ].w;
        }
    }
    F=F1;
    for(int i=0; i<zd.size(); i++)
        {
            f_perm[i] = temp[i];
        }
//=========================

    do{

    show_data(zd, temp);
    cout<<F<<endl;

    
    F1=0;
    C=0;
    for(int i=0; i<zd.size(); i++){
        C = C + zd[ temp[i] ].p;

        if(C-zd[ temp[i] ].d > 0)
        {
            F1 = F1 + (C-zd[ temp[i] ].d)*zd[ temp[i] ].w;
        }
    }
    
    cout<<"=======F aktualna:   "<<F1<<endl;
    if(F1 < F2)
    {
        F = F1;
        for(int i=0; i<zd.size(); i++)
        {
            f_perm[i] = temp[i];
        }

    }
    F2 = F;

    }while ( next_permutation(temp, temp + zd.size()) );

return F;
}



//==========================================================    MAIN    ==========================================================================
int main(){

    long seed, rozmiar;  

    vector<problem> zadanie;
    

    cout<<"Podaj seed: ";
    cin>>seed;
    cout<<endl;
    cout<<"Podaj rozmiar: ";
    cin>>rozmiar;
    cout<<endl;

    problem dane[rozmiar];
    RandomNumberGenerator liczba(seed);
    priority_queue < problem, vector < problem >, sort_deadline > zadania;         //kolejka priorytetowa dla czasu przygotowania

int suma=0, A=0;

    //losowanie czasow
    for(int i=0; i<rozmiar ; i++){

        dane[i].j = i;
        dane[i].p = liczba.nextInt(1,29);
        
        //A = A + dane[i].p;

    }
    A=29;

    for(int i=0; i<rozmiar; i++)
    {
        dane[i].w = liczba.nextInt(1,9);  
    }
    for(int i=0; i<rozmiar; i++)
    {
        dane[i].d = liczba.nextInt(1,A);    
    }

    for(int i=0; i<rozmiar ; i++)
    {
        zadanie.push_back(dane[i]);
    }

    for(int i=0; i<rozmiar; i++)
    {
        zadania.push(zadanie[i]);
    }

// =========== wyswietlanie danych ================= //
    cout<<"j [";
    for(int i=0; i<rozmiar ; i++){ cout<<zadanie[i].j<<", ";} cout<<"]"<<endl;
    cout<<"p [";
    for(int i=0; i<rozmiar ; i++){ cout<<zadanie[i].p<<", ";} cout<<"]"<<endl;
    cout<<"w [ ";
    for(int i=0; i<rozmiar; i++){  cout<<zadanie[i].w<<", ";} cout<<"]"<<endl;
    cout<<"d [ ";
    for(int i=0; i<rozmiar; i++){  cout<<zadanie[i].d<<", ";} cout<<"]"<<endl;
cout<<"====================================="<<endl;

// algorytm bruteforce

int f=0;

/*
for(int i=0; i<rozmiar; i++)
{
    dane[i] = zadania.top();
    zadania.pop();
    zadanie.pop_back();
}

for(int i=0; i<rozmiar ; i++)
{
    zadanie.push_back(dane[i]);
}
*/

f = F_min(zadanie);


cout<<"\n\nPosortowane brute force:\n";
    cout<<"j [";
    for(int i=0; i<rozmiar ; i++){ cout<<dane[i].j<<", ";} cout<<"]"<<endl;
    cout<<"p [";
    for(int i=0; i<rozmiar ; i++){ cout<<dane[i].p<<", ";} cout<<"]"<<endl;
    cout<<"w [ ";
    for(int i=0; i<rozmiar; i++){  cout<<dane[i].w<<", ";} cout<<"]"<<endl;
    cout<<"d [ ";
    for(int i=0; i<rozmiar; i++){  cout<<dane[i].d<<", ";} cout<<"]"<<endl;

cout<<"\n\nF="<<f<<endl;







    return 0;
}