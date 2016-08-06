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
		typedef typename random_access_iterator_tag iterator_category;
		typedef typename T value_type;
		typedef typename wsize difference_type;
		typedef typename T* pointer;
		typedef typename T& reference;
	};

	template<typename T>
	struct iterator_traits<const T*>
	{
		typedef typename random_access_iterator_tag iterator_category;
		typedef typename T value_type;
		typedef typename wsize difference_type;
		typedef typename T* pointer;
		typedef typename T& reference;
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

	/*
	type traits
	*/
	struct true_type{};
	struct false_type {};

	template<class T>
	struct type_traits
	{
		typedef true_type    this_dummy_member_must_be_first;

		typedef false_type   has_trivial_default_constructor;
		typedef false_type   has_trivial_copy_constructor;
		typedef false_type   has_trivial_assignment_operator;
		typedef false_type   has_trivial_destructor;
		typedef false_type    is_POD_type;
	};
	template<>
	struct type_traits<bool>
	{
		typedef true_type   has_trivial_default_constructor;
		typedef true_type   has_trivial_copy_constructor;
		typedef true_type   has_trivial_assignment_operator;
		typedef true_type   has_trivial_destructor;
		typedef true_type    is_POD_type;
	};
	template<>
	struct type_traits<char>
	{
		typedef true_type   has_trivial_default_constructor;
		typedef true_type   has_trivial_copy_constructor;
		typedef true_type   has_trivial_assignment_operator;
		typedef true_type   has_trivial_destructor;
		typedef true_type    is_POD_type;
	};
	template<>
	struct type_traits<unsigned char>
	{
		typedef true_type   has_trivial_default_constructor;
		typedef true_type   has_trivial_copy_constructor;
		typedef true_type   has_trivial_assignment_operator;
		typedef true_type   has_trivial_destructor;
		typedef true_type    is_POD_type;
	};
	template<>
	struct type_traits<short>
	{
		typedef true_type   has_trivial_default_constructor;
		typedef true_type   has_trivial_copy_constructor;
		typedef true_type   has_trivial_assignment_operator;
		typedef true_type   has_trivial_destructor;
		typedef true_type    is_POD_type;
	};
	template<>
	struct type_traits<unsigned short>
	{
		typedef true_type   has_trivial_default_constructor;
		typedef true_type   has_trivial_copy_constructor;
		typedef true_type   has_trivial_assignment_operator;
		typedef true_type   has_trivial_destructor;
		typedef true_type    is_POD_type;
	};
	template<>
	struct type_traits<int>
	{
		typedef true_type   has_trivial_default_constructor;
		typedef true_type   has_trivial_copy_constructor;
		typedef true_type   has_trivial_assignment_operator;
		typedef true_type   has_trivial_destructor;
		typedef true_type    is_POD_type;
	};
	template<>
	struct type_traits<unsigned int>
	{
		typedef true_type   has_trivial_default_constructor;
		typedef true_type   has_trivial_copy_constructor;
		typedef true_type   has_trivial_assignment_operator;
		typedef true_type   has_trivial_destructor;
		typedef true_type    is_POD_type;
	};
	template<>
	struct type_traits<long>
	{
		typedef true_type   has_trivial_default_constructor;
		typedef true_type   has_trivial_copy_constructor;
		typedef true_type   has_trivial_assignment_operator;
		typedef true_type   has_trivial_destructor;
		typedef true_type    is_POD_type;
	};
	template<>
	struct type_traits<unsigned long>
	{
		typedef typename true_type   has_trivial_default_constructor;
		typedef true_type   has_trivial_copy_constructor;
		typedef true_type   has_trivial_assignment_operator;
		typedef true_type   has_trivial_destructor;
		typedef true_type    is_POD_type;
	};
	template<>
	struct type_traits<long long>
	{
		typedef true_type   has_trivial_default_constructor;
		typedef true_type   has_trivial_copy_constructor;
		typedef true_type   has_trivial_assignment_operator;
		typedef true_type   has_trivial_destructor;
		typedef true_type    is_POD_type;
	};
	template<>
	struct type_traits<unsigned long long>
	{
		typedef true_type   has_trivial_default_constructor;
		typedef true_type   has_trivial_copy_constructor;
		typedef true_type   has_trivial_assignment_operator;
		typedef true_type   has_trivial_destructor;
		typedef true_type    is_POD_type;
	};
	template<>
	struct type_traits<float>
	{
		typedef true_type   has_trivial_default_constructor;
		typedef true_type   has_trivial_copy_constructor;
		typedef true_type   has_trivial_assignment_operator;
		typedef true_type   has_trivial_destructor;
		typedef true_type    is_POD_type;
	};
	template<>
	struct type_traits<double>
	{
		typedef true_type   has_trivial_default_constructor;
		typedef true_type   has_trivial_copy_constructor;
		typedef true_type   has_trivial_assignment_operator;
		typedef true_type   has_trivial_destructor;
		typedef true_type    is_POD_type;
	};
	template<>
	struct type_traits<long double>
	{
		typedef true_type   has_trivial_default_constructor;
		typedef true_type   has_trivial_copy_constructor;
		typedef true_type   has_trivial_assignment_operator;
		typedef true_type   has_trivial_destructor;
		typedef true_type    is_POD_type;
	};
	template<class T>
	struct type_traits<T *>
	{
		typedef true_type   has_trivial_default_constructor;
		typedef true_type   has_trivial_copy_constructor;
		typedef true_type   has_trivial_assignment_operator;
		typedef true_type   has_trivial_destructor;
		typedef true_type    is_POD_type;
	};
	
}

#endif // !TRAITS


