#include <iostream>
#include "../TopKHeap.hpp"
using namespace std;

struct Compare
{
    bool operator()(int a,int b){
        return a>b;
    }
};

int main()
{
    TopKHeap<int,Compare> * h = new TopKHeap<int,Compare>(5);
    int a[] = {1,1,1,101,1,3,5,4,9,6,1,11,29,5,109,76,31,39,1,1,1,1,1,1,1,1};
    for(int i=0;i<sizeof(a)/4;i++){
        h->push(a[i]);        
    }
    vector<int> topv;
    while(h->size()){
        int i = h->pop();
        topv.insert(topv.begin(),i);
    }
    for(size_t i=0;i<topv.size();i++){
        cout<<topv[i]<<endl;
    }
}
