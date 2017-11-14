#include "stackl.h"
#include <iostream>
using namespace std;


int main() {

    StackL stack;
    stack.push(3);
    cout << "top element: " << stack.top() << endl;
    cout << "stack is empty: " << (stack.isEmpty() ? "true" : "false") << endl;
    stack.pop();
    cout << "stack is empty: " << (stack.isEmpty() ? "true" : "false") << endl;
    try {
        stack.top();
    }
    catch (runtime_error e) {
        cout << "I tried to get top from empty stack but I couldn't" << endl;
    }
    stack.push(1);
    stack.push(2);
    cout << "top element: " << stack.top() << endl;
    stack.pop();
    cout << "top element: " << stack.top() << endl;
    stack.push(3);
    StackL stack2(stack);
    cout << "top element of 2nd stack: " << stack2.top() << endl;
    stack2.pop();
    cout << "top element of 2nd stack: " << stack2.top() << endl;
    stack2.pop();
    try {
        stack2.top();
    }
    catch (runtime_error e) {
        cout << "I tried to get top from empty stack but I couldn't" << endl;
    }
    StackL stack3;
    stack3 = stack;
    cout << "top element of 3rd stack: " << stack3.top() << endl;
    stack3.pop();
    cout << "top element of 3rd stack: " << stack3.top() << endl;
    stack3.pop();
    try {
        stack3.top();
    }
    catch (runtime_error e) {
        cout << "I tried to get top from empty stack but I couldn't" << endl;
    }


    return 0;
}