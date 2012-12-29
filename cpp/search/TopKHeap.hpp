#pragma once
#include <typeinfo> 
#include <assert.h> 
#include <boost/bind.hpp>
#include <string>
#include <sys/mman.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <iostream>
#include <algorithm>
#include <vector>
#include "Def.hpp"

using namespace std;

template<typename Node,typename Compare>
class TopKHeap 
{
    Node *node_array;
    const unsigned capacity;
    unsigned count;
    Compare comp;
public:
    TopKHeap(int n)
    :capacity(n),
    count(0)
    {
        node_array = new Node[n];
    }
    ~TopKHeap(){
        delete []node_array;
    }
    
    void push(const Node &node){
        if(count == capacity){
            if(comp(node_array[0],node)){
                return;
            }else{
                pop();
            }
        }
        node_array[count++] = node;
        push_heap(node_array, node_array + count,comp);
    }
    
    Node pop(){
        assert(count > 0);
        Node node = node_array[0];
        pop_heap(node_array, node_array+count,comp);
        --count;
        return node; 
    }
    
    unsigned size(){
        return count;
    }
    Node & operator[](unsigned i){
        return node_array[i];
    }
};

