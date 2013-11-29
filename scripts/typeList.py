"#define TYPELIST_arg( A, Aarg-1, Aarg  ) TypeList< A1, TYPELIST_(arg-1)( A2, A3 ) >" 

toMake = 21

print "#define TYPELIST_1( A1 ) TypeList< A1, NullType >"
for i in range( 2, toMake ):
    out = "#define TYPELIST_" + str(i) + "( A1"
    for j in range( 2, i+1 ):
        out = out + ", A%s" % ( j )
    out = out + ") \\\n\tTypeList< A1, TYPELIST_%s( A2" % ( i-1 )
    for j in range( 3, i+1 ):
        out = out + ", A%s" % ( j )
    out = out + " ) >"
    print out
