/*
 * File: paths.hh
 *
 * Copyright 2006-2009 Jorge Arellano Cid <jcid@dillo.org>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 */

#ifndef __PATHS_HH__
#define __PATHS_HH__

#define PATHS_RC_PREFS  "dillorc"
#define PATHS_RC_KEYS   "keysrc"
#define PATHS_RC_DOMAIN "domainrc"
#define PATHS_HSTS_PRELOAD "hsts_preload"
#define PATHS_BM "bm.txt"
#define BUFFERSIZE      4096
#define COPYMODE        0644

class Paths {
public:
   static void init(void);
   static void free(void);
   static char *getOldWorkingDir(void);
   static FILE *getPrefsFP(const char *rcFile);
   static void copy_file(char *, char*);
};

#endif /* __PATHS_HH__ */
