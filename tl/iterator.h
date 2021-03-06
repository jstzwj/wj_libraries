#pragma once
#ifndef ITERATOR
#define ITERATOR


#include"..\types.h"

namespace wl
{
	//Category of iterator
	struct input_iterator_tag { };
	struct output_iterator_tag { };
	struct forward_iterator_tag
		: public input_iterator_tag { };
	struct bidirectional_iterator_tag
		: public forward_iterator_tag { };
	struct random_access_iterator_tag
		: public bidirectional_iterator_tag { };
	//Base class of iterator
	template<class Category, class T, class Distance = ptrdiff, class Pointer = T*, class Reference = T&>
	struct iterator
	{
		typedef Category iterator_category;
		typedef T value_type;
		typedef Distance difference_type;
		typedef Pointer pointer;
		typedef Reference reference;
	};
}
#include"traits.h"

#endif // !ITERATOR


