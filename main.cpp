#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
#include <time.h>
#include <chrono>
#include <random>

using namespace std;
using namespace std::chrono;

vector<int> v;
void generare(int Nr,int ValMax)
{
    /*for (int i=1;i<5000;i++)
    {
        long long x;
        x=rand()*rand();
        v.push_back(x);
    }*/
    default_random_engine eng {time(0)};
    uniform_int_distribution<> dist(0, ValMax);

    for(int i = 0; i < Nr; i++)
        v.push_back(dist(eng));
}
void printare(vector<int> v)
{
    for (int i=0;i<v.size();i++)
        cout<<v[i]<<" ";
    cout<<endl;

}
void Bubblesort(vector<int> &v)
{
    for(int i=0;i<v.size();i++)
        for(int j=0;j<v.size()-1;j++)
            {
                if(v[j]>v[j+1])
                    swap(v[j],v[j+1]);
            }
}
void Countsort(vector<int> &v)
{
    try{
        long long maxim;
        maxim=v[0];
        for (int i=1;i<v.size();i++)
        {
            if(v[i]>maxim)
                maxim=v[i];
        }
        vector<int> frec(maxim+1);
        vector<int> rez;
        for(int i=0;i<v.size();i++)
            frec[v[i]]++;
        for(int i=0;i<frec.size();i++)
            {
                for(int j=0;j<frec[i];j++)
                    rez.push_back(i);
            }
        v.swap(rez);
    }
    catch (const bad_alloc&)
    {
        cout<<"nu am loc\n";
    }

}
void RadixSort(vector<int> &v, int baza)
{   /*
    vector<vector<int>> r ;
    vector<int> rez;
    for (int i=0;i<baza;i++)
    {
        for(int j=0;j<v.size();j++)
            if(v[j]%10==i)
                r[i].push_back(v[j])
    }
    for (int i=0;i<baza;i++)
        for(int j=0;j<r[i].size();j++)
            rez.push_back(r[i][j]);
    RadixSort(rez)
    */
    vector<int> bucket(v.size(),0);
    int mmax=0, pozitie=1;
    for(int i=0;i<v.size();i++)
    {
        if(v[i]>mmax)
            mmax = v[i];
    }
    while(mmax/pozitie>0)
    {
        int digitCount[baza] = {0};

        for(int i=0;i<v.size();i++)
            digitCount[v[i]/pozitie%10]++;
        for (int i=1;i<baza;i++)
            digitCount[i]+=digitCount[i-1];
        for(int i=v.size()-1;i>=0;i--)
            bucket[--digitCount[v[i]/pozitie%10]]=v[i];
        for(int i=0;i<v.size();i++)
            v[i]=bucket[i];
        pozitie*=10;
    }

}


vector<int> Interclasare(vector<int> S,vector<int> D)
{
    vector<int> rez;
    int i=0;
    int j=0;
    while(i<S.size() && j<D.size())
    {
        int k=0;
        if(S[i]==D[j] && k==0)
        {
            rez.push_back(S[i]);
            rez.push_back(D[j]);
            i++;
            j++;
            k=1;
        }
        if(S[i]<D[j] && k==0)
        {
            rez.push_back(S[i]);
            i++;
            k=1;
        }
        if(S[i]>D[j] && k==0)
        {
            rez.push_back(D[j]);
            j++;
            k=1;
        }
    }
    while(i<S.size())
    {
        rez.push_back(S[i]);
        i++;
    }
    while(j<D.size())
    {
        rez.push_back(D[j]);
        j++;
    }
    return rez;
}
 vector<int> MergeSort(vector<int> v)
{
    if (v.size()>1)
    {
        vector<int> S;
        vector<int> D;
        vector<int> R;
        int mij;
        mij=(v.size()+1)/2;
        for(int i=0;i<mij;i++)
            S.push_back(v[i]);
        for(int i=mij;i<v.size();i++)
            D.push_back(v[i]);
        S=MergeSort(S);
        D=MergeSort(D);
        R=Interclasare(S,D);

        return R;
    }
    else
        return v;

}
void QuickSort(vector<int> &v, int i,int j)
{
    int stanga,dreapta,pivot;
    if(i>=j)
        return;
    stanga=i;
    dreapta=j;

    pivot=v[(i+j)/2];

    while(stanga <= dreapta)
    {
        while(v[stanga]<pivot)
            stanga++;
        while(v[dreapta]>pivot)
            dreapta--;
        if(stanga<=dreapta)
        {
            swap(v[stanga],v[dreapta]);
            stanga++;
            dreapta--;
        }
    }
    QuickSort(v,i,dreapta);
    QuickSort(v,stanga,j);

}

void testare(vector<int> v)
{
    int k=1;
    for (int i=0;i<v.size()-1;i++)
    {
        for (int j=i+1;j<v.size();j++)
            if (v[i]>v[j])
                {
                    cout<<"nu e bine";
                    k=0;
                    break;
                }
        if(k==0)
            break;
    }

    if (v.size()==0)
        cout<<"vid";
    else
        if(k==1)
            cout<<"e bine";

}

int main()
{
    int Nr,ValMax;
    cout<<"cate numere?\n";cin>>Nr;
    cout<<"care sa fie valmax?\n";cin>>ValMax;
    generare(Nr,ValMax);
    printare(v);
    auto start = high_resolution_clock::now();
    Bubblesort(v);
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);
    cout <<"timpul sortarii este :"<< duration.count() << " microsecunde"<<endl;
    printare(v);
    return 0;
}
