/*
    Written by GuinpinSoft inc <oss@makemkv.com>

    This file is hereby placed into public domain,
    no copyright is claimed.

*/
#ifndef LGPL_GETOPT_H_INCLUDED
#define LGPL_GETOPT_H_INCLUDED

#ifdef _WIN32_WINNT
#include <src/glibc/getopt.h>

#ifdef __cplusplus
extern "C" {
#endif

extern int __cdecl getopt_get_optind();
extern void __cdecl getopt_set_optind(int value);
extern const char* __cdecl getopt_get_optarg();

#ifdef __cplusplus
};
#endif

#else

#include <getopt.h>

#define getopt_get_optind() (optind)
#define getopt_get_optarg() (optarg)
#define getopt_set_optind(v) {optind=(v);}

#endif

#endif // LGPL_GETOPT_H_INCLUDED
