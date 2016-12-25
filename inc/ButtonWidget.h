//
// Created by werl on 20/12/16.
//

#ifndef NETVIZGL_BUTTONS_H
#define NETVIZGL_BUTTONS_H

#include <gtk/gtk.h>

class ButtonWidget {
  static ButtonWidget *instance;

  GtkWidget *window;
  GtkWidget *button;
  GtkWidget *button_box;

  static void activate(GtkApplication *app, gpointer user_data);

 public:
  ButtonWidget();

  static ButtonWidget *Instance();

  static void doSomething();
};

#endif //NETVIZGL_BUTTONS_H
