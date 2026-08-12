#include <iostream>
using namespace std;

void UseStack() {
    int i = 35;
    cout<<i<<endl;
}
void UseHeap() {
    int* ptr = new int;
    *ptr = 25;
    cout<<*ptr<<endl;

    delete ptr;

    ptr = nullptr;
}

int main() {
    cout<< "MEMORY -------------- MANAGEMENT" <<endl;
    UseStack();
    UseHeap();

}