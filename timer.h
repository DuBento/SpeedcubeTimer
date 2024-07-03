#ifndef __TIMER_H__
#define __TIMER_H__

#include <glib.h>

typedef struct time_stuct {
  int msecs;
  int secs;
  int min;
} Time;

gboolean toggleTimer();

#endif