#include "priorityqueue.h"
#include <iostream>
using namespace std;


int main() {
    PriorityQueueL qu;
    try {
        qu.top();
    }
    catch (runtime_error e) {
        cout << "I tried to get top from empty Queue but I couldn't" << endl;
    }
    qu.push(2);
    cout << qu.top() << endl;
    qu.push(3);
    cout << qu.top() << endl;
    qu.push(1);
    cout << qu.top() << endl;

    int qweqweqwe;
    cin >> qweqweqwe;
}