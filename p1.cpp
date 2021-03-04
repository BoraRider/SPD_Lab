//Maciej Osak i Dominik Brzezina

#include <iostream>
#include "RandomNumberGenerator.h"
#include <algorithm>

using namespace std;

class wylosowana
{

public:
int wartosc;
int index;
int wykonywanie;

};



int main(){
long seed;
int przedzial;
int tab[10];
int tab2[10];


cout<<"Podaj seed: ";
cin>>seed;
cout<<endl;
cout<<"Podaj przedzial: ";
cin>>przedzial;

wylosowana liczba_wylosowana[10];
RandomNumberGenerator liczba(seed);
RandomNumberGenerator liczba2(seed+100);



//losowanie wartosci
for(int i=0; i<10; i++){

liczba_wylosowana[i].index=i+1;
liczba_wylosowana[i].wartosc=liczba.nextInt(1,przedzial);
liczba_wylosowana[i].wykonywanie=liczba2.nextInt(1,przedzial);

tab[i] = liczba_wylosowana[i].wartosc;
tab2[i] = liczba_wylosowana[i].wykonywanie;
}
cout<<"j [";
for(int i=0; i<10; i++){cout<<liczba_wylosowana[i].index<<"\t";} cout<<"]"<<endl<<"r [";
for(int i=0; i<10; i++){cout<<liczba_wylosowana[i].wartosc<<"\t";} cout<<"]"<<endl<<"p [";
for(int i=0; i<10; i++){cout<<liczba_wylosowana[i].wykonywanie<<"\t";} cout<<"]"<<endl;



sort(tab, tab+10);

int j=0;
//wyswietlanie
cout<<"\n\nSortowanie wedlug czasu przygotowania: \n"<<endl;
for(int i=0; i<10; i++){
    for(j=0; j<10; j++){
        if(tab[i] == liczba_wylosowana[j].wartosc){
          cout<<" index:"<<liczba_wylosowana[j].index<< " / ";   
        }
    }

cout<<"czas: "<<tab[i]<<", ";
cout<<endl;
}
cout<<"\n\n";
    return 0;
}