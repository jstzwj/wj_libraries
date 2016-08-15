#pragma once


#include<new>
#include"..\types.h"

namespace wl
{
	/// <summary>
	/// The type represents the basic allocator using new and delete.
	/// </summary>
	template<class T>
	class Allocator :public Object,public NonCopyable
	{
	public:
		typedef T                 value_type;
		typedef value_type*       pointer;
		typedef const value_type* const_pointer;
		typedef value_type&       reference;
		typedef const value_type& const_reference;
		typedef wsize			size_type;
		typedef ptrdiff			difference_type;
	public:
		//rebind other allocator
		template <class U>
		struct rebind
		{
			typedef Allocator<U> other;
		};
		//New a object
		static pointer allocate(size_type n, const_pointer = 0) 
		{
			T* p= static_cast<T *>(::operator new (n*sizeof(T)) );	//operator new
			return static_cast<pointer>(p);
		}
		//Delete the object
		static void deallocate(pointer p, size_type)
		{
			::operator delete(p);
		}
		//Call construct function
		static void construct(pointer p, const value_type& x)
		{
			new(p) value_type(x);	//placement new
		}
		//Call deconstruct function
		static void destroy(pointer p)
		{
			p->~value_type(); 
		}
		//Get the address of object
		static pointer address(reference x)
		{
			return static_cast<pointer>(&x);
		}
		static pointer const_address(const_reference x)
		{
			return static_cast<const_pointer>(&x);
		}
		//The largest number of this value type that computer can express.
		static size_type max_size()
		{
			return static_cast<size_type>(-1) / sizeof(value_type);
		}
		//Compare two allocator
		bool operator==(const Allocator<T>& rhs)
		{
			return true;
		}
		bool operator!=(const Allocator<T>& rhs)
		{
			return false;
		}
	};
}


