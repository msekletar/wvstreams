/*
 * Worldvisions Weaver Software:
 *   Copyright (C) 1997-2001 Net Integration Technologies, Inc.
 *
 * Test program for base64 functions...
 */

#include "base64.h"
#include <stdio.h>

int main( int argc, char ** argv )
/********************************/
{
    char * str;

    if( argc > 1 )
        str = argv[1];
    else
        str = "<insert secret message here>";

    char * enc = base64_encode( str );
    printf( "before:  %s\n"
            "encoded: %s\n"
            "decoded: %s\n", str, enc, base64_decode( enc ) );
    return( 0 );
}
