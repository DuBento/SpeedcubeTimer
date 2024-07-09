/* speedcubetimer-window.h
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

#pragma once

#include <adwaita.h>
#include <gtk/gtk.h>

struct _SpeedcubetimerWindow {
  AdwApplicationWindow parent_instance;

  /* Template widgets */
  GtkLabel *label_stopwatch;

  /* Logic */
  bool timer_running;
};

G_BEGIN_DECLS

#define SPEEDCUBETIMER_TYPE_WINDOW (speedcubetimer_window_get_type())

G_DECLARE_FINAL_TYPE(SpeedcubetimerWindow, speedcubetimer_window,
                     SPEEDCUBETIMER, WINDOW, AdwApplicationWindow)

G_END_DECLS

#include "timer.h"

void speedcubetimer_window__update_timer_label(Time time,
                                               SpeedcubetimerWindow *self);