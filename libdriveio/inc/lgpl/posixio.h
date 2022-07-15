/*
    libDriveIo - MMC drive interrogation library

    Copyright (C) 2007-2022 GuinpinSoft inc <libdriveio@makemkv.com>

    This library is free software; you can redistribute it and/or
    modify it under the terms of the GNU Lesser General Public
    License as published by the Free Software Foundation; either
    version 2.1 of the License, or (at your option) any later version.

    This library is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
    Lesser General Public License for more details.

    You should have received a copy of the GNU Lesser General Public
    License along with this library; if not, write to the Free Software
    Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA

*/
#ifndef LGPL_POSIXIO_H_INCLUDED
#define LGPL_POSIXIO_H_INCLUDED

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <stdio.h>

#if defined(_WIN32)

#include <io.h>
#include <process.h>

#define lseek64 _lseeki64
#define lseek   _lseek
#define O_LARGEFILE 0

#define open        _open
#define close       _close
#define read        _read
#define unlink      _unlink
#define write       _write
#define fileno      _fileno
#define dup         _dup
#define stat64      _stat64
#define fstat64     _fstat64

#ifndef S_IFBLK
#define	S_IFBLK 0060000	/* Block device.  */
#endif
#ifndef S_IFLNK
#define	S_IFLNK 0120000	/* Symbolic link.  */
#endif
#ifndef S_IFSOCK
#define	S_IFSOCK 0140000	/* Socket.  */
#endif

#ifndef STDIN_FILENO
#define	STDIN_FILENO	0
#define	STDOUT_FILENO	1
#define	STDERR_FILENO	2
#endif

#ifdef __cplusplus
extern "C" {
#endif

int     open_utf8(const char * _Filename, int _Openflag, int _PermissionMode);
int     stat64_utf8(const char * _Name, struct stat64 * _Stat);
FILE*   fopen_utf8(const char * _Filename, const char * _Mode);
int     unlink_utf8(const char * _Filename);
int     rmdir_utf8(const char * _Path);
int     mkdir_utf8(const char * _Path,unsigned int _Mode);
int     rename_utf8(const char * _OldPath, const char * _NewPath);
int     pread64(int fd,void* buf,size_t count,uint64_t offset);
int     pwrite64(int fd,const void* buf,size_t count,uint64_t offset);
int     ftruncate64(int fd,uint64_t offset);
int     fsync(int fd);

#ifdef __cplusplus
};
#endif

#elif defined(_darwin_)

#include <sys/param.h>
#include <sys/mount.h>

#ifndef _DARWIN_FEATURE_64_BIT_INODE
#error "_DARWIN_FEATURE_64_BIT_INODE not defined"
#endif

#undef  stat64
#define stat64 stat

#define O_LARGEFILE 0
#define O_BINARY    0
#define lseek64     lseek
#define pread64     pread
#define pwrite64    pwrite
#define ftruncate64 ftruncate

#define open_utf8   open
#define stat64_utf8 stat
#define lstat64_utf8 lstat
#define fstat64     fstat
#define fopen_utf8  fopen
#define unlink_utf8 unlink
#define rmdir_utf8  rmdir
#define mkdir_utf8  mkdir
#define rename_utf8 rename

#elif defined(_linux_)

#define O_BINARY 0

#define open_utf8   open
#define stat64_utf8 stat64
#define lstat64_utf8 lstat64
#define fopen_utf8  fopen
#define unlink_utf8 unlink
#define rmdir_utf8  rmdir
#define mkdir_utf8  mkdir
#define rename_utf8 rename

#endif

#endif // LGPL_POSIXIO_H_INCLUDED

