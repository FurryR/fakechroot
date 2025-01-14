/*
    libfakechroot -- fake chroot environment
    Copyright (c) 2010-2020 Piotr Roszatycki <dexter@debian.org>

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

#ifdef HAVE_STATX

#define _GNU_SOURCE
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

#include "libfakechroot.h"

wrapper(statx, int,
        (int dirfd, const char* pathname, int flags, unsigned int mask,
         struct statx* statxbuf)) {
  char fakechroot_abspath[FAKECHROOT_PATH_MAX];
  char fakechroot_buf[FAKECHROOT_PATH_MAX];
  debug("statx(%d, \"%s\", %d, %u, &statxbuf)", dirfd, pathname, flags, mask);
  expand_chroot_path_at(dirfd, pathname);
  int ret = nextcall(statx)(dirfd, pathname, flags, mask, statxbuf);
  statxbuf->stx_uid = 0;
  statxbuf->stx_gid = 0;
  return ret;
}

#else
typedef int empty_translation_unit;
#endif
