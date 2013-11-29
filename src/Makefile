# linux gcc/mpi
INCLUDE=-I../include -I/usr/local/include
GNU_CFLAGS=-Wno-long-double 
GNU_CXX=mpic++ $(GNU_CFLAGS)
CXX=$(GNU_CXX)

# aix 
#CXX=xlC -I/opt/osshpc/mpich-1.2.5/32/ch_shmem/include -L/opt/osshpc/mpich-1.2.5/32/ch_shmem/lib -lmpich
#LIB=-lmpich

# icpc
#CXX=icpc
#INCLUDE=-I../include -I/opt/mpich/intel/include 
#LIB=-L/opt/mpich/intel/lib -lmpich

# gcc/mpich
#CXX=g++
#INCLUDE=-I../include -I/opt/mpich/gnu/include 
#LIB=-L/opt/mpich/gnu/lib -lmpich

all:
	$(CXX) $(CFLAGS) $(INCLUDE) main.cpp $(LIB) -o main 
