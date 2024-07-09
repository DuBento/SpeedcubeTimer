#pragma once

#include <glib.h>

typedef struct {
  int msecs;
  int secs;
  int min;
} Time;

#include "speedcubetimer-window.h"

typedef void (*ResponseCallbackType)(Time time, SpeedcubetimerWindow* win);

void toggleTimer(ResponseCallbackType responseCallback,
                 SpeedcubetimerWindow* win);
