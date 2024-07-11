/* speedcubetimer-application.c
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

#include "speedcubetimer-application.h"

#include "config.h"
#include "speedcubetimer-window.h"

struct _SpeedcubetimerApplication {
  AdwApplication parent_instance;
};

G_DEFINE_FINAL_TYPE(SpeedcubetimerApplication, speedcubetimer_application,
                    ADW_TYPE_APPLICATION)

SpeedcubetimerApplication *speedcubetimer_application_new(
    const char *application_id, GApplicationFlags flags) {
  g_return_val_if_fail(application_id != NULL, NULL);

  return g_object_new(SPEEDCUBETIMER_TYPE_APPLICATION, "application-id",
                      application_id, "flags", flags, NULL);
}

static void load_css(void) {
  GtkCssProvider *provider = gtk_css_provider_new();
  GdkDisplay *display;

  gtk_css_provider_load_from_resource(provider,
                                      "/gtk/timer/speedcube/style.css");
  display = gdk_display_get_default();
  gtk_style_context_add_provider_for_display(
      display, GTK_STYLE_PROVIDER(provider),
      GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);
}

static void speedcubetimer_application_activate(GApplication *app) {
  GtkWindow *window;

  g_assert(SPEEDCUBETIMER_IS_APPLICATION(app));

  window = gtk_application_get_active_window(GTK_APPLICATION(app));

  if (window == NULL)
    window = g_object_new(SPEEDCUBETIMER_TYPE_WINDOW, "application", app, NULL);

  // load_css();

  gtk_window_present(window);
}

static void speedcubetimer_application_class_init(
    SpeedcubetimerApplicationClass *klass) {
  GApplicationClass *app_class = G_APPLICATION_CLASS(klass);

  app_class->activate = speedcubetimer_application_activate;
}

static void speedcubetimer_application_about_action(GSimpleAction *action,
                                                    GVariant *parameter,
                                                    gpointer user_data) {
  static const char *developers[] = {"Unknown", NULL};
  SpeedcubetimerApplication *self = user_data;
  GtkWindow *window = NULL;

  g_assert(SPEEDCUBETIMER_IS_APPLICATION(self));

  window = gtk_application_get_active_window(GTK_APPLICATION(self));

  adw_show_about_window(
      window, "application-name", "speedcubetimer", "application-icon",
      "gtk.timer.speedcube", "developer-name", "Unknown", "version", "0.1.0",
      "developers", developers, "copyright", "© 2024 Unknown", NULL);
}

static void speedcubetimer_application_quit_action(GSimpleAction *action,
                                                   GVariant *parameter,
                                                   gpointer user_data) {
  SpeedcubetimerApplication *self = user_data;

  g_assert(SPEEDCUBETIMER_IS_APPLICATION(self));

  g_application_quit(G_APPLICATION(self));
}

static const GActionEntry app_actions[] = {
    {"quit", speedcubetimer_application_quit_action},
    {"about", speedcubetimer_application_about_action},
};

static void speedcubetimer_application_init(SpeedcubetimerApplication *self) {
  g_action_map_add_action_entries(G_ACTION_MAP(self), app_actions,
                                  G_N_ELEMENTS(app_actions), self);
  gtk_application_set_accels_for_action(GTK_APPLICATION(self), "app.quit",
                                        (const char *[]){"<primary>q", NULL});
}
