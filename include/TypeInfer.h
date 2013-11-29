#ifndef TYPEINFER_H_CHRIS_HOGE
#define TYPEINFER_H_CHRIS_HOGE

#include "mpi.h"

template < class T >
MPI_Datatype TypeInfer()
{
    return T::MpiType;
}

template <>
MPI_Datatype TypeInfer<char>()
{
    return MPI_CHAR;
}


template <>
MPI_Datatype TypeInfer<signed char>()
{
    return MPI_CHAR;
}

template <>
MPI_Datatype TypeInfer<signed short int>()
{
    return MPI_SHORT;
}

template <>
MPI_Datatype TypeInfer<signed int>()
{
    return MPI_INT;
}

template <>
MPI_Datatype TypeInfer<signed long int>()
{
    return MPI_LONG;
}

template <>
MPI_Datatype TypeInfer<unsigned char>()
{
    return MPI_UNSIGNED_CHAR;
}

template <>
MPI_Datatype TypeInfer<unsigned short int>()
{
    return MPI_UNSIGNED_SHORT;
}

template <>
MPI_Datatype TypeInfer<unsigned int>()
{
    return MPI_UNSIGNED;
}

template <>
MPI_Datatype TypeInfer<unsigned long>()
{
    return MPI_UNSIGNED_LONG;
}

template <>
MPI_Datatype TypeInfer<float>()
{
    return MPI_FLOAT;
}

template <>
MPI_Datatype TypeInfer<double>()
{
    return MPI_DOUBLE;
}

template <>
MPI_Datatype TypeInfer<long double>()
{
    return MPI_LONG_DOUBLE;
}

#endif
// TYPEINFER_H_CHRIS_HOGE
