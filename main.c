#include <gtk/gtk.h>
#include <stdio.h>

#include "timer.h"

GtkWidget *labTime;

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
  GtkWidget *win;

  win = gtk_application_window_new(GTK_APPLICATION(app));
  gtk_window_set_title(GTK_WINDOW(win), "Speedcube Timer");
  gtk_window_set_default_size(GTK_WINDOW(win), 400, 300);

  /* Label */
  labTime = gtk_label_new("0.0");
  gtk_window_set_child(GTK_WINDOW(win), labTime);

  /* Keyboard event */
  GtkEventController *keyController = gtk_event_controller_key_new();
  g_signal_connect(G_OBJECT(keyController), "key-pressed",
                   G_CALLBACK(keypressHandler), NULL);
  gtk_widget_add_controller(win, keyController);

  gtk_widget_show(win);
}

int main(int argc, char **argv) {
  GtkApplication *app;
  int stat;

  app = gtk_application_new("speedcube.gtk.timer", G_APPLICATION_FLAGS_NONE);
  g_signal_connect(app, "activate", G_CALLBACK(appActivate), NULL);
  stat = g_application_run(G_APPLICATION(app), argc, argv);
  g_object_unref(app);
  return stat;
}
