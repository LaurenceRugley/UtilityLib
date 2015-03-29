

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <iomanip>
#include <vector>
#include <fstream>
#include <algorithm>

using namespace std;


namespace Util {


/**
 * @brief random integer generator
 * 
 * @param a low range for integer		
 * @param b high range for integer
 * 
 * @return random number between a and b;
 */
	int Random_Num(int a, int b)
	{
		return (a + rand() % (b - a + 1));
	}

	/**
	 * @brief generic swap
	 *        
	 */
	template<typename T>
	void Swap(T &a, T &b)
	{
		T temp;
		temp = b;
		b = a;
		a = temp;
	}


	/**
	 * @brief fill array with random integers
	 *  
	 * @param range1 low range 	
	 * @param range2 high range
	 */
	void Fill_Array(int arr[], int size, int Lowrange1, int Highrange2)
	{

		for (int i = 0; i < size; ++i)
		{
			arr[i] = Random_Num(1, 9);
		}

	}


	/**
	 * @brief prints array
	 *        
	 */
	void Print_Array(int arr[], int size)
	{
		for (int i = 0; i < size; ++i)
	{
		cout << setw(3) << arr[i] << setw(3);
		if ((i + 1) % 10 == 0)
		{
			cout << endl;
		}
	}

	cout << endl;
	}


	/**
	 * @brief Check if a container is sorted
	 *        	
	 */
	template<typename T>
	bool Is_Sorted(T arr[], int size)
	{

		for (int i = 0; i < size; ++i)
		{
			if (arr[i] > arr[i + 1])
			{
				return false;
			}
		}
		
		return true;
	}


	/**
	 * @brief [brief description]
	 * @details [long description]
	 * 
	 * @param isSorted [description]
	 */
	void Sort_msg(bool isSorted)
	{
		if (isSorted)
		{
			cout << "The List is sorted." << endl;
		}
		else
		{
			cout << "The List is not sorted." << endl;
		}
	}


} // Util

namespace Sort {


	/**
	 * @brief Check if a container is sorted
	 *        	
	 */
	template<typename T>
	bool Is_Sorted(T arr[], int size)
	{

		for (int i = 0; i < size; ++i)
		{
			if (arr[i] > arr[i + 1])
			{
				return false;
			}
		}
		
		return true;
	}


	/**
	 * @brief [brief description]
	 * @details [long description]
	 * 
	 * @param isSorted [description]
	 */
	void Sort_msg(bool isSorted)
	{
		if (isSorted)
		{
			cout << "The List is sorted." << endl;
		}
		else
		{
			cout << "The List is not sorted." << endl;
		}
	}

void showSort(int arr[], int size)
{
	int start = 0;
	int maxElement = arr[start];
		for (int j = 0; j < size; ++j)
		{
			if (maxElement < arr[j + 1])
			{
				maxElement = arr[j + 1];
			}
		}

		//cout << maxElement << endl;
	

	for (int i = 0; i < size; ++i)
	{
		//cout << " max E =" << maxElement << " " << endl;
		if (arr[i] == maxElement)
		{
			cout << setw(3) << "[" << arr[i] << "]" << setw(3);
			
		}
		
		if (arr[i] != maxElement)
		{
			cout << setw(3) << arr[i] << setw(3);
		
		}	
}

cout << endl;	
	
}





	////////////////////////////
	//Slow Sorts on integers //
	////////////////////////////


	 /**
	  * @brief Bubble Sort
	  * @details [long description]
	  * 
	  * @param arr [description]
	  * @param size [description]
	  */
	void Bubble_Sort(int arr[], int size) 
	{
		int flag = 1;
		for (int i = 0; i < size && flag; ++i)
		{
			flag = 0;

			for (int j = 0; j < size - 1; j++)
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

} // Sort


namespace typedefs {

	typedef vector<int>::iterator vecIT; 


} // typdefs




