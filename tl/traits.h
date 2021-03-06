#pragma once
#ifndef TRAITS
#define TRAITS

#include"iterator.h"
namespace wl
{
	/*
	iterator traits
	*/
	template<typename T>
	struct iterator_traits
	{
		typedef typename T::iterator_category iterator_category;
		typedef typename T::value_type value_type;
		typedef typename T::difference_type difference_type;
		typedef typename T::pointer pointer;
		typedef typename T::reference reference;
	};
	template<typename T>
	struct iterator_traits<T*>
	{
        typedef random_access_iterator_tag iterator_category;
        typedef T value_type;
        typedef wsize difference_type;
        typedef T* pointer;
        typedef T& reference;
	};

	template<typename T>
	struct iterator_traits<const T*>
	{
        typedef random_access_iterator_tag iterator_category;
        typedef T value_type;
        typedef wsize difference_type;
        typedef T* pointer;
        typedef T& reference;
	};
	//advance base
	template<class InputIterator, class Distance>
	void advanceBase(InputIterator p,Distance n,input_iterator_tag)
	{
		while (n--)
		{
			p++;
		}
	}
	template<class BidirectionalIterator, class Distance>
	void advanceBase(BidirectionalIterator p, Distance n,bidirectional_iterator_tag)
	{
		if (n >= 0)
		{
			while (n--)
			{
				p++;
			}
		}
		else
		{
			while (n++)
			{
				p++;
			}
		}
	}
	template<class RandomAccessIterator, class Distance>
	void advanceBase(RandomAccessIterator p, Distance n,random_access_iterator_tag)
	{
		p += n;
	}
	//advance
	template <class Iterator, class Distance>
	void advance(Iterator p,Distance n)
	{
		advanceBase(p,n, iterator_traits<Iterator>::iterator_category());
	}


	// calculate distance of pointers
	template<class InputIterator>
	typename iterator_traits<InputIterator>::difference_type
		distanceBase(InputIterator first,InputIterator second,input_iterator_tag)
	{
		typename iterator_traits<InputIterator>::difference_type n = 0;
		while (first!=second)
		{
			++first;
			++n;
		}
		return n;
	}
	template<class RandomAccessIterator>
	typename iterator_traits<RandomAccessIterator>::difference_type
		distanceBase(RandomAccessIterator first, RandomAccessIterator second,random_access_iterator_tag)
	{
		typename iterator_traits<RandomAccessIterator>::difference_type n = second - first;
		return n;
	}

	//distance
	template<class Iterator>
	typename iterator_traits<Iterator>::difference_type
		distanceBase(Iterator first, Iterator second)
	{
		typename iterator_traits<Iterator>::difference_type n;
		n = distanceBase(first,second, iterator_traits<Iterator>::iterator_category());
		return n;
	}


	
}

#endif // !TRAITS


