#include <iostream>
#include <cstdlib>
#include <ctime>
#include <chrono>
#include <algorithm>
#include <cmath>

using namespace std;

const int arraySize = 100000;

void linear_Search(int *arr, int valueToFind);
void binary_Search(int *arr, int valueToFind);
void ternary_Search(int *arr, int valueToFind);
void jump_Search(int *arr, int valueToFind);
void interpolation_Search(int *arr, int valueToFind);
int fibonacci_Search(int *arr, int valueToFind);

int main()
{
    srand(static_cast<unsigned>(time(nullptr)));

    int arr[arraySize];

    for (int i = 0; i < arraySize; ++i)
    {
        arr[i] = rand() % 1000000 + 1; // Generate a random number between 1 and 1000000
    }

    int indexToFind = rand() % arraySize;

    auto start = chrono::high_resolution_clock::now();

    linear_Search(arr, arr[indexToFind]);

    auto end = chrono::high_resolution_clock::now();

    cout << "Linear Search took " << chrono::duration_cast<chrono::nanoseconds>(end - start).count() << " nanoseconds to run" << endl;

    int copyArr[arraySize];
    for (int i = 0; i < arraySize; ++i)
    {
        copyArr[i] = arr[i];
    }

    sort(copyArr, copyArr + arraySize);

    start = chrono::high_resolution_clock::now();

    binary_Search(copyArr, arr[indexToFind]);

    end = chrono::high_resolution_clock::now();

    cout << "Binary Search took " << chrono::duration_cast<chrono::nanoseconds>(end - start).count() << " nanoseconds to run" << endl;

    start = chrono::high_resolution_clock::now();

    ternary_Search(copyArr, arr[indexToFind]);

    end = chrono::high_resolution_clock::now();

    cout << "Ternary Search took " << chrono::duration_cast<chrono::nanoseconds>(end - start).count() << " nanoseconds to run" << endl;

    start = chrono::high_resolution_clock::now();

    jump_Search(copyArr, arr[indexToFind]);

    end = chrono::high_resolution_clock::now();

    cout << "Jump Search took " << chrono::duration_cast<chrono::nanoseconds>(end - start).count() << " nanoseconds to run" << endl;

    start = chrono::high_resolution_clock::now();

    interpolation_Search(copyArr, arr[indexToFind]);

    end = chrono::high_resolution_clock::now();

    cout << "Interpolation Search took " << chrono::duration_cast<chrono::nanoseconds>(end - start).count() << " nanoseconds to run" << endl;

    start = chrono::high_resolution_clock::now();

    int result = fibonacci_Search(copyArr, arr[indexToFind]);

    end = chrono::high_resolution_clock::now();

    cout << "Fibonacci Search took " << chrono::duration_cast<chrono::nanoseconds>(end - start).count() << " nanoseconds to run" << endl;

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

void binary_Search(int *arr, int valueToFind)
{
    int l = 0, r = arraySize - 1;
    while (l <= r)
    {
        int m = l + (r - l) / 2;
        if (arr[m] == valueToFind)
        {
            cout << "Binary Search: Found " << valueToFind << " at index " << m << endl;
            return;
        }
        if (arr[m] < valueToFind)
            l = m + 1;
        else
            r = m - 1;
    }
    cout << "not found" << endl;
}

void ternary_Search(int *arr, int valueToFind)
{
    int l = 0, r = arraySize - 1;
    while (l <= r)
    {
        int mid1 = l + (r - l) / 3;
        int mid2 = r - (r - l) / 3;

        if (arr[mid1] == valueToFind)
        {
            cout << "Ternary Search: Found " << valueToFind << " at index " << mid1 << endl;
            return;
        }

        if (arr[mid2] == valueToFind)
        {
            cout << "Ternary Search: Found " << valueToFind << " at index " << mid2 << endl;
            return;
        }

        if (valueToFind < arr[mid1])
            r = mid1 - 1;
        else if (valueToFind > arr[mid2])
            l = mid2 + 1;
        else
        {
            l = mid1 + 1;
            r = mid2 - 1;
        }
    }
    cout << "not found" << endl;
}

void jump_Search(int *arr, int valueToFind)
{
    int step = sqrt(arraySize);
    int prev = 0;

    while (arr[min(step, arraySize) - 1] < valueToFind)
    {
        prev = step;
        step += sqrt(arraySize);
        if (prev >= arraySize)
        {
            cout << "not found" << endl;
            return;
        }
    }

    for (int i = prev; i < min(step, arraySize); ++i)
    {
        if (arr[i] == valueToFind)
        {
            cout << "Jump Search: Found " << valueToFind << " at index " << i << endl;
            return;
        }
    }

    cout << "not found" << endl;
}

void interpolation_Search(int *arr, int valueToFind)
{
    int l = 0, r = arraySize - 1;

    while (l <= r && arr[l] <= valueToFind && arr[r] >= valueToFind)
    {
        // Use interpolation formula to find the probable position
        int pos = l + ((valueToFind - arr[l]) * (r - l)) / (arr[r] - arr[l]);

        if (arr[pos] == valueToFind)
        {
            cout << "Interpolation Search: Found " << valueToFind << " at index " << pos << endl;
            return;
        }

        if (arr[pos] < valueToFind)
            l = pos + 1;
        else
            r = pos - 1;
    }

    cout << "not found" << endl;
}

int fibonacci_Search(int *arr, int valueToFind)
{
    int fibM_minus_2 = 0;                   // (m-2)'th Fibonacci number
    int fibM_minus_1 = 1;                   // (m-1)'th Fibonacci number
    int fibM = fibM_minus_1 + fibM_minus_2; // m'th Fibonacci number

    // Find the smallest Fibonacci number greater than or equal to array size
    while (fibM < arraySize)
    {
        fibM_minus_2 = fibM_minus_1;
        fibM_minus_1 = fibM;
        fibM = fibM_minus_1 + fibM_minus_2;
    }

    int offset = -1; // Offset to start comparing from

    while (fibM > 1)
    {
        // Check if fibM_minus_2 is a valid index
        int i = min(offset + fibM_minus_2, arraySize - 1);

        // If the element is greater than the target value, move fibM positions back
        if (arr[i] > valueToFind)
        {
            fibM = fibM_minus_2;
            fibM_minus_1 = fibM_minus_1 - fibM_minus_2;
            fibM_minus_2 = fibM - fibM_minus_1;
        }
        // If the element is smaller than the target value, move fibM positions ahead
        else if (arr[i] < valueToFind)
        {
            fibM = fibM_minus_1;
            fibM_minus_1 = fibM_minus_2;
            fibM_minus_2 = fibM - fibM_minus_1;
            offset = i;
        }
        // Element found
        else
        {
            return i;
        }
    }

    // Compare the last element
    if (fibM_minus_1 && arr[offset + 1] == valueToFind)
    {
        return offset + 1;
    }

    // If not found, return -1
    return -1;
}