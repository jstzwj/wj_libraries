#pragma once
#ifndef CONSTUCT
#define CONSTRUCT
#include<new>
namespace wl
{
	//placement new call constructor
	template<class T,class U>
	inline void construct(T *p, const U & value)
	{
		new(p)T(value);
	}
	//call deconstructor
	template<class T>
	inline void construct(T *p)
	{
		p->~T();
	}





}



#endif // !CONSTUCT
