/* speedcubetimer-window.c
 *
 * Copyright 2024 Unknown
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * 	http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include "speedcubetimer-window.h"

#include "config.h"
#include "timer.h"

G_DEFINE_FINAL_TYPE(SpeedcubetimerWindow, speedcubetimer_window,
                    ADW_TYPE_APPLICATION_WINDOW)

void speedcubetimer_window__update_timer_label(Time time,
                                               SpeedcubetimerWindow *self) {
  char buffer[16];
  if (self->timer_running) time.msecs = time.msecs / 10;

  if (time.min != 0)
    snprintf(buffer, sizeof(buffer), "%d:%d.%d", time.min, time.secs,
             time.msecs);
  else
    snprintf(buffer, sizeof(buffer), "%d.%d", time.secs, time.msecs);

  gtk_label_set_text(self->label_stopwatch, buffer);
}

static gboolean speedcubetimer_window__keypress_handler(
    GtkEventControllerKey *event_controller, guint keyval, guint keycode,
    GdkModifierType state, SpeedcubetimerWindow *self) {
  if (keyval == GDK_KEY_space) {
    toggleTimer(speedcubetimer_window__update_timer_label, self);
    return TRUE;
  }
  return FALSE;
}

static void speedcubetimer_window_class_init(SpeedcubetimerWindowClass *klass) {
  GtkWidgetClass *widget_class = GTK_WIDGET_CLASS(klass);

  gtk_widget_class_set_template_from_resource(
      widget_class, "/gtk/timer/speedcube/speedcubetimer-window.ui");
  gtk_widget_class_bind_template_child(widget_class, SpeedcubetimerWindow,
                                       label_stopwatch);
}

static void speedcubetimer_window_init(SpeedcubetimerWindow *self) {
  GtkEventController *keyController;

  gtk_widget_init_template(GTK_WIDGET(self));

  /* Keyboard event */
  keyController = gtk_event_controller_key_new();
  g_signal_connect(G_OBJECT(keyController), "key-pressed",
                   G_CALLBACK(speedcubetimer_window__keypress_handler), self);
  gtk_widget_add_controller(GTK_WIDGET(self), keyController);
}
