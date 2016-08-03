#pragma once
#include<cstdint>
#include<map>
#include<vector>
#include<list>

#ifdef _WIN64 || __x86_64 || __LP64__
typedef int64_t pointer;
#endif

#ifndef _WIN64 || __x86_64 || __LP64__
typedef int32_t pointer;
#endif // !_WIN32

#define ptoi(X) reinterpret_cast<pointer>(X)
#define itop(X) reinterpret_cast<T *>(X)


class RawPtr
{
public:
	pointer p;
	int size;
	int *refnum;
public:
	RawPtr()
	{
		p = 0;
		size = 0;
		refnum = nullptr;
	}
	RawPtr(pointer _p,int _size,int * ref)
	{
		p = _p;
		size = _size;
		refnum = ref;
	}
	bool operator<(const RawPtr& rhs)
	{
		return p < rhs.p;
	}
	bool isMine(pointer from)
	{
		if (p <= from&&from < p + size)
			return true;
		else
			return false;
	}
};
class PtrNode
{
public:
	PtrNode()
		:ptr (nullptr),prev (nullptr) ,next (nullptr) ,deleteFlag (true) ,root (false)
	{}
	PtrNode(RawPtr * _ptr,PtrNode *_prev,PtrNode *_next,bool _deleteFlag,bool _root)
		:ptr(_ptr),prev(_prev),next(_next),deleteFlag(_deleteFlag),root(_root)
	{}
	RawPtr * ptr;
	PtrNode *prev;
	PtrNode *next;
	bool deleteFlag;
	bool root;
};
class GcGlobal
{
public:
	static int capacity;
	static int capacityLimit;
public:
	static std::list<PtrNode> allptr;
	static void addPtr( RawPtr & ptr);

	static void gc();
};




template<class T>
class ptr:public RawPtr
{
public:
	ptr();
	ptr(const ptr<T>& rhs);
	ptr(T *rhs);
	ptr<T> & operator=(const ptr<T>&rhs);
	bool operator==(const ptr<T>& rhs);
	T * operator->()
	{
		return itop(p);
	}
	T & operator*()
	{
		return *itop(p);
	}
	~ptr();
public:
	void release();
	
};

template<class T>
ptr<T>::ptr()
	:RawPtr()
{
	p = 0;
	size = sizeof(T);
	refnum = nullptr;
}

template<class T>
ptr<T>::ptr(const ptr<T>& rhs)
{

	p = rhs.p;
	size = sizeof(T);
	refnum = rhs.refnum;
	++*refnum;
	GcGlobal::addPtr(*this);

}

template<class T>
ptr<T>::ptr(T * rhs)
	:RawPtr()
{
	p = ptoi(rhs);
	size = sizeof(T);
	refnum = new int(1);
	GcGlobal::addPtr(*this);
	//记录空间增长
	GcGlobal::capacity += size;
	if (GcGlobal::capacity>=GcGlobal::capacityLimit)
	{
		GcGlobal::gc();
	}
}

template<class T>
ptr<T>& ptr<T>::operator=(const ptr<T>& rhs)
{
	if (&rhs != this)
	{
		p = rhs.p;
		size = sizeof(T);
		refnum = rhs.refnum;
		++*refnum;
		GcGlobal::addPtr(*this);
	}
	return *this;
}

template<class T>
bool ptr<T>::operator==(const ptr<T>& rhs)
{
	return p == rhs.p;
}

template<class T>
ptr<T>::~ptr()
{
	release();

}

template<class T>
void ptr<T>::release()
{
	if (refnum != nullptr)
	{
		if (*refnum == 1)
		{
			delete refnum;
			delete itop(p);
			//记录空间减少
			GcGlobal::capacity -= size;
		}
		else
		{
			--*refnum;
		}
	}
	//删除指针
	std::list<PtrNode>::iterator i;
	for (i = GcGlobal::allptr.begin(); i != GcGlobal::allptr.end(); ++i)
	{
		if (i->ptr == this)
		{
			GcGlobal::allptr.erase(i);
			break;
		}
	}
}


