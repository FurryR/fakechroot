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

#include <config.h>
#include <fcntl.h>
#include <grp.h>
#include <stddef.h>
#include <sys/stat.h>
#include <unistd.h>

#include "libfakechroot.h"

wrapper(getuid, uid_t, ()) {
  debug("getuid()");
  return 0;
}
wrapper(geteuid, uid_t, ()) {
  debug("geteuid()");
  return 0;
}
wrapper(getresuid, int, (uid_t * a, uid_t *b, uid_t *c)) {
  debug("getresuid(%p, %p, %p)", a, b, c);
  *a = 0;
  *b = 0;
  *c = 0;
  return 0;
}
wrapper(getgid, gid_t, ()) {
  debug("getgid()");
  return 0;
}
wrapper(getegid, gid_t, ()) {
  debug("getegid()");
  return 0;
}
wrapper(getresgid, int, (gid_t * a, gid_t *b, gid_t *c)) {
  debug("getresgid(%p, %p, %p)", a, b, c);
  *a = 0;
  *b = 0;
  *c = 0;
  return 0;
}
wrapper(setuid, int, (uid_t a)) {
  debug("setuid(%u)", a);
  if (a < 0) return -1;
  return 0;
}
wrapper(seteuid, int, (uid_t a)) {
  debug("seteuid(%u)", a);
  if (a < 0) return -1;
  return 0;
}
wrapper(setreuid, int, (uid_t a, uid_t b)) {
  debug("setreuid(%u, %u)", a, b);
  if (a < 0 || b < 0) return -1;
  return 0;
}
wrapper(setresuid, int, (uid_t a, uid_t b, uid_t c)) {
  debug("setresuid(%u, %u, %u)", a, b, c);
  if (a < 0 || b < 0 || c < 0) return -1;
  return 0;
}
wrapper(setgid, int, (gid_t a)) {
  debug("setgid(%u)", a);
  if (a < 0) return -1;
  return 0;
}
wrapper(setegid, int, (gid_t a)) {
  debug("setegid(%u)", a);
  if (a < 0) return -1;
  return 0;
}
wrapper(setregid, int, (gid_t a, gid_t b)) {
  debug("setregid(%u, %u)", a, b);
  if (a < 0 || b < 0) return -1;
  return 0;
}
wrapper(setresgid, int, (gid_t a, gid_t b, gid_t c)) {
  debug("setresgid(%u, %u, %u)", a, b, c);
  if (a < 0 || b < 0 || c < 0) return -1;
  return 0;
}
wrapper(getgroups, int, (int size, gid_t list[])) {
  debug("setresuid(%d, %p)", size, list);
  if (size <= 0)
    return 1;
  else
    list[0] = 0;
  return 1;
}
wrapper(setgroups, int, (size_t __n, const __gid_t *__groups)) {
  debug("setgroups(%u, %p)", __n, __groups);
  return 0;
}
wrapper(fchown, int, (int fd, uid_t owner, gid_t group)) {
  debug("fchown(\"%d\", %d, %d)", fd, owner, group);
  owner = nextcall(getuid)();
  group = nextcall(getgid)();
  return nextcall(fchown)(fd, owner, group);
}