#include<iostream>
#include<chrono>

using namespace std;
using namespace std:: chrono;


int recursiveFibo(int num){
    if(num <= 1){
        return num;
    }
    return recursiveFibo(num-2) + recursiveFibo(num-1);

}


void nonRecursiveFibo(int num){
    int num1 = 0; 
    int num2 = 1;
    int num3;
    if(num >= 1) cout<< num1 << " ";
    if(num >= 2) cout<< num2 << " ";
    for(int i = 2; i < num; i++){
        num3 = num1 + num2;
        cout<<num3<<" ";
        num1 = num2;
        num2 = num3;
    }
}



int main() {

    int num;
    cout<<"Enter the number: ";
    cin>> num;

    cout<<"Non recursive fibonacci series:";
    auto start = high_resolution_clock::now();
    nonRecursiveFibo(num);
    auto end = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(end-start);
    cout<<"\nElapsed Time (non-recursive): "<<duration.count()<<" microseconds"<<endl;

    cout<<"Recursive fibonacci series:";
    auto rstart = high_resolution_clock::now();
    for(int i = 0 ; i < num; i++)
    {
        cout<<recursiveFibo(i)<<" ";
    }
    auto rend = high_resolution_clock::now();
    auto rduration = duration_cast<microseconds>(rend - rstart);
    cout<<"\nElapsed Time (recursive): "<<rduration.count()<<" microseconds"<<endl;

    return 0;
}
