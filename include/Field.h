#ifndef FIELD_H_CHRIS_HOGE
#define FIELD_H_CHRIS_HOGE

template < class T, class H >
typename H::template Rebind<T>::Result& Field( H& obj )
{
    return obj;
}

template < class T, class H >
const typename H::template Rebind<T>::Result& Field( const H& obj )
{
    return obj;
}


/*
#include "Type2Type.h"

template < class H, typename R >
inline R& FieldHelper( H& obj, Type2Type<R>, Int2Type<0> )
{
    typename H::LeftBase& subobj = obj;
    return subobj;
}

template < class H, typename R, int i >
inline R& FieldHelper( H& obj, Type2Type<R> tt, Int2Type<i> )
{
    typename H::RightBase& subobj = obj;
    return FieldHelper( subobj, tt, Int2Type<i-1>() );
}


*/

#endif
// FIELD_H_CHRIS_HOGE
