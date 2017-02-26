#pragma once
#ifndef MEMORY
#define MEMORY
#include<new>
#include"iterator.h"
#include"type_traits.h"
namespace wl
{
	template<class T,class V>
	void construct(T * p,const V & value)
	{
		new (p)T(value);
	}
	/*
	Call deconstruct function.
	*/
    template<class ForwardIterator>
    void destroy_aux(ForwardIterator p, true_type) {}

    template<class ForwardIterator>
    void destroy_aux(ForwardIterator p, false_type)
    {
        typedef typename iterator_traits<ForwardIterator>::value_type T;
        p->~T();
    }

    template<class ForwardIterator>
    void destroy_aux(ForwardIterator first, ForwardIterator last,true_type){}

    template<class ForwardIterator>
    void destroy_aux(ForwardIterator first, ForwardIterator last, false_type)
    {
        while (first != last)
        {
            first->~T();
            ++first;
        }
    }


	template<class T>
	void destroy(T *p)
	{
		//p->~T();
        destroy_aux(p, type_traits<typename iterator_traits<T *>::value_type>::has_trivial_destructor());
	}

	template<class Iterator>
	void destroy(Iterator p)
	{
		//p->~T();
        destroy_aux(p,type_traits<typename iterator_traits<Iterator>::value_type>::has_trivial_destructor());
	}

	template<class ForwardIterator>
	void destroy(ForwardIterator first, ForwardIterator last)
	{
        destroy_aux(first,last,typename type_traits<typename iterator_traits<ForwardIterator>::value_type >::has_trivial_destructor() );
	}






	template<class InputIterator, class ForwardIterator>
	ForwardIterator uninitialized_copy(InputIterator first, InputIterator last, ForwardIterator result)
	{
        return uninitialized_copy_aux(first,last,result,type_traits<typename iterator_traits<ForwardIterator>::value_name>::is_POD_type());
	}


	template<class InputIterator, class ForwardIterator>
	ForwardIterator uninitialized_copy_aux(InputIterator first, InputIterator last, ForwardIterator result,true_type)
	{
		//TODO
		return copy(first,last,result);
	}
	template<class InputIterator, class ForwardIterator>
	ForwardIterator uninitialized_copy_aux(InputIterator first, InputIterator last, ForwardIterator result, false_type)
	{
		while (first != last)
		{
			construct(result, *first);
			result++;
			first++;
		}
		return result;
	}




	template<class ForwardIterator, class T>
	void uninitialized_fill(ForwardIterator first, ForwardIterator last, const T &value)
	{
		uninitialized_fill_aux(first, last, value, type_traits<T>::is_POD_type());
	}


	template<class ForwardIterator, class T>
	void uninitialized_fill_aux(ForwardIterator first, ForwardIterator last, const T &value, true_type)
	{
		//TODO
		fill(first, last, value);
	}
	template<class ForwardIterator, class T>
	void uninitialized_fill_aux(ForwardIterator first, ForwardIterator last, const T &value, false_type)
	{
		while (first != last)
		{
			construct(first, value);
			first++;
		}
	}



	template<class ForwardIterator,class Size, class T>
	ForwardIterator uninitialized_fill_n(ForwardIterator first, Size n, const T &value)
	{
		//return uninitialized_fill_n_aux(first, n,value, type_traits<T>::is_POD_type());
		return uninitialized_fill_n_aux(first, n, value, false_type());
	}

	/*
	template<class ForwardIterator, class Size, class T>
	ForwardIterator uninitialized_fill_n_aux(ForwardIterator first, Size n, const T &value, true_type)
	{
		//TODO
		return fill_n(first, n, value);
	}
	*/
	template<class ForwardIterator, class Size, class T>
	ForwardIterator uninitialized_fill_n_aux(ForwardIterator first, Size n, const T &value, false_type)
	{
		while (n!=0)
		{
			construct(first, value);
			first++;
			n--;
		}
		return first;
	}




}


#endif // !MEMORY
