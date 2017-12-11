#include <iostream>;
#include "stacka.h"
using namespace std;

void out_top(StackA& st) {
    cout << "top element is " << st.top() << endl;
}

int main() {
    StackA st1;
    st1.resize(2);

    st1.push(3);
    out_top(st1);

    cout << "current logic size: " << st1.size() << endl;
    cout << "current phys size: " << st1.capacity() << endl;
    cout << "stack is empty: " << st1.isEmpty() << endl;

    st1.push(4);
    out_top(st1);

    st1.push(5);
    out_top(st1);

    st1.pop();
    out_top(st1);

    st1.pop();
    st1.pop();

    try { 
        out_top(st1); 
    }
    catch (out_of_range e) {
        cout << "couldn't get top from empty stack" << endl;
    }
    cout << "stack is empty: " << st1.isEmpty() << endl;

    st1.push(3);

    cout << endl;
    cout << "----- copying -----" << endl;
    StackA st2;
    st2 = st1;
    cout << "st2 --------" << endl;
    out_top(st2);
    cout << "current logic size: " << st2.size() << endl;
    cout << "current phys size: " << st2.capacity() << endl;
    cout << "st1 --------" << endl;
    out_top(st1);
    cout << "current logic size: " << st1.size() << endl;
    cout << "current phys size: " << st1.capacity() << endl;

    cout << endl;
    cout << "----- copying operator -----" << endl;
    StackA st3(st1);
    cout << "st3 --------" << endl;
    out_top(st3);
    cout << "current logic size: " << st3.size() << endl;
    cout << "current phys size: " << st3.capacity() << endl;
    cout << "st1 --------" << endl;
    out_top(st1);
    cout << "current logic size: " << st1.size() << endl;
    cout << "current phys size: " << st1.capacity() << endl;


    int qweqweqwe;
    cin >> qweqweqwe;
}