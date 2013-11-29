#include <moss.h>

#include <iostream>

struct handMade
{
    double y;
    double x[2];
    double z;
};

using namespace std;

// construct the serializable object
struct pos_x : public MossBase< double, 1 > {};
struct pos_y : public MossBase< double, 2 > {};
struct pos_z : public MossBase< double, 1 > {};

typedef GenClass 
<
    TypeListGen::Y::
        Add< pos_x >::Y::
        Add< pos_y >::Y::
        Add< pos_z >::Y::
        TypeList
> Three;


//typedef Reflector<Three> RThree;
// end construction

int main( int argc, char* argv[] )
{
    MPI_Init( &argc, &argv );

    GenClass 
    <
        TypeListGen::Y::
            Add< pos_x >::Y::
            Add< pos_y >::Y::
            Add< pos_z >::Y::
            TypeList,
        Holder
    > foo;

    // Three foo;

    Field< pos_x >( foo ).value = 10;
    Field< pos_y >( foo ).value[0] = 20;
    Field< pos_y >( foo ).value[1] = 40;
    Field< pos_z >( foo ).value = 30;
    cout 
        << Field< pos_x >( foo ).value << ": "
        << Field< pos_y >( foo ).value[0] << ": "
        << Field< pos_y >( foo ).value[1] << ": "
        << Field< pos_z >( foo ).value << ": "
        << endl;
    cout << "Moss:" << sizeof( Three ) <<
        " Handmade:" << sizeof( handMade ) << endl;

    cout << Three::Reflector::fields() << endl;

    cout << MPI_INT << "*" << endl;

    Three::Reflector::commit();


    MPI_Finalize();
}
