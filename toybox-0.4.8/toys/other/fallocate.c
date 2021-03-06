/* fallocate.c - Preallocate space to a file
 *
 * Copyright 2013 Felix Janda <felix.janda@posteo.de>
 *
 * No standard

USE_FALLOCATE(NEWTOY(fallocate, ">1l#|", TOYFLAG_USR|TOYFLAG_BIN))

config FALLOCATE
  bool "fallocate"
  default n
  help
    usage: fallocate [-l size] file

    Tell the filesystem to allocate space for a file.
*/

#define FOR_fallocate
#include "toys.h"

GLOBALS(
  long size;
)

void fallocate_main(void)
{
  int fd = xcreate(*toys.optargs, O_RDWR | O_CREAT, 0644);
  if (posix_fallocate(fd, 0, TT.size)) error_exit("Not enough space");
  if (CFG_TOYBOX_FREE) close(fd);
}
