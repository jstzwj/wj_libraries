#include "RawPointer.h"
#include<new>
namespace wl
{
	/// <summary>
	/// Initializes a new instance of the class.A nullptr.
	/// </summary>
	template <class T>
	RawPointer::RawPointer()
	{
	}

	/// <summary>
	/// Copy from another pointer.
	/// </summary>
	/// <param name="ptr">The other PTR.</param>
	template<class T>
	RawPointer<T>::RawPointer(T & ptr)
	{
	}

	template<class T>
	RawPointer<T>::RawPointer(const RawPointer<T>& ptr)
	{
	}

	template <class T>
	RawPointer::~RawPointer()
	{
	}


}

