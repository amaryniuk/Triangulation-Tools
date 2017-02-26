#ifndef _QUICKSORT_H_
#define _QUICKSORT_H_

#include <vector>

/*****************************************************************************
 ** NAME:  Swap(Object&, Object&)
 ** DESCRIPTION: who knows what stl swap is doing?. made my own :)
 ** PARAMETERS:  two objects, passed by ref.
 ** RETURN:  void - both items passed by reference. returned in swapped positions.
 ******************************************************************************/
template<class Object>
void Swap(Object& one, Object& two)
{
  Object temp = one;
  one = two;
  two = temp;
}

/*****************************************************************************
 ** NAME:	bubbleSort(vector<Object>& v, Comparator cmp)
 ** DESCRIPTION:  Sorts a vector passed by reference and by the dimension specified
 **				 by the comparator cmp.  The bubble sort has complexity O(n^2) so
 **				 it is not at all efficient for larger data sets - but it does work
 **				 well for smaller data sets say, smaller that 50 points.
 ** PARAMETERS:  vector<Object>& v - Vector container defined by STL. - by reference -
 **				Comparator - defines how object should be evaluated.
 ******************************************************************************/
template<class Object, class Comparator>
void bubbleSort(vector<Object>& v, Comparator cmp)
{
  int i;
  bool swapElem = true;

  while (swapElem)
    {
      swapElem = false;
      for(i=0; i<v.size()-1; i++)
	if(cmp(v[i+1], v[i]))
	  {
	    Swap(v[i+1], v[i]);
	    swapElem = true;
	  }
    }
  return;
}

/*****************************************************************************
 ** NAME:	quickSort(vector<Object>&, Comparator);
 **			quickSort(vector<Object>&, long, long, Comparator);
 ** DESCRIPTION:  Sorts a vector of objects between a given index range and a
 **				 Comparator defining how the object should be evaluated.
 **				 Recursive calls to itself sorting the "Partitions" of the vector until
 **				 partition size == 1.  ***NOTE*** There is no .cpp companion source file
 **				 for this header file as both quicksort and partition are templated functions.
 **				 Im not sure why c++ doesnt handle this, but I really wish I knew earlier that
 **				 this was the case.  It would have saved me several days worth of headaches.
 **				 ***NOTE*** All calls to quickSort should invoke quickSort using the refined
 **				 reference quickSort(vector<obj>&, Comparator)
 **
 ** PARAMETERS:  vector<Object>& v - Vector container defined by STL. - by reference -
 **				long low, high - range of the vector to be sorted.
 **							   - sort entire vector with sort(v, 0, size-1);
 **				Comparator - defines how object should be evaluated.
 **						   - ie. how is an object "less/greater than" another?
 ** RETURN:  void - vector passed by reference returns sorted vector.
 ******************************************************************************/
template<class Object, class Comparator>
void quickSort(vector<Object>& v, Comparator cmp)
{
  quickSort(v, 0, v.size()-1, cmp);
}

template<class Object, class Comparator>
void quickSort(vector<Object>& v, long left, long right, Comparator cmp)
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
	  // while(cmp(v[i], pivot) && i<=right);		// This has to check the upperbound of the vector.
	  while(!cmp(pivot, v[i]) && i<=right);		// Without it, some input would cause i to run off into infinity.

	  do j--;
	  while(cmp(pivot, v[j]));					// Shouldnt have to check lowerbound here, j should always
	                                   // just run into the pivot before getting out of hand.
	  if(i<j)
	    Swap(v[i], v[j]);

	} while(i<j);

      Swap(v[j], v[left]);

      quickSort(v, left, j-1, cmp);
      quickSort(v, j+1, right, cmp);
    }
}

#endif
