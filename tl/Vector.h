#pragma once

#ifndef VECTOR
#define VECTOR
#include<initializer_list>
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
		//constructor
        ConstVectorIterator(typename ConstVectorIterator<T>::pointer otherPtr) : p(otherPtr) {}
		ConstVectorIterator() {}
		ConstVectorIterator(const iterator& otherIterator) : p(otherIterator.p) {}

		// equal and inequal operator
		bool operator==(const ConstVectorIterator& other) const { return p == other.p; }
		bool operator!=(const ConstVectorIterator& other) const { return p != other.p; }

		//Pointer operator
        typename ConstVectorIterator<T>::reference operator*() const { return *p; }
        typename ConstVectorIterator<T>::pointer operator->() const { return &*p; }

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
        ConstVectorIterator& operator+=(typename ConstVectorIterator<T>::difference_type n) { p += n; return p; }
        ConstVectorIterator& operator-=(typename ConstVectorIterator<T>::difference_type n) { p -= n; return p; }

		//assignment
        ConstVectorIterator & operator=(const ConstVectorIterator & other) { p = other.p; return *this; }

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
        VectorIterator(typename VectorIterator<T>::pointer otherPtr) : p(otherPtr) {}
		VectorIterator() {}
		VectorIterator(const iterator& otherIterator) : p(otherIterator.p) {}
		// equal and inequal operator
		bool operator==(const VectorIterator& other) const { return p == other.p; }
		bool operator!=(const VectorIterator& other) const { return p != other.p; }
		//Pointer operator
        typename VectorIterator<T>::reference operator*() const { return *p; }
        typename VectorIterator<T>::pointer operator->() const { return &*p; }

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
        VectorIterator& operator+=(typename VectorIterator<T>::difference_type n) { p += n; return p; }
        VectorIterator& operator-=(typename VectorIterator<T>::difference_type n) { p -= n; return p; }

		//assignment
        VectorIterator & operator=(const VectorIterator & other) { p = other.p; return *this; }

		//compare
		bool operator>(const VectorIterator & other)const { return p > other.p; }
		bool operator<(const VectorIterator & other)const { return p < other.p; }
		bool operator>=(const VectorIterator & other)const { return p >= other.p; }
		bool operator<=(const VectorIterator & other)const { return p <= other.p; }


	};


	/// <summary>
	/// The base of vecor , which is used to allocate the memory of vector.
	/// </summary>
    template<class T, class Allocator = wl::allocator<T> >
    class VectorBase:public Allocator
	{
	public:
        typedef VectorBase<T, Allocator> MyType;
        typedef Allocator allocator_type;
        typedef T * pointer;

        Allocator& get_allocator_aux() noexcept
            { return *static_cast<Allocator*>(&this); }

        const Allocator& get_allocator_aux() const noexcept
            { return *static_cast<const Allocator*>(&this); }

        allocator_type get_allocator() const noexcept
            { return allocator_type(get_allocator()); }

    protected:
		pointer start;
		pointer finish;
		pointer end_of_storage;

	public:

        VectorBase() : VectorBase( Allocator() ){}

        explicit VectorBase( const Allocator& alloc ) noexcept
            :Allocator(alloc),start(), finish(), end_of_storage() {}

        VectorBase(Allocator&& alloc) noexcept
        : Allocator(wl::move(alloc)), start(), finish(), end_of_storage()
        { }

        explicit VectorBase( wl::size_t count, const Allocator& alloc = Allocator() )
            :Allocator(alloc)
        {
            create_storage(count);
        }

        VectorBase( const VectorBase& other )
        {
            start = allocate(other.size());
            finish = uninitialized_copy(other.start, other.finish, start);
            end_of_storage = finish;
        }


        void swap_data(VectorBase & other) noexcept
        {
          wl::swap(start, other.start);
          wl::swap(finish, other.finish);
          wl::swap(end_of_storage, other.end_of_storage);
        }


        VectorBase(VectorBase&& other) noexcept
            : Allocator(std::move(other.get_allocator()))
        { this->swap_data(other); }

        VectorBase(VectorBase&& other, const allocator_type& alloc)
            : Allocator(alloc)
        {
            if (other.get_allocator() == alloc)
            {
              this->swap_data(other);
            }
            else
            {
                size_t __n = other.finish -other.start;
                create_storage(__n);
            }
        }



		VectorBase(long n, const T &value)
		{
            start = this->allocate(n);
			uninitialized_fill_n(start,n,value);
			finish = start + n;
			end_of_storage = finish;
		}
		~VectorBase()
		{
			destroy(start,finish);
            this->deallocate(start,end_of_storage-start);
		}
    private:
      void create_storage(wl::size_t n)
      {
        this->start = this->allocate(n);
        this->finish = this->start;
        this->end_of_storage = this->start + n;
      }

	};





    template<class T,class Allocator=wl::allocator<T> >
    class Vector:public VectorBase<T,Allocator>
	{
	public:
        typedef Vector<T, Allocator> MyType;
        typedef Allocator allocator_type;

		typedef VectorIterator<T> iterator;
        typedef ConstVectorIterator<T> const_iterator;


        using value_type=T;
        //using allocator_type=Allocator;
        using size_type=wsize;
        using difference_type=std::ptrdiff_t;
        using reference=value_type&;
        using const_reference=const value_type&;
        //using pointer=std::allocator_traits<Allocator>::pointer;
        //using const_pointer=std::allocator_traits<Allocator>::const_pointer;
        //using iterator=VectorIterator<T>;
        //using const_iterator=ConstVectorIterator<T>;
        //using reverse_iterator=std::reverse_iterator<iterator>;
        //using const_reverse_iterator=std::reverse_iterator<const_iterator>;

        explicit Vector( const Allocator& alloc ):VectorBase<T,Allocator>(alloc){}
        Vector() : Vector( Allocator() ){}


        Vector( size_type count,const T& value,const Allocator& alloc = Allocator())
            :VectorBase<T,Allocator>(count,value,alloc){}

        explicit Vector( size_type count, const Allocator& alloc = Allocator() )
            :VectorBase<T,Allocator>(count,alloc){}

        template< class InputIt >
        Vector( InputIt first, InputIt last,const Allocator& alloc = Allocator() )
            :VectorBase<T,Allocator>(first,last,alloc){}

        Vector( const Vector& other ):VectorBase<T,Allocator>(other){}
        Vector( const Vector& other, const Allocator& alloc )
            :VectorBase<T,Allocator>(other,alloc){}
        Vector( Vector&& other ){}
        Vector( Vector&& other, const Allocator& alloc ){}
        Vector( std::initializer_list<T> init,const Allocator& alloc = Allocator() ){}

    public:
        iterator begin() { return this->start; }
        iterator end() { return this->finish; }
        const_iterator cbegin() { return this->start; }
        const_iterator cend() { return this->finish; }

        reference front() { return *(this->start); }
        reference back() { return *(this->finish-1); }

        size_type size() { return this->finish - this->start; }
        size_type capacity() { return this->end_of_storage - this->start; }

        bool empty() { return this->start == this->finish; }
        reference operator[] (size_type n) { return *(this->start + n); }

        iterator erase(iterator n)
        {
            if (n<this->start||n>=this->finish)
            {
                throw "Erase error:Iterator is out of range.";
            }
            if (n+1!=end())
            {
                destroy(n);
                copy(n+1,iterator(this->finish),n);
            }
            else
            {
                destroy(n);
            }
            --this->finish;
            return n;
        }
        void push_back(const T& value )
        {
            if(this->finish==this->end_of_storage)
            {
                T * new_start;
                if(size()==0)
                {
                    new_start=this->allocate(1);
                }
                else
                {
                    new_start=this->allocate(2*size());
                }
                copy(this->start,this->end_of_storage,new_start);
                this->deallocate(this->start,size());
                this->end_of_storage=new_start+(this->end_of_storage-this->start);
                this->finish=new_start+(this->finish-this->start);
                this->start=new_start;
            }
            *(this->finish)=value;
            ++(this->finish);
        }


	};






}
#endif // !VECTOR
