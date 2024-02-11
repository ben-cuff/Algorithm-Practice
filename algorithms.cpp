#include <iostream>
#include <cstdlib>
#include <ctime>
#include <chrono>
#include <algorithm>
#include <cmath>

using namespace std;

const int arraySize = 100000;

const int searchTests = 1000000;

void linear_Search(int *arr, int valueToFind);
void binary_Search(int *arr, int valueToFind);
void ternary_Search(int *arr, int valueToFind);
void jump_Search(int *arr, int valueToFind);
void runAllSearchAlgorithms();
void testingRuntime();

int main()
{

    srand(static_cast<unsigned>(time(nullptr))); // used for randomization

    cout << "This is my algorithm tester" << endl;
    string input = "";
    bool run = true;

    while (run)
    {

        // does input validation
        do
        {
            cout << "type 1 to run all of the search algorithms" << endl;
            cout << "type 2 to see data concerning a comprehensive test of the search algorithms" << endl;
            cout << "type 3 to end the program" << endl;

            cin >> input;

            if (input == "1")
            {
                runAllSearchAlgorithms(); // runs all of the search algorithms once
            }
            else if (input == "2")
            {
                testingRuntime(); // runs all of the search algorithms many times
            }
            else if (input == "3")
            {
                run = false;
            }

        } while (input != "1" && input != "2" && input != "3");
    }
    return 0;
}

/**
 * This function is intended to run a test of each of the algorithms in order to determine an average runtime.
 * It creates a random array and then searches it using each of the algorithms a number of times
 * Once it is done running, it prints the average runtime of the algorithm
 *
 * @pre None
 *
 * @post Prints to the console the average runtime of each algorithm after running a number of times
 *
 */
void testingRuntime()
{
    int arr[arraySize];

    for (int i = 0; i < arraySize; ++i)
    {
        arr[i] = rand() % 1000000 + 1; // Generate a random number between 1 and 1000000
    }

    int indexToFind;

    auto start = chrono::high_resolution_clock::now();

    for (int i = 0; i < searchTests; i++)
    {
        indexToFind = rand() % arraySize;
        linear_Search(arr, arr[indexToFind]);
    }

    auto end = chrono::high_resolution_clock::now();

    cout << "10000 linear searches took an average of " << chrono::duration_cast<chrono::nanoseconds>(end - start).count() / searchTests << " nanoseconds to run" << endl;

    int copyArr[arraySize];
    for (int i = 0; i < arraySize; ++i)
    {
        copyArr[i] = arr[i];
    }

    sort(copyArr, copyArr + arraySize);

    start = chrono::high_resolution_clock::now();

    for (int i = 0; i < searchTests; i++)
    {
        indexToFind = rand() % arraySize;
        binary_Search(copyArr, arr[indexToFind]);
    }

    end = chrono::high_resolution_clock::now();

    cout << "10000 binary searches took an average of " << chrono::duration_cast<chrono::nanoseconds>(end - start).count() / searchTests << " nanoseconds to run" << endl;

    start = chrono::high_resolution_clock::now();

    for (int i = 0; i < searchTests; i++)
    {
        indexToFind = rand() % arraySize;
        ternary_Search(copyArr, arr[indexToFind]);
    }

    end = chrono::high_resolution_clock::now();

    cout << "10000 ternary searches took an average of " << chrono::duration_cast<chrono::nanoseconds>(end - start).count() / searchTests << " nanoseconds to run" << endl;

    start = chrono::high_resolution_clock::now();

    for (int i = 0; i < searchTests; i++)
    {
        indexToFind = rand() % arraySize;
        jump_Search(copyArr, arr[indexToFind]);
    }

    end = chrono::high_resolution_clock::now();

    cout << "10000 jump searches took an average of " << chrono::duration_cast<chrono::nanoseconds>(end - start).count() / searchTests << " nanoseconds to run" << endl;
}

/**
 * This function is intended to test each of the algorithms once and then display the runtime.
 * It searches an array of a given size
 * These algorithms include a linear search, tinary search, ternary search and jump search.
 *
 * @pre none
 *
 * @post The runtime performance of each search algorithm is displayed on the console.
 *
 */
void runAllSearchAlgorithms()
{
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
}

/**
 * This function is intended to be an implementation of a linear search
 *
 * @param arr is a pointer to the first value in the array that is being searched
 * @param valueToFind is the value being searched for in the array
 *
 * @pre arr cannot be a nullptr and must be an array of ints.
 *
 * @post the function ends when the value has been found
 *
 */
void linear_Search(int *arr, int valueToFind)
{
    for (int i = 0; i < arraySize; i++)
    {
        if (valueToFind == arr[i])
        {
            return;
        }
    }
}

/**
 * This function is intended to be an implementation of a binary search
 *
 * @param arr is a pointer to the first value in the array that is being searched
 * @param valueToFind is the value being searched for in the array
 *
 * @pre arr cannot be a null pointer and must be a sorted array of ints
 *
 * @post the function ends when the value has been found
 *
 */
void binary_Search(int *arr, int valueToFind)
{
    int l = 0, r = arraySize - 1;
    while (l <= r)
    {
        int m = l + (r - l) / 2;
        if (arr[m] == valueToFind)
        {
            return;
        }
        if (arr[m] < valueToFind)
            l = m + 1;
        else
            r = m - 1;
    }
    cout << "not found" << endl;
}

/**
 * This function is intended to be an implementation of a ternary
 *
 * @param arr is a pointer to the first value in the array that is being searched
 * @param valueToFind is the value being searched for in the array
 *
 * @pre arr cannot be a null pointer and must be a sorted array of ints
 *
 * @post the function ends when the value has been found
 *
 */
void ternary_Search(int *arr, int valueToFind)
{
    int l = 0, r = arraySize - 1;
    while (l <= r)
    {
        int mid1 = l + (r - l) / 3;
        int mid2 = r - (r - l) / 3;

        if (arr[mid1] == valueToFind)
        {
            return;
        }

        if (arr[mid2] == valueToFind)
        {
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

/**
 * This function is intended to be an implementation of a jump search
 *
 * @param arr is a pointer to the first value in the array that is being searched
 * @param valueToFind is the value being searched for in the array
 *
 * @pre arr cannot be a null pointer and must be a sorted array of ints
 *
 * @post the function ends when the value has been found
 *
 */
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
            return;
        }
    }

    cout << "not found" << endl;
}
