#ifndef TYPELIST_H_CHRIS_HOGE
#define TYPELIST_H_CHRIS_HOGE

#include "NullType.h"

template <class H, class T>
class TypeList
{
public:
    typedef H Head;
    typedef T Tail;
};

// Define length operation
template < class TList > class Length;

template <> class Length< NullType >
{
public:
    enum { value = 0 };
};

template < class H, class T >
class Length< TypeList< H, T> >
{
public:
    enum { value = 1 + Length<T>::value };
};


// Define indexed access
template <class TList, unsigned int index> class TypeAt;

template < class H, class T >
class TypeAt< TypeList< H, T >, 0 >
{
public:
    typedef H Result;
};

template < class H, class T, int i >
class TypeAt< TypeList< H, T >, i >
{
public:
    typedef typename TypeAt< T, i-1 >::Result Result;
};

///// BEGIN APPEND
template <class TList, class T> class Append
{
public:
    typedef TypeList< T, TList > Result;
};

template <> class Append< NullType, NullType >
{
public:
    typedef NullType Result;
};


template < class T >
class Append< NullType, T >
{
public:
    typedef TypeList< T, NullType > Result;
};

template < class Head, class Tail >
class Append< NullType, TypeList< Head, Tail> >
{
public:
    typedef TypeList< Head, Tail > Result;
};

template < class Head, class Tail, class T >
class Append< TypeList< Head, Tail >, T >
{
public:
    typedef TypeList< Head, typename Append< Tail, T >::Result > Result;
};

///// END APPEND

template < class Head, class Tail >
class TypeListGenHelper
{
public:
    typedef typename Append< typename Head::TypeList, Tail>::Result TypeList;
    typedef TypeListGenHelper< Head, Tail > Y;

    template < class Next >
    class Add : public TypeListGenHelper< TypeListGenHelper< Head, Tail >, Next >
    {
        typedef TypeListGenHelper< TypeListGenHelper< Head, Tail>, Next > X;
    };

};

class TypeListGenStart
{
public:
    typedef NullType TypeList;
};

class TypeListGen : public TypeListGenHelper< TypeListGenStart, NullType >
{
};


#define TYPELIST_1( A ) TypeList< A, NullType >
#define TYPELIST_2( A, B ) TypeList< A, TYPELIST_1( B ) >
#define TYPELIST_3( A, B, C ) TypeList< A, TYPELIST_2( B, C ) >

#endif
// TYPELIST_H_CHRIS_HOGE
