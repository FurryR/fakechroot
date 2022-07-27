/*
    libfakechroot -- fake chroot environment
    Copyright (c) 2010, 2013 Piotr Roszatycki <dexter@debian.org>

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

#ifndef __GETCWD_H
#define __GETCWD_H

#include <stddef.h>

#include "libfakechroot.h"

wrapper_proto(getuid, uid_t, ());
wrapper_proto(geteuid, uid_t, ());
wrapper_proto(getresuid, int, (uid_t *, uid_t *, uid_t *));
wrapper_proto(getgid, gid_t, ());
wrapper_proto(getegid, gid_t, ());

wrapper_proto(getresgid, int, (gid_t *, gid_t *, gid_t *));
wrapper_proto(setuid, int, (uid_t));
wrapper_proto(seteuid, int, (uid_t));
wrapper_proto(setreuid, int, (uid_t, uid_t));
wrapper_proto(setresuid, int, (uid_t, uid_t, uid_t));
wrapper_proto(setgid, int, (gid_t));
wrapper_proto(setegid, int, (gid_t));
wrapper_proto(setregid, int, (gid_t, gid_t));
wrapper_proto(setresgid, int, (gid_t, uid_t, uid_t));
wrapper_proto(getgroups, int, (int, gid_t[]));

#endif
