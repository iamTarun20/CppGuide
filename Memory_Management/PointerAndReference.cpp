#include <iostream>
using namespace std;

// Pointer se swap
void swapPointer(int* p1, int* p2)
{
    int temp = *p1;
    *p1 = *p2;
    *p2 = temp;
}

// Reference se swap
void swapReference(int& a, int& b)
{
    int temp = a;
    a = b;
    b = temp;
}

int main()
{
    int x = 10;

    // ---------------- POINTER ----------------

    int* ptr = &x;

    cout << "x = " << x << endl;
    cout << "Address of x = " << ptr << endl;
    cout << "Value through ptr = " << *ptr << endl;

    // ---------------- REFERENCE ----------------

    int& ref = x;

    ref = 20;

    cout << "x after changing ref = " << x << endl;

    // ---------------- SWAP ----------------

    int a = 10;
    int b = 20;

    cout << "\nBefore swap: " << a << " " << b << endl;

    swapPointer(&a, &b);

    cout << "After pointer swap: " << a << " " << b << endl;

    swapReference(a, b);

    cout << "After reference swap: " << a << " " << b << endl;

    return 0;
}