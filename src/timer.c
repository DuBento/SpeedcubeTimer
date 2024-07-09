/**
 * @file timer.c
 * @author DuBento (github.com/DuBento)
 * @brief Simple timer implementation to be displayed
 * @version 0.1
 * @date 2022-01-16
 *
 * Chose to use Gtimer for more precision;
 * Timeout used to display new time;
 */

#include "timer.h"

#include <glib.h>
#include <gtk/gtk.h>

#include "speedcubetimer-window.h"

static GTimer* timer = NULL;
/* Elapsed Time in 1/100 ths of second */
// static double elapsedTime = 0;

typedef struct _TimerCallbackUserData {
  ResponseCallbackType responseCallback;
  SpeedcubetimerWindow* win;
} TimerCallbackUserData;

void updateTimerLabel(Time);
void updateTimerLabelFinal(Time);

static gboolean timerCallback(gpointer userData) {
  Time time;
  gdouble elapsed;
  TimerCallbackUserData* userDataStruct = (TimerCallbackUserData*)userData;
  SpeedcubetimerWindow* win = userDataStruct->win;
  bool timerRunning = win->timer_running;

  if (timer) {
    elapsed = g_timer_elapsed(timer, NULL);

    time.min = elapsed / 60;
    time.secs = (int)elapsed % 60;
    time.msecs = (int)(elapsed * 100) % 100;
  }

  if (timerRunning) {
    (userDataStruct->responseCallback)(time, win);
    return G_SOURCE_CONTINUE;
  } else {
    (userDataStruct->responseCallback)(time, win);
    g_timer_destroy(timer);
    /* Stop timeout timer */
    return G_SOURCE_REMOVE;
  }
}

static void startTimer(ResponseCallbackType responseCallback,
                       SpeedcubetimerWindow* win) {
  TimerCallbackUserData* userData;

  /* Timer starts */
  timer = g_timer_new();
  win->timer_running = TRUE;

  userData = g_new(TimerCallbackUserData, 1);
  userData->responseCallback = responseCallback;
  userData->win = win;

  // TimerCallbackUserData userData = {responseCallback, win};

  /* Callback every 100ms */
  g_timeout_add(100, timerCallback, userData);
}

static void stopTimer(SpeedcubetimerWindow* win) {
  g_timer_stop(timer);
  win->timer_running = FALSE;
}

void toggleTimer(ResponseCallbackType responseCallback,
                 SpeedcubetimerWindow* win) {
  !(win->timer_running) ? startTimer(responseCallback, win) : stopTimer(win);
}