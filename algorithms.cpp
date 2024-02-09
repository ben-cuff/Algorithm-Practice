#include <iostream>
#include <cstdlib>
#include <ctime>
#include <chrono>

using namespace std;

const int arraySize = 100000;

void linear_Search(int *, int);

int main()
{
    srand(static_cast<unsigned>(time(nullptr)));

    int arr[arraySize];

    for (int i = 0; i < arraySize; ++i)
    {
        arr[i] = rand() % 1000000 + 1; // Generate a random number between 1 and 1000000
    }

    int indexToFind = rand() % arraySize + 1;

    auto start = chrono::high_resolution_clock::now();

    linear_Search(arr, arr[indexToFind]);

    auto end = chrono::high_resolution_clock::now();

    cout << "Linear Search took " << chrono::duration_cast<chrono::nanoseconds>(end - start).count() << " nanoseconds to run" << endl;

    return 0;
}

void linear_Search(int *arr, int valueToFind)
{
    for (int i = 0; i < arraySize; i++)
    {
        if (valueToFind == arr[i])
        {
            cout << "Linear Search: Found " << valueToFind << " at index " << i << endl;
            return;
        }
    }
}