#pragma once
#ifndef ALGOBASE
#define ALGOBASE

#include"utility.h"
#include"iterator.h"

namespace wl
{

	//Equal all objects between first and last
	template<class InputIterator1, class InputIterator2>
	inline bool equal(InputIterator1 first1, InputIterator1 last1, InputIterator2 first2)
	{
		while (first1 != last1)
		{
			if (*first1 != *first2)
			{
				return false;
			}
			++first1;
			++first2;
		}
		return true;
	}
	//Equal by predicate
	template<class InputIterator1, class InputIterator2, class BinaryPredicate>
	inline bool equal(InputIterator1 first1, InputIterator1 last1, InputIterator2 first2, BinaryPredicate binary_predicate)
	{
		while (first1 != last1)
		{
			if (!binary_predicate(*first1, *first2))
			{
				return false;
			}
			++first1;
			++first2;
		}
		return true;
	}
	//Fill all objects with the value setted
	template<class ForwardIterator, class T>
	inline void fill(ForwardIterator first, ForwardIterator last, const T &value)
	{
		while (*first != *last)
		{
			*first = value;
			++first;
		}
	}
	//Fill_n
	template<class ForwardIterator, class Size, class T>
	inline void fill(ForwardIterator first, Size n, const T &value)
	{
		while (n > 0)
		{
			*first = value;
			--n;
			++first;
		}
	}
	//iter_swap
	template<class ForwardIterator1, class ForwardIterator2, class T>
	inline void iter_swap_aux(ForwardIterator1 a, ForwardIterator2 b, T *)
	{
		T tmp;
		tmp = *a;
		*a = *b;
		*b = tmp;
	}

	template<class ForwardIterator1, class ForwardIterator2>
	inline void iter_swap(ForwardIterator1 a, ForwardIterator2 b)
	{
                iter_swap_aux(a, b, iterator_traits<ForwardIterator1>::pointer());
	}

	//lexicographical_compare
	template <class InputIterator1, class InputIterator2>
	inline bool lexicographical_compare(InputIterator1 first1, InputIterator1 last1,
		InputIterator2 first2, InputIterator2 last2)
	{
		for (; first1 != last1 && first2 != last2; ++first1, ++first2)
		{
			if (*first1 < *first2)
			{
				return true;
			}
			if (*first2 < *first1)
			{
				return false;
			}
		}
		return first1 == last1 && first2 != last2;
	}
	template <class InputIterator1, class InputIterator2, class BinaryCompare>
	inline bool lexicographical_compare(InputIterator1 first1, InputIterator1 last1,
		InputIterator2 first2, InputIterator2 last2, BinaryCompare binary_compare)
	{
		for (; first1 != last1 && first2 != last2; ++first1, ++first2)
		{
			if (binary_compare(*first1, *first2))
			{
				return true;
			}
			if (binary_compare(*first2, *first1))
			{
				return false;
			}
		}
		return first1 == last1 && first2 != last2;
	}
	//max
	//Why not use two different types as template classes,just like <class T,class U> ?
	template<class T>
	inline T & max(const T & a, const T & b)
	{
		return a < b ? b : a;
	}
	//Why not use two different types as template classes,just like <class T,class U> ?
	template<class T, class BinaryCompare>
	inline T & max(const T& a, const T& b, BinaryCompare binary_compare)
	{
		return binary_compare(a, b) ? b : a;
	}
	//min
	//Why not use two different types as template classes,just like <class T,class U> ?
	template<class T>
	inline T& min(const T& a, const T& b)
	{
		return a < b ? a : b;
	}
	//Why not use two different types as template classes,just like <class T,class U> ?
	template<class T, class BinaryCompare>
	inline T& min(const T& a, const T& b, BinaryCompare binary_compare)
	{
		return binary_compare(a, b) ? a : b;
	}
	//mismatch
	template<class InputIterator1, class InputIterator2>
	inline pair<InputIterator1, InputIterator2> mismatch(InputIterator1 first1, InputIterator1 last1, InputIterator2 first2)
	{
		while (first1 != last1&&*first1 == *first2)
		{
			++first1;
			++first2;
		}
		return pair<InputIterator1, InputIterator2>(first1, first2);
	}
	template<class InputIterator1, class InputIterator2, class BinaryPredicate>
	inline pair<InputIterator1, InputIterator2> mismatch(InputIterator1 first1, InputIterator1 last1,
		InputIterator2 first2, BinaryPredicate binary_predicate)
	{
		while (first1 != last1&&binary_predicate(*first1, *first2))
		{
			++first1;
			++first2;
		}
		return pair<InputIterator1, InputIterator2>(first1, first2);
	}

        //swap (move to utility)
        /*
	template<class T>
	inline void swap(T&a, T&b)
	{
		T tmp;
		tmp = a;
		a = b;
		b = tmp;
	}
        */
        //copy
        template<class InputIterator, class OutputIterator>
        struct copy_dispatch
        {
                OutputIterator operator() (InputIterator first, InputIterator last, OutputIterator result)
                {
                        return copy_aux(first, last, result,typename iterator_traits<InputIterator>::iterator_category());
                }
        };

	template<class InputIterator, class OutputIterator>
	inline OutputIterator copy(InputIterator first, InputIterator last, OutputIterator result)
	{
		return copy_dispatch<InputIterator,OutputIterator>()(first, last, result);
	}

	template<class InputIterator, class OutputIterator>
	inline OutputIterator copy_aux(InputIterator first, InputIterator last, OutputIterator result, input_iterator_tag)
	{
		for (; first != last; ++first, ++result)
		{
			*result = *first;
		}
		return result;
	}
}
#endif // !ALGOBASE
