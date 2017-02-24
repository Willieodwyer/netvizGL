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
  GtkWidget *window;
  GtkWidget *button_box;

  GtkWidget *openFileButton;
  GtkWidget *dialog;
  GtkWidget *exportAsButton;

  GtkWidget *fruchterman, *simpleForce, *multiLevel, *box;
  GtkWidget *refreshButton,*entry;

  GtkWidget *separator1,*separator2,*separator3;

  GtkWidget *deleteNodeButton;
  GtkWidget *deleteEdgeButton;

  GtkWidget *colourNodeLabel;
  GtkWidget *distanceCentralityButton;
  GtkWidget *degreeCentralityButton;
  GtkColorChooser *colourNodeButton;

  GtkWidget *colourEdgeButton;

  GtkWidget *filterButton;
  GtkWidget *textNodeLabel;

  GtkWidget *textNodeEntry;

  GtkWidget *exitButton;

  static void activate(GtkApplication *app, gpointer user_data);

 public:
  Widget();
  virtual ~Widget();
  static Widget *Ins();
  static void toggleView();
  static void openFile();
  static void saveFile();
  static void quitNetviz();
  static void updateColour();
  static void updateNodeDetails();
  static void textChanged();
  static void refresh();
  enum AlgorithmSelection { FR, SMPL, MLT };
  enum SaveAsFileType { ADJACENCY, EDGELIST, PNG, SVG };
  static int getAlgorithm();
  double redColour;
  double blueColour;
  double greenColour;
  char *textNodeText;
  static void degreeC();
  static void distanceC();
  static void colourChanged();
  GtkWidget *textEdgeLabel;
  GtkWidget *textEdgeEntry;
  char *textEdgeText;
  static void edgeTextChanged();
};

#endif //NETVIZGL_BUTTONS_H
