/**
 * @file    Util.h
 * @brief   Personal C++ Utility Library
 * @details A header-only library of helper functions, algorithm
 *          implementations, and data structure utilities.
 *
 * @author  Laurence Rugley
 * @version 1.1
 *
 * USAGE:
 *   #include "Util.h"
 *
 * NAMESPACES:
 *   Util::    — General helpers (random, swap, array fill/print, string box)
 *   Sort::    — Sorting algorithms and visual sort display
 *   Search::  — Search algorithms
 *   Timer::   — Runtime benchmarking using clock()
 *   Types::   — Useful typedefs
 */

#pragma once   // FIX 1: Prevents duplicate-include errors

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <iomanip>
#include <vector>
#include <fstream>
#include <algorithm>


// ─────────────────────────────────────────────────────────────────────────────
// Util — General purpose helpers
// ─────────────────────────────────────────────────────────────────────────────
namespace Util {

    /**
     * @brief   Generate a random integer in the range [a, b] inclusive.
     * @param   a  Lower bound
     * @param   b  Upper bound
     * @return  Random integer between a and b
     */
    int Random_Num(int a, int b)
    {
        return (a + rand() % (b - a + 1));
    }


    /**
     * @brief   Generic swap — works on any type T.
     * @tparam  T   Type of the values to swap
     * @param   a   First value
     * @param   b   Second value
     */
    template<typename T>
    void Swap(T &a, T &b)
    {
        T temp = b;
        b = a;
        a = temp;
    }


    /**
     * @brief   Fill an array with random integers in the given range.
     * @param   arr        Target array
     * @param   size       Number of elements to fill
     * @param   lowRange   Minimum value (inclusive)
     * @param   highRange  Maximum value (inclusive)
     *
     * FIX 2: Parameters lowRange and highRange are now actually used.
     *        Previous version hardcoded Random_Num(1, 9) regardless of args.
     */
    void Fill_Array(int arr[], int size, int lowRange, int highRange)
    {
        for (int i = 0; i < size; ++i)
        {
            arr[i] = Random_Num(lowRange, highRange);
        }
    }


    /**
     * @brief   Print an array to stdout, 10 elements per row.
     * @param   arr   Array to print
     * @param   size  Number of elements
     */
    void Print_Array(int arr[], int size)
    {
        for (int i = 0; i < size; ++i)
        {
            std::cout << std::setw(3) << arr[i] << std::setw(3);   // FIX 3: std:: explicit
            if ((i + 1) % 10 == 0)
            {
                std::cout << std::endl;
            }
        }
        std::cout << std::endl;
    }


    /**
     * @brief   Draw a simple text box around a string.
     * @param   str  String to box
     *
     * Example output for "Hello":
     *   -------
     *   !Hello!
     *   -------
     */
    void box_string(std::string str)
    {
        int n = str.length();

        if (n == 0)
        {
            std::cout << "Goodbye!" << std::endl;
            return;
        }

        for (int i = 0; i < n + 2; ++i) std::cout << "-";
        std::cout << std::endl;
        std::cout << "!" << str << "!" << std::endl;
        for (int i = 0; i < n + 2; ++i) std::cout << "-";
        std::cout << std::endl;
    }

} // namespace Util


// ─────────────────────────────────────────────────────────────────────────────
// Sort — Sorting algorithms and helpers
// ─────────────────────────────────────────────────────────────────────────────
namespace Sort {

    /**
     * @brief   Check whether an array is sorted in non-decreasing order.
     * @tparam  T     Element type
     * @param   arr   Array to check
     * @param   size  Number of elements
     * @return  true if sorted, false otherwise
     *
     * FIX 4: Loop bound changed from i < size to i < size - 1.
     *        Previous version read arr[size] (one past the end) on the
     *        last iteration — undefined behaviour.
     * FIX 5: Removed duplicate Is_Sorted from Util namespace.
     *        Sort:: is the correct home for this function.
     */
    template<typename T>
    bool Is_Sorted(T arr[], int size)
    {
        for (int i = 0; i < size - 1; ++i)   // FIX 4: was i < size
        {
            if (arr[i] > arr[i + 1])
            {
                return false;
            }
        }
        return true;
    }


    /**
     * @brief   Print a human-readable sorted / not sorted message.
     * @param   isSorted  Result of Is_Sorted()
     */
    void Sort_msg(bool isSorted)
    {
        if (isSorted)
            std::cout << "The list is sorted." << std::endl;
        else
            std::cout << "The list is not sorted." << std::endl;
    }


    /**
     * @brief   Print array with the current maximum element highlighted in [].
     * @details Used by Bubble_Sort to visualise each pass.
     * @param   arr   Array to display
     * @param   size  Number of elements
     */
    void showSort(int arr[], int size)
    {
        int maxElement = arr[0];
        for (int j = 1; j < size; ++j)
        {
            if (arr[j] > maxElement)
                maxElement = arr[j];
        }

        for (int i = 0; i < size; ++i)
        {
            if (arr[i] == maxElement)
                std::cout << std::setw(3) << "[" << arr[i] << "]" << std::setw(3);
            else
                std::cout << std::setw(3) << arr[i] << std::setw(3);
        }
        std::cout << std::endl;
    }


    /**
     * @brief   Bubble Sort with early-exit optimisation.
     * @details The flag variable causes the outer loop to stop as soon as
     *          a full pass completes with no swaps — meaning the array is
     *          already sorted. Best case O(n), worst case O(n²).
     * @param   arr   Array to sort (sorted in-place)
     * @param   size  Number of elements
     */
    void Bubble_Sort(int arr[], int size)
    {
        int flag = 1;
        for (int i = 0; i < size && flag; ++i)
        {
            flag = 0;
            for (int j = 0; j < size - 1; ++j)
            {
                if (arr[j] > arr[j + 1])
                {
                    Util::Swap(arr[j], arr[j + 1]);
                    flag = 1;
                }
            }
            showSort(arr, size);
        }
    }


    /**
     * @brief   Insertion Sort.
     * @details Efficient for small or nearly-sorted arrays. O(n) best case,
     *          O(n²) worst case. Stable sort.
     * @param   arr   Array to sort (sorted in-place)
     * @param   size  Number of elements
     */
    void Insertion_Sort(int arr[], int size)
    {
        for (int i = 1; i < size; ++i)
        {
            int key = arr[i];
            int j   = i - 1;
            while (j >= 0 && arr[j] > key)
            {
                arr[j + 1] = arr[j];
                --j;
            }
            arr[j + 1] = key;
        }
    }


    /**
     * @brief   Selection Sort.
     * @details Finds the minimum element and moves it to the front on each
     *          pass. Always O(n²) — use Insertion_Sort for nearly-sorted data.
     * @param   arr   Array to sort (sorted in-place)
     * @param   size  Number of elements
     */
    void Selection_Sort(int arr[], int size)
    {
        for (int i = 0; i < size - 1; ++i)
        {
            int minIdx = i;
            for (int j = i + 1; j < size; ++j)
            {
                if (arr[j] < arr[minIdx])
                    minIdx = j;
            }
            if (minIdx != i)
                Util::Swap(arr[i], arr[minIdx]);
        }
    }

} // namespace Sort


// ─────────────────────────────────────────────────────────────────────────────
// Search — Search algorithms
// ─────────────────────────────────────────────────────────────────────────────
namespace Search {

    /**
     * @brief   Sequential (linear) search.
     * @details Scans every element from index 0 to size-1. O(n).
     *          Works on unsorted and sorted arrays.
     * @param   arr   Array to search
     * @param   size  Number of elements
     * @param   key   Value to find
     * @return  Index of key if found, -1 if not found
     */
    int Linear_Search(int arr[], int size, int key)
    {
        for (int i = 0; i < size; ++i)
        {
            if (arr[i] == key)
                return i;
        }
        return -1;
    }


    /**
     * @brief   Recursive binary search.
     * @details Requires a sorted array. Divides the search range in half
     *          on each recursive call. O(log n).
     * @param   arr    Sorted array to search
     * @param   first  Start index of current search range
     * @param   last   End index of current search range
     * @param   key    Value to find
     * @return  Index of key if found, -1 if not found
     *
     * FIX 6: Implemented the empty stub that existed in v1.0.
     */
    int Binary_Search(int arr[], int first, int last, int key)
    {
        if (first > last)
            return -1;

        int mid = (first + last) / 2;

        if (arr[mid] == key)
            return mid;
        else if (key < arr[mid])
            return Binary_Search(arr, first, mid - 1, key);
        else
            return Binary_Search(arr, mid + 1, last, key);
    }

} // namespace Search


// ─────────────────────────────────────────────────────────────────────────────
// Timer — Simple runtime benchmarking
// ─────────────────────────────────────────────────────────────────────────────
namespace Timer {

    static clock_t _start = 0;

    /**
     * @brief   Start the timer.
     */
    void Start()
    {
        _start = clock();
    }

    /**
     * @brief   Stop the timer and return elapsed time in milliseconds.
     * @return  Elapsed milliseconds since Start() was called
     */
    double Stop()
    {
        clock_t end = clock();
        return (double)(end - _start) * 1000.0 / (double)CLOCKS_PER_SEC;
    }

    /**
     * @brief   Stop the timer and print the result with a label.
     * @param   label  Description printed alongside the time
     */
    void Stop_Print(std::string label)
    {
        double ms = Stop();
        std::cout << label << ": " << ms << " ms" << std::endl;
    }

} // namespace Timer


// ─────────────────────────────────────────────────────────────────────────────
// Types — Useful typedefs
// ─────────────────────────────────────────────────────────────────────────────
namespace Types {

    typedef std::vector<int>::iterator          vecIntIT;
    typedef std::vector<std::string>::iterator  vecStrIT;

} // namespace Types
