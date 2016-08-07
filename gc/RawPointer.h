#pragma once
namespace wl
{
	template <class T>
	class RawPointer
	{
	private:
		T * ptr;
	public:
		//Initialize a null pointer
		RawPointer();
		RawPointer(T & ptr);
		RawPointer(const RawPointer<T>& ptr);
		T operater->();
		virtual ~RawPointer();
	};
}


