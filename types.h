#ifndef TYPES
#define TYPES
#include<cctype>
#include<cstdint>

namespace wl
{

	/*
	Define some basic types in this segment.
	integer
	pointer address
	unicode and ascii character

	*/

	//These defines were only tested in MSVS2015. More compiles will be supported later.
	//Test x64 system
	#if defined _WIN64 || __x86_64 || __LP64__
	#define x64
	#endif

	//Typedef some integer type here
	typedef int8_t wint8_t;
	typedef int16_t wint16_t;
	typedef int32_t wint32_t;
	typedef int64_t wint64_t;

	typedef uint8_t wuint8_t;
	typedef uint16_t wuint16_t;
	typedef uint32_t wuint32_t;
	typedef uint64_t wuint64_t;

	typedef int32_t wint;
	typedef uint32_t wuint;
	typedef wuint wsize;

	//Typedef pointer here, which can be casted to integer.
	#if defined x64
	typedef wint64_t Pint;
	#endif
	#if ! defined x64
	typedef wint32_t Pint;
	#endif

    using size_t=wl::wsize;
    using ptrdiff=Pint;


	//Decide use unicode char or ascii char
	#ifdef _UNICODE
	typedef wchar_t Char;
	#endif // _UNICODE

	#ifndef _UNICODE
	typedef char Char;
	#endif // _ASCII

	/*
	This segment is used to state some most basic utilities class.
	Object::=The base class of any classes(like java or Qt), signals will base on it.
	NonCopyable::=The classes derived from it may not be copied if derived classes do not override the copy construct function. 
	*/
	class NonCopyable
	{
	private:
		NonCopyable(const NonCopyable&) ;
		NonCopyable& operator=(const NonCopyable&) { return *this; } 
	public:
		NonCopyable() {}
	};

	class Object
	{
	public:
		Object() {}
		virtual ~Object() {}
	};


}





#endif // !TYPES
