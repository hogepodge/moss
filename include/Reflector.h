#ifndef REFLECTOR_H_CHRIS_HOGE
#define REFLECTOR_H_CHRIS_HOGE

#include <mpi.h>
#include "TypeInfer.h"
#include "TypeList.h"
#include "Field.h"

#include <iostream>

template <class T, int I>
struct MpiLengthAt
{
    static void length( int* l )
    {
        *l = T::Head::SIZE;
        MpiLengthAt< typename T::Tail, I-1 >::length( l + 1 );
    }
};

template <class H, class T>
struct MpiLengthAt< TypeList< H, T >, 1 >
{
    static void length( int* l )
    {
        *l = H::SIZE;
    }
};

template <class T, int I>
struct MpiTypeAt
{
    static void type( MPI_Datatype* t )
    {
        MPI_Datatype x;
        x = TypeInfer< typename T::Head::TYPE >();
        *t = x;
        MpiTypeAt< typename T::Tail, I-1 >::type( t + 1 );
    }
};


template < class H, class T >
struct MpiTypeAt< TypeList< H, T >, 1 >
{
    static void type( MPI_Datatype* t )
    {
        MPI_Datatype x;
        x = TypeInfer< typename H::TYPE >();
        *t = x;
    }
};

template < class H, class T, int I >
struct MpiTypeAt< TypeList< H, T >, I >
{
    static void type( MPI_Datatype* t )
    {
        MPI_Datatype x;
        x = TypeInfer< typename H::TYPE >();
        *t = x;
        MpiTypeAt< T, I-1>::type( t + 1 );
    }
};

template <class G, class L, int I>
struct MpiDispAt
{
    static void type( G* p, MPI_Aint* t )
    {
        MPI_Aint x = (MPI_Aint)(&(Field< typename L::Head >( *p ).value));
        *t = (x - (MPI_Aint)(p));
        MpiDispAt< G, typename L::Tail, I-1>::type( p, t + 1 );
     }
};

template < class G, class H, class T, int I >
struct MpiDispAt< G, TypeList< H, T >, I >
{
    static void type( G* p, MPI_Aint* t )
    {
        MPI_Aint x = (MPI_Aint)(&(Field< H >( *p ).value));
        *t = (x - (MPI_Aint)(p));
        MpiDispAt< G, T, I-1>::type( p, t + 1 );
    }
};

template < class G, class H, class T >
struct MpiDispAt< G, TypeList<H, T> , 1 >
{
    static void type( G* p, MPI_Aint* t )
    {
        MPI_Aint x = (MPI_Aint)(&(Field< H >( *p ).value));
        *t = (x - (MPI_Aint)(p));
    }
};


template < class G >
class Reflector
{
public:
    Reflector();

    static void commit();
    static void free();

    static int fields();

    static MPI_Datatype* MpiType();

private:



    typedef MpiTypeAt< typename G::TList, Length< typename G::TList>::value > TypeFunctor;
    typedef MpiDispAt< G, typename G::TList, Length< typename G::TList>::value > DispFunctor;
    typedef MpiLengthAt< typename G::TList, Length< typename G::TList>::value > LengthFunctor;

};

template <class G>
MPI_Datatype* Reflector<G>::MpiType()
{
    static MPI_Datatype type;
    return &type;
}

template <class G>
int
Reflector<G>::fields()
{
    return Length< typename G::TList>::value;
}

template < class G >
void
Reflector<G>::commit()
{
    G sample;

    MPI_Datatype types[ Length<typename G::TList>::value ];
    MPI_Aint disps[ Length<typename G::TList>::value ];
    int lengths[ Length<typename G::TList>::value ];

    // TODO make thread safe
    TypeFunctor::type( types );
    DispFunctor::type( &sample, disps );
    LengthFunctor::length( lengths );

    // TODO MPI error checking
    MPI_Type_struct( Length< typename G::TList>::value , lengths, disps, 
        types, MpiType() );
    MPI_Type_commit( MpiType() );
}

template < class G >
void
Reflector<G>::free()
{
    MPI_Type_free( &MpiType );
}


#endif
// REFLECTOR_H_CHRIS_HOGE
