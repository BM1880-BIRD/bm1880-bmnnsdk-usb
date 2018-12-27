/*
 * Copyright (C) Bitmain Technologies Inc.
 * All Rights Reserved.
 */
#ifndef _DEBUG_H_
#define _DEBUG_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <execinfo.h>
#include <stdio.h>
#include <stdlib.h>

static inline void print_trace(void)
{
  void *array[10];
  size_t i;

  size_t size = backtrace (array, 10);
  char **strings = backtrace_symbols (array, size);

  printf ("Obtained %lu stack frames.\n", size);

  for (i = 0; i < size; i++)
    printf ("%s\n", strings[i]);

  free (strings);
}

static inline void hang(int ret)
{
  exit(ret);
}

#define ASSERT(_cond)                                   \
  do {                                                  \
    if (!(_cond)) {                                     \
      printf("ASSERT %s: %d: %s: %s\n",                 \
             __FILE__, __LINE__, __func__, #_cond);     \
      print_trace();                                    \
      fflush(stdout);                                   \
      hang(-1);                                         \
    }                                                   \
  } while(0)

#ifdef DEBUG_BMNT
#define BMNT_DBG(fmt, ...)         printf("BMNT_INFO: " fmt, ##__VA_ARGS__)
#else
#define BMNT_DBG(fmt, ...)
#endif

#define BMNT_INFO(fmt, ...)         printf("BMNT_INFO: " fmt, ##__VA_ARGS__)

#define LINE_DBG()                 printf("LINE_DBG: %s %d\n", __func__, __LINE__);

#ifdef __cplusplus
}
#endif

#endif /* _DEBUG_H_ */
