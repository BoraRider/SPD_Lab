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
        int index;
        int p1;
        int p2;
        int flag=0;

};

int znajdz_min(vector<problem> tab)
{
    int min=-1, poz=0, j=0;


    while(min<0){
        if(tab[j].flag<1){
            min=tab[j].p1;
            poz=j;
        }
        j++;
    }

    for(int i=0; i<tab.size(); i++)
    {
        if(tab[i].flag<1){
            if(tab[i].p1<tab[i].p2)
            {
                if(tab[i].p1<min)
                {
                min=tab[i].p1;
                poz=i;
                }
            }
            else
            {
                if(tab[i].p2<min)
                {
                min=tab[i].p2;
                poz=i;
                }
            }
        }

    }

    return poz;

}

//==========================================================    MAIN    ==========================================================================
int main(){

    long seed, rozmiar;  

    vector<problem> dane;

    cout<<"Podaj seed: ";
    cin>>seed;
    cout<<endl;
    cout<<"Podaj rozmiar: ";
    cin>>rozmiar;
    cout<<endl;

    //deklaracja L i K
    int k=rozmiar-1, l=0;
    problem zadanie[rozmiar];

    RandomNumberGenerator liczba(seed);

int suma=0;
    //losowanie czasow
    for(int i=0; i<rozmiar ; i++){

    zadanie[i].index=i+1;
    zadanie[i].p1=liczba.nextInt(1,PRZEDZIAL);
    zadanie[i].p2=liczba.nextInt(1,PRZEDZIAL);
    }

for(int i=0; i<rozmiar ; i++){
    dane.push_back(zadanie[i]);
}

// =========== wyswietlanie danych ================= //

    cout<<"i [";
    for(int i=0; i<rozmiar ; i++){cout<<dane[i].index<<"\t";} cout<<"]"<<endl;
    for(int i=0; i<100; i++){cout<<"-";} 
    cout<<"\n[ ";
    for(int i=0; i<rozmiar; i++){  cout<<"["<<dane[i].p1<<", "<<dane[i].p2<<"] ";  }
    cout<<" ]\n\n";


    //problem dane_backup[rozmiar], w[rozmiar]; //zmienne pomocnicze
    //vector<problem> dane_2;
//backup dla tabeli
/*
    for(int i=0; i<rozmiar; i++){
    dane_backup[i].index = dane[i].index;
    dane_backup[i].p1 = dane[i].p1;
    dane_backup[i].p2 = dane[i].p2;
    dane_backup[i].flag = dane[i].flag;
    }
*/

    int pi[rozmiar]; //tablica posortowanych zadań
	//int t = 0;      //chwila czasowa
	int C[2][rozmiar];   //maksymalny z terminow dostarczenia zadan
    int min_index=0;
    int cMax=0;
    int licznik=0;

while(licznik<rozmiar){

        min_index=znajdz_min(dane);
        dane[min_index].flag++;

        if(dane[min_index].p1<dane[min_index].p2)
        {
            pi[l] = min_index+1;
            l++;
        }
        else
        {
            pi[k] = min_index+1;
            k--;
        }  
licznik++;
}

    cout<<"pi:  [";
    for(int i=0; i<rozmiar ; i++){cout<<pi[i]<<"  ";} cout<<"]"<<endl;

    C[0][0] = dane[pi[0]-1].p1;
    C[1][0] = dane[pi[0]-1].p1 + dane[pi[0]-1].p2; 

    for(int i=1; i<rozmiar; i++){

        C[0][i] = C[0][i-1] + dane[pi[i]-1].p1;

        if(     C[0][i] > C[1][i-1]  ){
           C[1][i] = C[0][i] + dane[pi[i]-1].p2;
        }
        else{
            C[1][i] = C[1][i-1] + dane[pi[i]-1].p2;
        }
        

    }

cout<<"C:  [";
    for(int i=0; i<rozmiar; i++){
        cout<<"["<<C[0][i]<<", "<<C[1][i]<<"] ";
    }
cout<<"]"<<endl;
cMax = C[1][rozmiar-1];

cout<<"Cmax: "<<cMax<<endl;




    return 0;
}