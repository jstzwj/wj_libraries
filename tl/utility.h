#ifndef UTILITY_H
#define UTILITY_H
#include"types.h"
#include"type_traits.h"
namespace wl
{
    //move
    template< class T >
    constexpr typename wl::remove_reference<T>::type && move( T&& t );
    //forward
    template< class T >
    constexpr T&& forward( typename wl::remove_reference<T>::type& t ) noexcept;

    template< class T >
    constexpr T&& forward( typename wl::remove_reference<T>::type&& t ) noexcept;
    //pair
    template<class T1,class T2> struct pair
    {
        using first_type=T1;
        using second_type=T2;

        first_type first;
        second_type second;
        //ctor
        /*EXPLICIT*/constexpr pair();
        /*EXPLICIT*/constexpr pair( const T1& x, const T2& y )
            :first(x),second(y){}
        template< class U1, class U2 >
        /*EXPLICIT*/ constexpr pair( U1&& x, U2&& y )
            :first(wl::move(x)),second(wl::move(y)){}
        template< class U1, class U2 >
        /*EXPLICIT*/ constexpr pair( const pair<U1, U2>& p )
            :first(p.first),second(p.second){}
        template< class U1, class U2 >
        /*EXPLICIT*/ constexpr pair(pair<U1, U2>&& p )
            : first(wl::forward<U1>(p.first)),
              second(wl::forward<U2>(p.second)) { }
        /*template< class... Args1, class... Args2 >
        pair( std::piecewise_construct_t,
              std::tuple<Args1...> first_args,
              std::tuple<Args2...> second_args );*/
        pair( const pair& p ) = default;
        pair( pair&& p ) = default;
    };
    //swap
    template< class T >
    inline void swap( T& a, T& b )
    {
        T tmp=a;
        a=b;
        b=tmp;
    }

    template< class T2, wl::size_t N >
    inline void swap( T2 (&a)[N], T2 (&b)[N])
    {
        for(wl::size_t i=0;i<N;++i)
        {
            wl::swap(a[i],b[i]);
        }
    }
}
#endif // UTILITY_H
