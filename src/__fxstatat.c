/*
    libfakechroot -- fake chroot environment
    Copyright (c) 2010-2015 Piotr Roszatycki <dexter@debian.org>

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
    Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307  USA
*/

#include <config.h>

#ifdef HAVE___FXSTATAT

#define _ATFILE_SOURCE
#define _BSD_SOURCE
#define _DEFAULT_SOURCE
#include <limits.h>
#include <stdlib.h>
#include <sys/stat.h>

#include "libfakechroot.h"

wrapper(__fxstatat, int,
        (int ver, int dirfd, const char* pathname, struct stat* buf,
         int flags)) {
  char fakechroot_abspath[FAKECHROOT_PATH_MAX];
  char fakechroot_buf[FAKECHROOT_PATH_MAX];
  debug("__fxstatat(%d, %d, \"%s\", &buf, %d)", ver, dirfd, pathname, flags);
  expand_chroot_path_at(dirfd, pathname);
  int ret = nextcall(__fxstatat)(ver, dirfd, pathname, buf, flags);
  buf->st_uid = 0;
  buf->st_gid = 0;
  return ret;
}

#else
typedef int empty_translation_unit;
#endif
