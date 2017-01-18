//
// Created by werl on 20/12/16.
//

#ifndef NETVIZGL_BUTTONS_H
#define NETVIZGL_BUTTONS_H

#include <gtk/gtk.h>

class Widget {
  GtkApplication *app;
  static Widget *instance;
  bool visible;

  GtkWidget *openFileButton;
  GtkWidget *dialog;
  GtkWidget *algorithmButton;
  GtkWidget *exitButton;
  GtkWidget *separator;
  GtkWidget *deleteNodeButton;
  GtkWidget *deleteEdgeButton;
  GtkColorChooser *colourNodeButton;
  GtkWidget *colourEdgeButton;
  GtkWidget *filterButton;
  GtkWidget *runButton;
  GtkWidget *button_box;
  GtkWidget *colourNodeLabel;


  GtkWidget *window;
  static void activate(GtkApplication *app, gpointer user_data);
 public:

  Widget();

  virtual ~Widget();

  static Widget *Instance();
  static void toggleView();
  static void openFile();
  static void quitNetviz();
  static void updateColour();
  double redColour;
  double blueColour;
  double greenColour;
};

#endif //NETVIZGL_BUTTONS_H
