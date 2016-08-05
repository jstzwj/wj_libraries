#ifndef TYPES
#define TYPES
#include<cctype>
#include<cstdint>
namespace wl
{
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


	typedef int32_t wint;

	//Typedef pointer here, which can be casted to integer.
	#if defined x64
	typedef wint32_t Pint;
	#endif
	#if ! defined x64
	typedef wint64_t Pint;
	#endif


	//Decide use unicode char or ascii char
	#ifdef _UNICODE
	typedef wchar_t Char;
	#endif // _UNICODE

	#ifndef _UNICODE
	typedef char Char;
	#endif // _ASCII



}





#endif // !TYPES
