#ifndef _QUICKSELECT_H_
#define _QUICKSELECT_H_

#include <vector>
#include "quickSort.h"

/*****************************************************************************
** NAME: quickSelect(vector<Object>&, Comparator);
** 		quickSelect(vector<Object>& v, long med, Comparator cmp);
** 		quickSelect(vector<Object>&, long, long, long, Comparator);
** DESCRIPTION: (def'n: Median: The middle value of an ordered set of values)
** 				Modified quickSort routine. The Kth smallest value is put in it's
** 				proper place with all smaller values on the left, and all larger
** 				values on the right.  However, there is no particular order to the
** 				larger or smaller values.	By leaving the values to the left or the
** 				right of the wanted value unsorted, complexity of quickSelect is O(n),
** 				out-performing that of quickSort running O(n lg n).
** 				***NOTE*** There is no .cpp companion source file for this header
** 				file as both quicksort and partition are templated functions.
** PARAMETERS:	vector<Object>& v - Vector container defined by STL. - by reference -
** 				long left, right - range of the vector to look for the median value
** 				long med -	The Kth smallest item to be found. (in most cases,
** 								the median value = vectorSize / 2
** 				Comparator -defines how object should be evaluated. ie. how is an
** 								object "less/greater than" another?
** RETURN:		void - vector passed by reference returns *partially* sorted vector.
******************************************************************************/
template<class Object, class Comparator>
void quickSelect(vector<Object>& v, Comparator cmp)
{
	quickSelect(v, 0, v.size()-1, (v.size()-1) / 2, cmp);
}

template<class Object, class Comparator>
void quickSelect(vector<Object>& v, long med, Comparator cmp)
{
	quickSelect(v, 0, v.size()-1, med, cmp);
}

template<class Object, class Comparator>
void quickSelect(vector<Object>& v, long left, long right, long med, Comparator cmp)
{
	if(left<right)
	{
		long x = (rand() % (right+1-left)) + left;		// Randomized pivot generator

		Swap(v[left], v[x]);

		Object pivot = v[left];
		int i=left;
		int j=right+1;

		do
		{
			do i++;
			while(!cmp(pivot, v[i]) && i<=right);		// This has to check the upperbound of the vector.
																	// Without it, some input would cause i to run off into infinity.
			do j--;
			while(cmp(pivot, v[j]));						// Shouldnt have to check lowerbound here, j should always
																	// just run into the pivot before getting out of hand.
			if(i<j)
				Swap(v[i], v[j]);

		} while(i<j);

		Swap(v[j], v[left]);

		if(left<i && med<=j)
			quickSelect(v, left, j-1, med, cmp);
		else if(i<right)
			quickSelect(v, j+1, right, med, cmp);
	}
}

#endif
