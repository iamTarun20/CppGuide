#include <iostream>

using namespace std;

int main() {
    cout << "--- Dynamic Memory Allocation ---" << "\n\n";

    // 1. ALLOCATING A SINGLE VARIABLE
    // Allocates memory for an int on the Heap and initializes it to 100
    int* singlePtr = new int(100);

    cout << "Value of dynamically allocated int: " << *singlePtr << endl;

    // Always free the memory!
    delete singlePtr;

    // Good Habit: Avoid Dangling Pointers
    singlePtr = nullptr;

    // 2. ALLOCATING AN ARRAY DYNAMICALLY (AT RUNTIME)
    int size;
    cout << "\nEnter the size of the array: ";
    // Simulating user input - if this was a real program, we'd take input from cin
    size = 5;
    cout << size << endl;

    // We can't do int arr[size] on the Stack safely in standard C++.
    // We MUST use the Heap for dynamic sizes.
    int* dynamicArr = new int[size];

    // Populate the array
    for (int i = 0; i < size; i++) {
        dynamicArr[i] = (i + 1) * 10;
    }

    // Print the array
    cout << "Dynamic Array contents: ";
    for (int i = 0; i < size; i++) {
        cout << dynamicArr[i] << " ";
    }
    cout << endl;

    // 3. FREEING THE ARRAY MEMORY
    // Notice the [] brackets! Essential for deleting arrays properly.
    delete[] dynamicArr;

    // Safe practice
    dynamicArr = nullptr;

    cout << "\nMemory successfully freed. No memory leaks here!" << endl;

    return 0;
}