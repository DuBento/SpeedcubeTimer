#include <gtk/gtk.h>
#include <stdio.h>

#include "timer.h"

GtkLabel *labTime;

void _updateTimerLabel(Time, gboolean);

void updateTimerLabel(Time time) { _updateTimerLabel(time, FALSE); }

void updateTimerLabelFinal(Time time) { _updateTimerLabel(time, TRUE); }

void _updateTimerLabel(Time time, gboolean bFinal) {
  char buffer[16];
  if (!bFinal) time.msecs = time.msecs / 10;

  if (time.min != 0)
    sprintf(buffer, "%d:%d.%d", time.min, time.secs, time.msecs);
  else
    sprintf(buffer, "%d.%d", time.secs, time.msecs);

  gtk_label_set_text(GTK_LABEL(labTime), buffer);
}

gboolean keypressHandler(GtkEventControllerKey *self, guint keyval,
                         guint keycode, GdkModifierType state,
                         gpointer user_data) {
  if (keyval == GDK_KEY_space) {
    toggleTimer();
    return TRUE;
  }
  return FALSE;
}

static void appActivate(GApplication *app, gpointer user_data) {
  GtkBuilder *build;
  GtkWidget *win;

  build = gtk_builder_new_from_resource("/speedcube/gtk/timer/sct.ui");
  win = GTK_WIDGET(gtk_builder_get_object(build, "win"));
  gtk_window_set_application(GTK_WINDOW(win), GTK_APPLICATION(app));

  /* Label */
  labTime = GTK_LABEL(gtk_builder_get_object(build, "stopwatchTime"));

  /* Keyboard event */
  GtkEventController *keyController = gtk_event_controller_key_new();
  g_signal_connect(G_OBJECT(keyController), "key-pressed",
                   G_CALLBACK(keypressHandler), NULL);
  gtk_widget_add_controller(win, keyController);

  gtk_widget_set_visible(GTK_WIDGET(win), TRUE);

  g_object_unref(build);
}

int main(int argc, char **argv) {
  GtkApplication *app;
  int status;

  app = gtk_application_new("speedcube.gtk.timer", G_APPLICATION_DEFAULT_FLAGS);
  g_signal_connect(app, "activate", G_CALLBACK(appActivate), NULL);
  status = g_application_run(G_APPLICATION(app), argc, argv);
  g_object_unref(app);
  return status;
}
