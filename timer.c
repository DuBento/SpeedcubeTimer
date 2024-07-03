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

static int bTimerRunning = FALSE;
static GTimer* timer = NULL;
/* Elapsed Time in 1/100 ths of second */
// static double elapsedTime = 0;

void updateTimerLabel(Time);
void updateTimerLabelFinal(Time);

static gboolean timerCallback(gpointer data) {
  Time time;
  gdouble elapsed;

  if (timer) {
    elapsed = g_timer_elapsed(timer, NULL);

    time.min = elapsed / 60;
    time.secs = (int)elapsed % 60;
    time.msecs = (int)(elapsed * 100) % 100;

    // g_print("%d, %d, %d\n", time.min, time.secs, time.msecs);
  }

  if (bTimerRunning) {
    updateTimerLabel(time);
    return G_SOURCE_CONTINUE;
  } else {
    updateTimerLabelFinal(time);
    g_timer_destroy(timer);
    /* Stop timeout timer */
    return G_SOURCE_REMOVE;
  }
}

void startTimer() {
  /* Timer starts */
  timer = g_timer_new();
  bTimerRunning = TRUE;

  /* Callback every 100ms */
  g_timeout_add(100, timerCallback, NULL);
}

void stopTimer() {
  g_timer_stop(timer);
  bTimerRunning = FALSE;
}

gboolean toggleTimer() {
  !bTimerRunning ? startTimer() : stopTimer();
  return bTimerRunning;
}