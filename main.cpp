#include"tl\String.h"
#include"tl\mpl.h"
#include"tl/Vector.h"
#include<vector>
#include<iostream>
#include<memory>
#include<utility>
int main()
{
	wl::String s;
    std::vector<int> vec;
    wl::Vector<int> myvec;

    vec.push_back(1);
    myvec.push_back(1);
    std::cout<<myvec.back();

	return 0;
}
