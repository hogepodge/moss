#ifndef GENCLASS_H_CHRIS_HOGE
#define GENCLASS_H_CHRIS_HOGE

#include "TypeList.h"
#include "Reflector.h"
#include "Holder.h"
#include <string>

template < class TList, template <class> class Unit = Holder >
class GenClass;

template < class T1, class T2, template <class> class Unit >
class GenClass< TypeList< T1, T2 >, Unit >
:   public GenClass< T1, Unit >,
    public GenClass< T2, Unit >
{
public:
    typedef TypeList< T1, T2 > TList;
    typedef GenClass< T1, Unit > LeftBase;
    typedef GenClass< T2, Unit > RightBase;

    typedef GenClass< TypeList< T1, T2 >, Unit > This;
    typedef Reflector< This > Reflector;

    template <typename T> struct Rebind
    {
        typedef Unit<T> Result;
    };
};

template < class AtomicType, template <class> class Unit >
class GenClass : public Unit< AtomicType >
{
    typedef Unit< AtomicType > LeftBase;
    template <typename T> struct Rebind
    {
        typedef Unit<T> Result;
    };
};

template < template <class> class Unit >
class GenClass< NullType, Unit >
{
    template <typename T> struct Rebind
    {
        typedef Unit<T> Result;
    };
};

template <class T, int Size> 
struct MossBase 
{
    enum { SIZE=Size }; 
    typedef T TYPE;
    T value[Size];
};

template <class T>
struct MossBase< T, 1 >
{
    enum { SIZE=1 }; 
    typedef T TYPE;
    T value;
};


#define MOSS_BASE( type, name, size ) \
    struct name : public MossBase< type, size > {};

#define MOSS_TYPE_1( typeName, type1, name1 ) \
    MOSS_BASE( type1, name1 ) \
    typedef GenClass< \
        TYPELIST_1( name1 ), \
        Holder > typeName; 

#define MOSS_TYPE_2( typeName, type1, name1, type2, name2 ) \
    MOSS_BASE( type1, name1 ) \
    MOSS_BASE( type2, name2 ) \
    typedef GenClass< \
        TYPELIST_2( name1, name2 ), \
        Holder > typeName;

#define MOSS_TYPE_3( typeName, type1, name1, size1, type2, name2, size2, type3, name3, size3 ) \
    MOSS_BASE( type1, name1, size1) \
    MOSS_BASE( type2, name2, size2 ) \
    MOSS_BASE( type3, name3, size3 ) \
    struct typeName : public GenClass< \
        TYPELIST_3( name1, name2, name3 ), \
        Holder > {};

#endif
// GENCLASS_H_CHRIS_HOGE
