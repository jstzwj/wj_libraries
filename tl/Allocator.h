#pragma once


#include<new>
#include"..\types.h"
#include"type_traits.h"

namespace wl
{
	/// <summary>
	/// The type represents the basic allocator using new and delete.
	/// </summary>
	template<class T>
    class allocator
	{
	public:
        using value_type=T;
        using propagate_on_container_move_assignment=true_type;
        using is_always_equal=true_type;



        typedef value_type*       pointer;
        typedef const value_type* const_pointer;
        typedef value_type&       reference;
        typedef const value_type& const_reference;
        typedef wsize			size_type;
        typedef ptrdiff			difference_type;
	public:
        //ctor
        allocator()noexcept{}
        allocator( const allocator& other )noexcept{}
        template<class U>
        allocator( const allocator<U>& other )noexcept{}

		//rebind other allocator
		template <class U>
		struct rebind
		{
            typedef allocator<U> other;
		};
		//New a object
        pointer allocate(size_type n, const_pointer = 0)
		{
			T* p= static_cast<T *>(::operator new (n*sizeof(T)) );	//operator new
			return static_cast<pointer>(p);
		}
		//Delete the object
        void deallocate(pointer p, size_type)
		{
			::operator delete(p);
		}
		//Call construct function
        void construct(pointer p, const value_type& x)
		{
			new(p) value_type(x);	//placement new
		}
		//Call deconstruct function
        void destroy(pointer p)
		{
			p->~value_type(); 
		}
		//Get the address of object
        pointer address(reference x)
		{
			return static_cast<pointer>(&x);
		}
        pointer const_address(const_reference x)
		{
			return static_cast<const_pointer>(&x);
		}
		//The largest number of this value type that computer can express.
        size_type max_size()
		{
			return static_cast<size_type>(-1) / sizeof(value_type);
		}
		//Compare two allocator
        bool operator==(const allocator<T>& rhs)
		{
			return true;
		}
        bool operator!=(const allocator<T>& rhs)
		{
			return false;
		}
	};
}


