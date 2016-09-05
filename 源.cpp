#include"tl\String.h"
#include"tl\mpl.h"
#include"tl\Vector.h"
#include<iostream>
int main()
{
	wl::String s;
	wl::Vector<int> v(10,5);
	wl::Vector<int>::iterator i (v.begin());
	v.erase(i);
	std::cout << v.size() << std::endl;
	system("pause");
	return 0;
}