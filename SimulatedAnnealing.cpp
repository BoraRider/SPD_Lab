//Maciej Osak i Dominik Brzezina
//Algorytm NEH

#include <iostream>
#include "RandomNumberGenerator.h"
#include <algorithm>
#include <vector>
#include <queue>
#include <math.h>

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
int poz=0, cmax=0, cmax0=0, poz0=0, nastepny_size=0;

class problem
{
    public:
        int index;
        vector<int> p;
        vector<int> o;
        int flag;
        int sum;
};

class wynik_
{
    public:
        vector<int> pi;
        int cmax;
};

vector<problem> sprawdzany;

int momenty(vector<problem> zd, int operacje)
{
    int cmax;
    int i=0; 
 
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

    return cmax;

}

void neh(int operacje, int rozmiar, vector<problem> wrzucany){

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
            /*
            cout<<"C: "<<cmax<<" \t[";
            for(int idx=0; idx<nastepny_size; idx++)
            {
                cout<<sprawdzany[idx].index;
                if(idx<nastepny_size-1){
                    cout<<", ";
                }
            }
            cout<<"]"<<endl;
            */
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


}

wynik_ wyzarzanie(int T0, int T_end, int operacje, int rozmiar, int L, problem* zadanie){

    int cmax, T, pi[rozmiar], pi_new[rozmiar], pi_best[rozmiar], k=1, wylosowana, delta_cmax, cmax1, cmax2;
    T=T0;
    float r;

    wynik_ wynik;
    RandomNumberGenerator liczba(2564);
    vector<problem> dane1, dane2;

    wynik.cmax = 0;
    for(int i=0; i<rozmiar; i++){
     pi[i]=i;
     pi_new[i]=i;
     pi_best[i]=i;
     wynik.pi.push_back(i);
    }
    for(int i=0; i<rozmiar ; i++){
        dane1.push_back(zadanie[pi[i]]);
    }

    int i=0, j=0;
    //cmax = momenty(dane, operacje);

    while(T > T_end){

        //cout<<endl<<"================== Petla T: "<<T<<" =================="<<endl<<endl;
        for(k=1; k<L; k++){
            i = liczba.nextInt(0,rozmiar-1);
            j = liczba.nextInt(0,rozmiar-1);

            swap(pi_new[i], pi_new[j]);
            
            dane2.clear();
            dane1.clear();
            for(int l=0; l<rozmiar ; l++)
            {
                dane2.push_back(zadanie[pi_new[l]]);
                dane1.push_back(zadanie[pi[l]]);
            }
            /*
            cout<<"PI: ";
            for(int h=0; h<rozmiar; h++){
                cout<<pi[h]<<" ";
            }
            cout<<endl<<"PI_NEW: ";
            for(int h=0; h<rozmiar; h++){
                cout<<pi_new[h]<<" ";
            }
            cout<<endl;*/
            cmax2 = momenty(dane2, operacje);
            cmax1 = momenty(dane1, operacje);

            delta_cmax = cmax1 - cmax2;
            //cout<<"Przejscie k = "<<k<<endl;
            //cout<<"Cmax pi_new: "<<cmax2<<"\tCmax pi: "<<cmax1<<endl;
            if( cmax2 > cmax1 ){
                
                wylosowana = liczba.nextInt(0,999999);
                r = (float)wylosowana/1000000;

                //cout<<"\nWartosc r: "<<r<<endl;

                if( r >= exp(delta_cmax/T) )
                {
                    for(int l=0; l<rozmiar; l++){
                        pi_new[l] = pi[l];
                    }
                }// end if
            }// end if

            for(int l=0; l<rozmiar; l++){
                pi[l] = pi_new[l];
            }

            dane2.clear();
            dane1.clear();
            for(int l=0; l<rozmiar ; l++){
                dane2.push_back(zadanie[pi[l]]);
                dane1.push_back(zadanie[wynik.pi[l]]);
            }
            cmax2 = momenty(dane2, operacje);
            cmax1 = momenty(dane1, operacje);
            //cout<<"\nC_MAX po petli t:"<<endl;
            //cout<<"Cmax pi: "<<cmax2<<"\tCmax wynik: "<<cmax1<<endl;
            if(cmax2 < cmax1){

                for(int l=0; l<rozmiar; l++){
                wynik.pi[l] = pi[l];
                }
                wynik.cmax = cmax1;

            }// end if

        }// end for

        T = T - 1;
    }// end while
/*
    for(int l=0; l<rozmiar; l++){
    wynik.pi[l] = pi_best[l];

    }
*/
    cout<<endl<<endl<<"PI_BEST: ";
    for(int h=0; h<rozmiar; h++){
        cout<<wynik.pi[h]<<" ";
    }
    cout<<endl;
    //wynik.cmax = cmax;

    return wynik;
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


// sumowanie czasów wszystkich operacji w jednym zadaniu
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
wynik_ wynik;

// algorytm NEH
neh(operacje, rozmiar, wrzucany);



//=================== wyswietlanie koncowe ===================
cout<<"Algorytm NEH:"<<endl;
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

// ====================== wyzazanie ===========================
//wyzarzanie(int T0, int T_end, int operacje, int rozmiar, int L, problem* zadanie)

// T0 - temperatura początkowa
// T_end - temperatura końcowa
// L - iteracje wewnetrzne (epoki)

wynik = wyzarzanie(100, 0, operacje, rozmiar, 10, zadanie);

wrzucany.clear();
for(int i=0; i<rozmiar; i++)
{
    wrzucany.push_back( zadanie[ wynik.pi[i] ]);
}

//=================== wyswietlanie koncowe ===================
cout<<"Algorytm Simulated Annealing:"<<endl;
cout<<"Cmax: "<< wynik.cmax <<endl;
    cout<<"PI: [";
    for(int idx=0; idx<rozmiar; idx++)
    {
    cout<<wrzucany[idx].index;
    if(idx<rozmiar-1){
            cout<<", ";
        }
    }
    cout<<"]"<<endl;

momenty(wrzucany, operacje);

    cout<<"C: [";
    for(int idx=0; idx<rozmiar; idx++)
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
    if(idx<rozmiar-1){
            cout<<", ";
        }
    }
    cout<<"]\n\n";

    return 0;
}