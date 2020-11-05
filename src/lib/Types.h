#ifndef VAR_H
    #define VAR_H

	#include <string>

    #define true 1
    #define false 0

    #define KB 1024
    #define MB 1024*KB
    #define GB 1024*MB

    typedef unsigned long long int uint64;
    typedef unsigned int uint32;
    typedef unsigned short uint16;
    typedef unsigned char uint8;
    typedef long long int int64;
    typedef int int32;
    typedef short int16;
    typedef char int8;

    typedef std::string String;

	#include "Type48.h"


	#include "Memory.h"

	#ifndef NULL
    	#define NULL 0
	#endif
#endif
