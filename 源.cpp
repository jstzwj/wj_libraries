#include"tl\String.h"
#include"tl\mpl.h"
#include"tl\Vector.h"
#include<iostream>
int main()
{
	wl::String s;
	wl::VectorBase<int> v(10,5);
	wl::VectorBase<int>::iterator i (v.begin());
	v.erase(i);
	std::cout << v.size() << std::endl;
	system("pause");
	return 0;
}