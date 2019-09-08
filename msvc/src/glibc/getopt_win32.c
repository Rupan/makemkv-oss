/*
    Written by GuinpinSoft inc <oss@makemkv.com>

    This file is hereby placed into public domain,
    no copyright is claimed.

*/
#include "getopt.h"

extern int __cdecl getopt_get_optind()
{
    return optind;
}

extern void __cdecl getopt_set_optind(int value)
{
    optind = value;
}

extern const char* __cdecl getopt_get_optarg()
{
    return optarg;
}

