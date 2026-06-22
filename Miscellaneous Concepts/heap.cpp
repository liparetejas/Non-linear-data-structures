#include<bits/stdc++.h>
using namespace std;

class Heap {
private:
    vector<int> heap;
    

public:
    Heap() {
        heap.clear();
    }

    void insert(int val) {
        heap.push_back(val);
        int i = heap.size() - 1;
        while((i != 0) && (heap[i] > heap[(i - 1) / 2])) {
            swap(heap[i], heap[(i - 1) / 2]);
            i = (i - 1) / 2;
        }
    }

    void heapify(int i) {
        int largest = i;
        int left = 2 * i + 1;
        int right = 2 * i + 2;
        int size = heap.size();
        if((left < size) && (heap[left] > heap[largest])) {
            largest = left;
        }
        if((right < size) && (heap[right] > heap[largest])) {
            largest = right;
        }
        if(largest != i) {
            swap(heap[i], heap[largest]);
            heapify(largest);
        }
    }

    int pop() {
        if(heap.empty()) {
            return -1;
        }
        if(heap.size() == 1) {
            int root = heap[0];
            heap.pop_back();
            return root;
        }
        int root = heap[0];
        heap[0] = heap.back();
        heap.pop_back();
        heapify(0);
        return root;
    }

    void printHeap() {
        for(int i = 0; i < heap.size(); i++) {
            cout << heap[i] << " ";
        }
        cout << endl;
    }
    
    
};

int main() {
    Heap* heap = new Heap();
    heap->insert(10);
    heap->insert(20);
    heap->insert(5);
    heap->insert(15);
    heap->insert(30);
    heap->insert(45);
    heap->insert(50);
    heap->insert(35);
    heap->insert(25);
    heap->insert(40);
    heap->printHeap();
    cout << "Popped: " << heap->pop() << endl;
    cout << "Popped: " << heap->pop() << endl;
    cout << "Popped: " << heap->pop() << endl;
    cout << "Popped: " << heap->pop() << endl;
    cout << "Popped: " << heap->pop() << endl;
    cout << "Popped: " << heap->pop() << endl;
    cout << "Popped: " << heap->pop() << endl;
    cout << "Popped: " << heap->pop() << endl;
    cout << "Popped: " << heap->pop() << endl;
    cout << "Popped: " << heap->pop() << endl;
    heap->printHeap();
    delete heap;
    return 0;
}

/*
Output:
50 40 45 25 35 5 30 10 20 15 
Popped: 50
Popped: 45
Popped: 40
Popped: 35
Popped: 30
Popped: 25
Popped: 20
Popped: 15
Popped: 10
Popped: 5
*/