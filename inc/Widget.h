//
// Created by werl on 20/12/16.
//

#ifndef NETVIZGL_BUTTONS_H
#define NETVIZGL_BUTTONS_H

#include <gtk/gtk.h>

class Widget {
  static Widget *instance;
  bool visible;

  GtkWidget *openFileButton;
  GtkWidget *dialog;
  GtkWidget *algorithmButton;
  GtkWidget *exitButton;
  GtkWidget *separator;
  GtkWidget *deleteNodeButton;
  GtkWidget *deleteEdgeButton;
  GtkWidget *colourNodeButton;
  GtkWidget *colourEdgeButton;
  GtkWidget *filterButton;
  GtkWidget *runButton;
  GtkWidget *button_box;
  GtkWidget *window;


  static void activate(GtkApplication *app, gpointer user_data);
 public:
  Widget();

  virtual ~Widget();

  static Widget *Instance();

  static void quitEvent();
  static void toggleView();
  static void openFile();
  static void quitNetviz();
};

#endif //NETVIZGL_BUTTONS_H
