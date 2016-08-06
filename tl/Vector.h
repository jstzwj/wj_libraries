#pragma once

#ifndef VECTOR
#define VECTOR
#include"Allocator.h"
#include"iterator.h"

namespace wl
{

	/// <summary>
	/// The iterator of vector
	/// </summary>
	template<class T>
	class ConstVectorIterator
		:public iterator<random_access_iterator_tag,T>
	{
	private:
		const T * p;
		
	public:
		typedef VectorIterator             iterator;
		typedef random_access_iterator_tag iterator_category;     // µü´úÆ÷ÀàÐÍ
	
	public:
		//constructor
		iterator(pointer otherPtr) : p(otherPtr) {}
		iterator() {}
		iterator(const iterator& otherIterator) : p(otherIterator.p) {}

		// equal and inequal operator
		bool operator==(const iterator& other) const { return p == other.p; }
		bool operator!=(const iterator& other) const { return p != other.p; }

		//Pointer operator
		reference operator*() const { return *p; }
		pointer operator->() const { return &*p; }

		//Move iterator
		iterator& operator++() { return *(++p); }
		iterator operator++(int) { return *(p++); }
		iterator& operator--() { return *(--p); }
		iterator operator--(int) { return *(p--); }

		//Random move
		iterator operator+(ptrdiff dis) { return p + dis; }
		iterator operator-(ptrdiff dis) { return p - dis; }
		iterator& operator+=(const iterator &other) { p += other; return p; }
		iterator& operator-=(const iterator &other) { p -= other; return p; }
		iterator& operator+=(different_type n) { p += n; return p; }
		iterator& operator-=(different_type n) { p -= n; return p; }

		//assignment
		iterator & operator=(const iterator & other) { p = other.p; return *this; };

		//compare
		bool operator>(const iterator & other) { return p > other.p; }
		bool operator<(const iterator & other) { return p < other.p; }
		bool operator>=(const iterator & other) { return p >= other.p; }
		bool operator<=(const iterator & other) { return p <= other.p; }
		


	};


	template<class T>
	class VectorIterator
		:public ConstVectorIterator<T>
	{
	private:
		T * p;
	};


	/// <summary>
	/// The base of vecor , which is used to allocate the memory of vector.
	/// </summary>
	template<class T, class alloc = Allocator<T> >
	class VectorBase
	{
	public:
		typedef VectorBase<T, alloc> MyType;
		typedef alloc allocator_type;

		typedef typename T value_type;
		typedef typename wsize size_type;
		typedef typename ptrdiff difference_type;
		typedef typename T * pointer;
		typedef typename const T * const_pointer;
		typedef typename T & reference;
		typedef typename const T & const_reference;

		typedef VectorIterator<T> iterator;
		typedef ConstVectorIterator<T> const_iterator;
	private:
		pointer start;
		pointer finish;
		pointer end_of_storage;

	public:
		VectorBase()
			:start(NULL), finish(NULL), end_of_storage(NULL) {}
		//VectorBase(const VectorBase & other);


	public:
		iterator begin() { return start; }
		iterator end() { return finish; }
		const_iterator cbegin() { return start; }
		const_iterator cend() { return finish; }

		size_type size() { return finish - start; }
		size_type capacity() { return end_of_storage - start; }

		bool empty() { return start == finish; }
		reference operator[] (size_type n) { return *(start + n); }

	};





	template<class T,class alloc=Allocator<T> >
	class Vector:VectorBase<T,alloc>
	{
	public:
		typedef vector<T, alloc> MyType;
		typedef alloc allocator_type;

		typedef typename T value_type;
		typedef typename wsize size_type;
		typedef typename ptrdiff difference_type;
		typedef typename T * pointer;
		typedef typename const T * const_pointer;
		typedef typename T & reference;
		typedef typename const T & const_reference;

		typedef VectorIterator iterator;

	protected:



	};






}
#endif // !VECTOR
