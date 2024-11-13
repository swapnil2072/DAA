#include<iostream>
#include<chrono>
#include<vector>
#include<algorithm>

using namespace std;
using namespace std::chrono;

struct Item{
    double value;
    double weight;
};

class Greedy {

public: 
        static bool comp(const Item &a, const Item &b){
            double result1 = a.value/a.weight;
            double result2 = b.value/b.weight;
            return result1 > result2;
        }

        double fractionalKnapsack(double maxWt, vector<Item>& v){
            sort(v.begin(),v.end(),comp);
            double currWeight = 0;
            double finalValue = 0;

            for(auto& item:v){
                if(currWeight + item.weight < maxWt){
                    currWeight += item.weight;
                    finalValue += item.value;
                }
                else{
                    double remain = maxWt - currWeight;
                    finalValue += remain * (item.value/item.weight); 
                    break;
                }
            }
            return finalValue;
        }


};


int main(){

    int numberOfItems;
    double maxWeight;
    cout<<"Enter the number of Items"<<endl;
    cin>>numberOfItems;
    cout<<"Enter the max weight"<<endl;
    cin>>maxWeight;
    vector<Item> v(numberOfItems);
    for(int i = 0; i < numberOfItems; i++){
        cout<<"Enter the Item"<<i+1<<" Value:"<<endl;
        cin>>v[i].value;
        cout<<"Enter the Item"<<i+1<<" Weight:"<<endl;
        cin>>v[i].weight;
    }
    Greedy obj;
    auto startTime = high_resolution_clock::now();
    double ans = obj.fractionalKnapsack(maxWeight,v);
    auto endTime = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(endTime - startTime);

    cout<<"The maximum value is "<<ans<<endl;
    cout<<"Elapsed Time: "<<duration.count()<<" microseconds"<<endl;

    return 0;
}
