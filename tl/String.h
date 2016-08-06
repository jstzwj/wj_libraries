#pragma once
#include"types.h"
#include"iterator.h"
#include"traits.h"
#include"Allocator.h"
namespace wl
{
	
	/// <summary>
	/// Const itertor
	/// </summary>
	template<class Ptr>
	class ConstStringIterator
		:public iterator<random_access_iterator_tag, 
		typename Ptr::value_type, 
		typename Ptr::different_type, 
		typename Ptr::pointer, 
		typename Ptr::reference>
	{
	public:
		typedef random_access_iterator_tag iterator_category;     // 迭代器类型
	
	private:
		typename Ptr::pointer p;
		typedef ConstStringIterator             iterator;
	public:
		//constructor
		iterator(pointer otherPtr) : p(otherPtr) {}
		iterator() {}
		iterator(const iterator& otherIterator) : p(otherIterator.p) {}

		// equal and inequal operator
		bool operator==(const iterator& other) const { return p == other.p; }
		bool operator!=(const iterator& other) const { return p != other.p; }

		//Pointer operator
		typename Ptr::reference operator*() const { return *p; }
		typename Ptr::pointer operator->() const { return &*p; }

		//Move iterator
		iterator& operator++() { return *(++p); }
		iterator operator++(int) { return *(p++); }
		iterator& operator--() { return *(--p); }
		iterator operator--(int) { return *(p--); }

		//Random move
		iterator operator+(ptrdiff dis) { return p + dis; }
		iterator operator-(ptrdiff dis) { return p - dis; }
	};

	/// <summary>
	/// Itertor of string
	/// </summary>
	template<class Ptr>
	class StringIterator
		:public iterator<random_access_iterator_tag, 
		typename Ptr::value_type, 
		typename Ptr::different_type, 
		typename Ptr::pointer, 
		typename Ptr::reference>
	{
	public:
		typedef random_access_iterator_tag iterator_category;     // 迭代器类型
	private:
		typename Ptr::pointer p;
		typedef StringIterator             iterator;
	public:
		//constructor
		iterator(pointer otherPtr) : p(otherPtr) {}
		iterator() {}
		iterator(const iterator& otherIterator) : p(otherIterator.p) {}

		// equal and inequal operator
		bool operator==(const iterator& other) const { return p == other.p; }
		bool operator!=(const iterator& other) const { return p != other.p; }

		//Pointer operator
		typename Ptr::reference operator*() const { return *p; }
		typename Ptr::pointer operator->() const { return &*p; }

		//Move iterator
		iterator& operator++() { return *(++p); }
		iterator operator++(int) { return *(p++); }
		iterator& operator--() { return *(--p); }
		iterator operator--(int) { return *(p--); }

		//Random move
		iterator operator+(ptrdiff dis) { return p + dis; }
		iterator operator-(ptrdiff dis) { return p - dis; }
	};





	/// <summary>
	/// A type representing a stringbase, which control the allocation of memory.
	/// </summary>
	template <class T,class allocator = Allocator<Char> >
	class StringBase
	{
	public:
		typedef T                 value_type;
		typedef value_type*       pointer;
		typedef const value_type* const_pointer;
		typedef value_type&       reference;
		typedef const value_type& const_reference;
		typedef wsize			size_type;
		typedef ptrdiff			difference_type;

		typedef StringIterator<T*> iterator;
		typedef ConstStringIterator<T*> const_iterator;
	private:
		Char * begin;
		Char * finish;
		Char * end_of_storage;
	public:
		StringBase();
		StringBase(Char * cstr);
		StringBase(const StringBase & cstr);

		virtual ~StringBase();
	};
	
	//Define string we used
	typedef StringBase<Char, Allocator<Char> > String;

	template<class T, class allocator>
	StringBase<T, allocator>::StringBase()
	{
	}
	template<class T, class allocator>
	inline StringBase<T, allocator>::StringBase(Char * cstr)
	{
	}
	template<class T, class allocator>
	inline StringBase<T, allocator>::StringBase(const StringBase & cstr)
	{
	}
	template<class T, class allocator>
	StringBase<T, allocator>::~StringBase()
	{
	}
	
	

}


