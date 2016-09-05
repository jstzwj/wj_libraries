#pragma once

#ifndef VECTOR
#define VECTOR
#include"Allocator.h"
#include"iterator.h"
#include"memory.h"
#include"algobase.h"
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
		typedef ConstVectorIterator             iterator;
	public:
		typedef random_access_iterator_tag iterator_category;     // µü´úÆ÷ÀàÐÍ

	public:
		//constructor
		ConstVectorIterator(pointer otherPtr) : p(otherPtr) {}
		ConstVectorIterator() {}
		ConstVectorIterator(const iterator& otherIterator) : p(otherIterator.p) {}

		// equal and inequal operator
		bool operator==(const ConstVectorIterator& other) const { return p == other.p; }
		bool operator!=(const ConstVectorIterator& other) const { return p != other.p; }

		//Pointer operator
		reference operator*() const { return *p; }
		pointer operator->() const { return &*p; }

		//Move iterator
		ConstVectorIterator& operator++() { ++p; return *this; }
		ConstVectorIterator operator++(int)
		{
			ConstVectorIterator tmp(*this);
			p++;
			return tmp;
		}
		ConstVectorIterator& operator--() { --p; return *this; }
		ConstVectorIterator operator--(int)
		{
			ConstVectorIterator tmp(*this);
			p--;
			return tmp;
		}

		//Random move
		ConstVectorIterator operator+(ptrdiff dis) const{ return p + dis; }
		ConstVectorIterator operator-(ptrdiff dis) const{ return p - dis; }
		ConstVectorIterator& operator+=(const ConstVectorIterator &other) { p += other; return p; }
		ConstVectorIterator& operator-=(const ConstVectorIterator &other) { p -= other; return p; }
		ConstVectorIterator& operator+=(difference_type n) { p += n; return p; }
		ConstVectorIterator& operator-=(difference_type n) { p -= n; return p; }

		//assignment
		ConstVectorIterator & operator=(const ConstVectorIterator & other) { p = other.p; return *this; };

		//compare
		bool operator>(const ConstVectorIterator & other)const { return p > other.p; }
		bool operator<(const ConstVectorIterator & other)const { return p < other.p; }
		bool operator>=(const ConstVectorIterator & other)const { return p >= other.p; }
		bool operator<=(const ConstVectorIterator & other)const { return p <= other.p; }
		


	};


	template<class T>
	class VectorIterator
		:public ConstVectorIterator<T>
	{
	private:
		T * p;
		typedef VectorIterator             iterator;
	public:
		//constructor
		VectorIterator(pointer otherPtr) : p(otherPtr) {}
		VectorIterator() {}
		VectorIterator(const iterator& otherIterator) : p(otherIterator.p) {}
		// equal and inequal operator
		bool operator==(const VectorIterator& other) const { return p == other.p; }
		bool operator!=(const VectorIterator& other) const { return p != other.p; }
		//Pointer operator
		reference operator*() const { return *p; }
		pointer operator->() const { return &*p; }

		//Move iterator
		VectorIterator& operator++() { ++p; return *this; }
		VectorIterator operator++(int) 
		{ 
			VectorIterator tmp(*this);
			p++; 
			return tmp; 
		}
		VectorIterator& operator--() { --p; return *this; }
		VectorIterator operator--(int) 
		{ 
			VectorIterator tmp(*this);
			p--; 
			return tmp; 
		}

		//Random move
		VectorIterator operator+(ptrdiff dis) const { return p + dis; }
		VectorIterator operator-(ptrdiff dis) const { return p - dis; }
		VectorIterator& operator+=(const VectorIterator &other) { p += other; return p; }
		VectorIterator& operator-=(const VectorIterator &other) { p -= other; return p; }
		VectorIterator& operator+=(difference_type n) { p += n; return p; }
		VectorIterator& operator-=(difference_type n) { p -= n; return p; }

		//assignment
		VectorIterator & operator=(const VectorIterator & other) { p = other.p; return *this; };

		//compare
		bool operator>(const VectorIterator & other)const { return p > other.p; }
		bool operator<(const VectorIterator & other)const { return p < other.p; }
		bool operator>=(const VectorIterator & other)const { return p >= other.p; }
		bool operator<=(const VectorIterator & other)const { return p <= other.p; }


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

		//alloc allocator;
	public:
		VectorBase()
			:start(NULL), finish(NULL), end_of_storage(NULL) {}
		VectorBase(const VectorBase & other)
		{
			start = allocator.allocate(other.size());
			finish = uninitialized_copy(other.start, other.finish, start);
			end_of_storage = finish;
		}
		VectorBase(long n, const T &value)
		{
			start = alloc::allocate(n);
			uninitialized_fill_n(start,n,value);
			finish = start + n;
			end_of_storage = finish;
		}
		~VectorBase()
		{
			destroy(start,finish);
			alloc::deallocate(start,end_of_storage-start);
		}
	public:
		iterator begin() { return start; }
		iterator end() { return finish; }
		const_iterator cbegin() { return start; }
		const_iterator cend() { return finish; }

		reference front() { return *start; }
		reference back() { return *(finish-1); }

		size_type size() { return finish - start; }
		size_type capacity() { return end_of_storage - start; }

		bool empty() { return start == finish; }
		reference operator[] (size_type n) { return *(start + n); }

		iterator erase(iterator n)
		{
			if (n<start||n>=finish)
			{
				throw "Erase error:Iterator is out of range.";
			}
			if (n+1!=end())
			{
				destroy(n);
				copy(n+1,iterator(finish),n);
			}
			else
			{
				destroy(n);
			}
			--finish;
			return n;
		}

	};





	template<class T,class alloc=Allocator<T> >
	class Vector:public VectorBase<T,alloc>
	{
	public:
		typedef Vector<T, alloc> MyType;
		typedef alloc allocator_type;

		typedef typename T value_type;
		typedef typename wsize size_type;
		typedef typename ptrdiff difference_type;
		typedef typename T * pointer;
		typedef typename const T * const_pointer;
		typedef typename T & reference;
		typedef typename const T & const_reference;

		typedef VectorIterator<T> iterator;


		Vector():VectorBase{}
		Vector(const Vector & other):VectorBase(other){}
		Vector(long n, const T &value)
		:VectorBase<T>(n,value){}
	protected:



	};






}
#endif // !VECTOR
