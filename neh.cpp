//Maciej Osak i Dominik Brzezina
//Algorytm NEH

#include <iostream>
#include "RandomNumberGenerator.h"
#include <algorithm>
#include <vector>
#include <queue>

#define PRZEDZIAL 29

using namespace std;

/* ========================== Z A Ł O Ż E N I A ================================================================
*   Mamy n zadań
*   Zbiór J(1, 2, 3, ... , n)
*   Wykonujemy je na m maszynach
*   Zbiór M(1, 2, 3, ... , m)
*   Każde zadanie składa się z m operacji
*   Zbiór O(1, 2, 3, ... , m)
*   Każda operacja wykonuje się kolejno na 1 maszynie (operacja 1 na maszynie1, op2 na masz2, op3 na masz3 itp)
*   Każda operacja ma swój czas wykonywania
*   Zbiór P(czas1, czas2, ... , czas_m)
*/

int momentS[100][100];
int momentC[100][100];

class problem
{
    public:
        int index;
        vector<int> p;
        vector<int> o;
        int flag;
        int sum;
};


int momenty(vector<problem> zd, int operacje)
{
    
    int cmax;
    int i=0; 

    //vector<int> tmp(zd.size());
    //for(i;i<zd.size();i++){tmp.push_back(0);}
    //vector<vector<int>> momentS(operacje, tmp);
    //vector<vector<int>> momentC(operacje, tmp);

    //for(i=0;i<operacje;i++){momentS.push_back(tmp);}
    //for(i=0;i<operacje;i++){momentC.push_back(tmp);}


 

    for(i=0; i<zd.size(); i++)
    {
        if(i==0)
        {
            //cout <<"\nOK\n";
            momentC[i][0] = zd[i].p[0];
            momentS[i][0]=0;
            for(int j=1; j<operacje; j++)
            {
               momentS[i][j]=momentS[i][j-1] + zd[i].p[j-1];
               momentC[i][j]=momentC[i][j-1] + zd[i].p[j];
            }
        }
        if(i>0)
        {
            
            momentS[i][0] = momentC[i-1][0];
            momentC[i][0] = momentS[i][0] + zd[i].p[0];
            for(int j=1; j<operacje; j++)
            {
                
                momentS[i][j] = max(momentC[i-1][j] , momentC[i][j-1]);
                momentC[i][j] = zd[i].p[j] + momentS[i][j];

            }    
        }
    }
    cmax = momentC[zd.size()-1][operacje-1];

/*
    cout<<"Macierz C:\n\n";
    for(int w=0; w<operacje; w++)
    {
        for(int k=0; k<zd.size(); k++)
        {
            cout<<" "<<momentC[k][w];
        }
        cout<<endl;
    }
    cout<<"\nMacierz S:\n\n";
    for(int w=0; w<operacje; w++)
    {
        for(int k=0; k<zd.size(); k++)
        {
            cout<<" "<<momentS[k][w];
        }
        cout<<endl;
    }
*/
    return cmax;

}
//z  1  2  3
//m1 1 50  2
//m2 4 6  5

// czy maszyna 2 się zwolniła w czasie robienia poprzedniego zadania na 2 maszynie

//1 505050505050 ??????
// 4444 --------666666 55555


 //0 1 51
 //0 4 10 

struct sort_sum
{
    bool operator ()(const problem p1, const problem p2)
    {
        return p1.sum < p2.sum;
    }
};

//==========================================================    MAIN    ==========================================================================
int main(){

    long seed, rozmiar, operacje;  
    int oTemp=0;
    vector<problem> dane;

    cout<<"Podaj seed: ";
    cin>>seed;
    cout<<endl;
    cout<<"Podaj rozmiar: ";
    cin>>rozmiar>>operacje;
    cout<<endl;

    problem zadanie[rozmiar];

    RandomNumberGenerator liczba(seed);

int suma=0;
    //losowanie czasow
    for(int i=0; i<rozmiar ; i++){

        zadanie[i].index=i;

        for(int j=0; j<operacje; j++){
            oTemp = j;
            zadanie[i].o.push_back(oTemp);

            oTemp = liczba.nextInt(1,PRZEDZIAL);
            zadanie[i].p.push_back(oTemp);
        }
        zadanie[i].flag = 0;
    }

for(int i=0; i<rozmiar ; i++){
    dane.push_back(zadanie[i]);
}

// =========== wyswietlanie danych ================= //

    cout<<"i [";
    for(int i=0; i<rozmiar ; i++){cout<<dane[i].index<<"\t";} cout<<"]"<<endl;
    for(int i=0; i<100; i++){cout<<"-";} 
    cout<<"\nZadania\n";
    for(int i=0; i<rozmiar; i++)
    {
        cout<<"[ ";
        for(int j=0; j<operacje; j++){
         cout<<dane[i].o[j]<<" ";    
        }
        cout<<" ], ";
    }
    cout<<"\nCzasy\n";
    for(int i=0; i<rozmiar; i++)
    {
        cout<<"[ ";
        for(int j=0; j<operacje; j++){
         cout<<dane[i].p[j]<<" ";    
        }
        cout<<" ], ";
    }
 // =========== wyswietlanie danych ================= //


// sumowanie czasów
    int sum_czas[rozmiar];
    cout<<"\nsumy czasow: "<<endl;

    for(int i=0; i<rozmiar; i++)
    {
        dane[i].sum=0;
        for(int j=0; j<operacje; j++)
        {
            dane[i].sum += dane[i].p[j];
        }
        cout<<"czas: "<<dane[i].sum<<endl;
    }



vector<problem> wrzucany;
priority_queue < problem, vector < problem >, sort_sum > problematyczna_kolejka; 
for(int i=0; i<rozmiar; i++){
        problematyczna_kolejka.push(dane[i]);
    }

 
for(int i=0; i<rozmiar; i++)
{
    wrzucany.push_back( problematyczna_kolejka.top());
    cout<<"Wartosc: "<<wrzucany[i].index<<endl;
    problematyczna_kolejka.pop();
}

vector<problem> sprawdzany;
int poz=0, cmax=0, cmax0=0, poz0=0, nastepny_size=0;

cmax0=99999;
cmax0 = cmax;

for(int i=0; i<rozmiar; i++)
{
    nastepny_size = sprawdzany.size()+1;
    for(poz=0; poz<nastepny_size ;poz++)
    {
        sprawdzany.insert(sprawdzany.begin()+ poz, wrzucany[i]);
        cmax = momenty(sprawdzany, operacje);

        //Wyswietlanie=================
        cout<<"C: "<<cmax<<" \t[";
        for(int idx=0; idx<nastepny_size; idx++)
        {
            cout<<sprawdzany[idx].index;
            if(idx<nastepny_size-1){
                cout<<", ";
            }
        }
        cout<<"]"<<endl;
        //=================Wyswietlanie

        sprawdzany.erase(sprawdzany.begin()+ poz);
        if(cmax<cmax0)
        {
            cmax0 = cmax;
            poz0 = poz;
        }
    }
    sprawdzany.insert(sprawdzany.begin()+ poz0, wrzucany[i]);
    cout<<"Cmax: [ "<<cmax0<<" ]"<<endl<<endl;
    cmax0 = 99999;

}
//=================== wyswietlanie koncowe ===================
    cout<<"PI: [";
    for(int idx=0; idx<nastepny_size; idx++)
    {
    cout<<sprawdzany[idx].index;
    if(idx<nastepny_size-1){
            cout<<", ";
        }
    }
    cout<<"]"<<endl;

momenty(sprawdzany, operacje);

    cout<<"C: [";
    for(int idx=0; idx<nastepny_size; idx++)
    {
        cout<<"[ ";
        for(int opr=0; opr<operacje; opr++)
        {
            cout<<momentC[idx][opr];;
            if(opr<operacje-1){
            cout<<", ";
            }
        }
        cout<<" ]";
    if(idx<nastepny_size-1){
            cout<<", ";
        }
    }
    cout<<"]\n\n";


    return 0;
}