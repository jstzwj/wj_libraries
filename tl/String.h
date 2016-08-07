#pragma once
#include"..\types.h"
#include"iterator.h"
#include"traits.h"
#include"Allocator.h"
namespace wl
{
	
	/// <summary>
	/// Const itertor
	/// </summary>
    template<class T>
	class ConstStringIterator
        :public iterator<random_access_iterator_tag, T>
	{
	public:
		typedef random_access_iterator_tag iterator_category;     // 迭代器类型


	private:
        const T * p;

	public:
		//constructor
        ConstStringIterator(const T * otherPtr) : p(otherPtr) {}
        ConstStringIterator() {}
        ConstStringIterator(const ConstStringIterator& otherIterator) : p(otherIterator.p) {}

		// equal and inequal operator
        bool operator==(const ConstStringIterator& other) const { return p == other.p; }
        bool operator!=(const ConstStringIterator& other) const { return p != other.p; }

		//Pointer operator
        const T & operator*() const { return *p; }
        const T * operator->() const { return &*p; }

		//Move iterator
        ConstStringIterator& operator++() { return *(++p); }
        ConstStringIterator operator++(int) { return *(p++); }
        ConstStringIterator& operator--() { return *(--p); }
        ConstStringIterator operator--(int) { return *(p--); }

		//Random move
        ConstStringIterator operator+(ptrdiff dis) { return p + dis; }
        ConstStringIterator operator-(ptrdiff dis) { return p - dis; }
	};

	/// <summary>
	/// Itertor of string
	/// </summary>
    template<class T>
	class StringIterator
        :public iterator<random_access_iterator_tag, T>
	{
	public:
		typedef random_access_iterator_tag iterator_category;     // 迭代器类型
        typedef T* pointer;


	private:
        T * p;

	public:
		//constructor
        StringIterator(T * otherPtr) : p(otherPtr) {}
        StringIterator() {}
        StringIterator(const StringIterator& otherIterator) : p(otherIterator.p) {}

		// equal and inequal operator
        bool operator==(const StringIterator& other) const { return p == other.p; }
        bool operator!=(const StringIterator& other) const { return p != other.p; }

		//Pointer operator
        T & operator*() const { return *p; }
        T * operator->() const { return &*p; }

		//Move iterator
        StringIterator& operator++() { return *(++p); }
        StringIterator operator++(int) { return *(p++); }
        StringIterator& operator--() { return *(--p); }
        StringIterator operator--(int) { return *(p--); }

		//Random move
        StringIterator operator+(ptrdiff dis) { return p + dis; }
        StringIterator operator-(ptrdiff dis) { return p - dis; }
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

        typedef StringIterator<T> iterator;
        typedef ConstStringIterator<T> const_iterator;
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


