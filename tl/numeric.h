#pragma once
#ifndef NUMERIC
#define NUMERIC


//Accumulate the objects in the range
template<class InputIterator,class T>
T accumulate(InputIterator first, InputIterator last, T init)
{
	while (first!=last)
	{
		init = init + *first;
		++first;
	}
	return init;
}
//Accumulate by use a functional
template<class InputIterator, class T,class BinaryOperation>
T accumulate(InputIterator first, InputIterator last, T init, BinaryOperation binary_op)
{
	while (first != last)
	{
		init = binary_op(init,*first);
		++first;
	}
	return init;
}
//Adjacent differance
// Input sequence: x0,x1,...,x(n-1), accumulate the subtraction sequence x1-x0,x2-x1,...,x(n-1)-x(n-2).
template<class InputIterator,class OutputIterator>
OutputIterator adjacent_difference(InputIterator first, InputIterator last, OutputIterator result)
{
	if (first==last)
	{
		return result;
	}
	*result = *first;

	T value = *first;
	while (++first!=last)
	{
		T tmp = *first;
		*++result = tmp - value;
		value = tmp;
	}
	return ++result;
}
template < class InputIterator, class OutputIterator, class BinaryOperation >
OutputIterator adjacent_difference(InputIterator first, InputIterator last, OutputIterator result, BinaryOperation binary_op)
{
	if (first == last)
	{
		return result;
	}
	*result = *first;

	T value = *first;
	while (++first != last)
	{
		T tmp = *first;
		*++result = binary_op(tmp,value);
		value = tmp;
	}
	return ++result;
}

//Inner Product
template<class InputIterator1, class InputIterator2,class T>
T inner_product(InputIterator1 first1,InputIterator1 last1,InputIterator2 first2,T init)
{
	while (first1!=last1)
	{
		init = init + *first1 * *first2;
		++first1;
		++first2;
	}
}
template<class InputIterator1, class InputIterator2, class T,class BinaryOperation1,class BinaryOperation2>
T inner_product(InputIterator1 first1, InputIterator1 last1, InputIterator2 first2, T init, BinaryOperation1 plus, BinaryOperation2 mult)
{
	while (first1 != last1)
	{
		init = plus(init, mult(*first1 , *first2) );
		++first1;
		++first2;
	}
}
//partial sum
template<class InputIterator,class OutputIterator>
OutputIterator partial_sum(InputIterator first,InputIterator last,OutputIterator result)
{
	if (first==last)
	{
		return result;
	}
	*result = *first;
	//get the value of object,which is pointed by iterator.
	iterator_traits<InputIterator>::value_type  value = *first;
	++first;
	while (first!=last)
	{
		value = value + *first;
		++result;
		*result = value;
		++first;
	}
	return ++result;
}
template<class InputIterator, class OutputIterator,class BinaryOperation>
OutputIterator partial_sum(InputIterator first, InputIterator last, OutputIterator result, BinaryOperation binary_op)
{
	if (first == last)
	{
		return result;
	}
	*result = *first;
	//get the value of object,which is pointed by iterator.
	iterator_traits<InputIterator>::value_type  value = *first;
	++first;
	while (first != last)
	{
		value = binary_op(value , *first);
		++result;
		*result = value;
		++first;
	}
	return ++result;
}
//TODO
//power

//itoa



#endif // !NUMERIC
