#include "priorityqueuel.h"
#include <iostream>
using namespace std;

void out_all(const PriorityQueueL& qu) {
    PriorityQueueL copy = qu;
    cout << "full queue now: ";
    while (!copy.isEmpty()) {
        cout << copy.top() << " ";
        copy.pop();
    }
    cout << endl;
}

void pushandout(PriorityQueueL& qu, const int& n) {
    qu.push(n);
    out_all(qu);
}

void popandout(PriorityQueueL& qu) {
    qu.pop();
    out_all(qu);
}

int main() {
    PriorityQueueL qu;
    try {
        qu.top();
    }
    catch (runtime_error e) {
        cout << "I tried to get top from empty Queue but I couldn't" << endl;
    }

    pushandout(qu, 2);
    cout << "top now: " << qu.top() << endl;
    pushandout(qu, 3);
    pushandout(qu, 10);
    cout << "top now: " << qu.top() << endl;
    pushandout(qu, 4);
    pushandout(qu, 1);
    pushandout(qu, 5);
    popandout(qu);
    popandout(qu);
    cout << "--------" << endl;
    PriorityQueueL qu2 = qu;
    PriorityQueueL qu3;
    PriorityQueueL qu4;
    qu4.push(666);
    out_all(qu2);
    qu2 = qu3;
    pushandout(qu2, 999);

    qu2 = qu4;
    out_all(qu2);

    qu2 = qu;
    out_all(qu2);

    qu2 = qu4;
    out_all(qu2);

    cout << "qu2 is empty? : " << (qu2.isEmpty() ? "true" : "false") << endl;
    qu2.clear();
    cout << "qu2 is empty? : " << (qu2.isEmpty() ? "true" : "false") << endl;


    //int qweqweqwe;
    //cin >> qweqweqwe;
}