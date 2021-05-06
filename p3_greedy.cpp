//Maciej Osak i Dominik Brzezina

#include <iostream>
#include "RandomNumberGenerator.h"
#include <algorithm>
#include <vector>
#include <queue>

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


// algorytm zachlanny
for(int i=0; i<rozmiar; i++)
{
    dane[i] = zadania.top();
    zadania.pop();
}

int C=0;
int F=0;
for(int i=0; i<rozmiar; i++){
    C = C + dane[i].p;

    if(C-dane[i].d > 0)
    {
        F = F + (C-dane[i].d)*dane[i].w;
    }
}


cout<<"\n\nPosortowane po d:\n";
    cout<<"j [";
    for(int i=0; i<rozmiar ; i++){ cout<<dane[i].j<<", ";} cout<<"]"<<endl;
    cout<<"p [";
    for(int i=0; i<rozmiar ; i++){ cout<<dane[i].p<<", ";} cout<<"]"<<endl;
    cout<<"w [ ";
    for(int i=0; i<rozmiar; i++){  cout<<dane[i].w<<", ";} cout<<"]"<<endl;
    cout<<"d [ ";
    for(int i=0; i<rozmiar; i++){  cout<<dane[i].d<<", ";} cout<<"]"<<endl;

cout<<"\n\nF="<<F<<endl;







    return 0;
}