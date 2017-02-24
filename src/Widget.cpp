//
// Created by werl on 20/12/16.
//

#include "../inc/Widget.h"
#include "../inc/GLWindow.h"
#include "../inc/Command/RefreshGraph.h"
#include "../inc/Centrality/DistanceCentrality.h"
#include "../inc/Centrality/DegreeCentrality.h"
#include "../inc/Command/SaveGraph.h"

Widget *Widget::instance = NULL;

Widget *Widget::Ins() {
  if (!instance)   // Only allow one instance of class to be generated.
    instance = new Widget();
  return instance;
}

Widget::Widget() {
  visible = true;
  app = gtk_application_new("org.gtk.Netviz", G_APPLICATION_FLAGS_NONE);
  g_signal_connect(app, "activate", G_CALLBACK(activate), this);
  g_application_run(G_APPLICATION(app), 0, 0);
  g_object_unref(app);
}

Widget::~Widget() {
}

void Widget::activate(GtkApplication *app, gpointer user_data) {
  Widget::Ins()->window = gtk_application_window_new(app);
  gtk_window_set_title(GTK_WINDOW (Widget::Ins()->window), "Toolbox");
  gtk_window_set_default_size(GTK_WINDOW (Widget::Ins()->window), 197, 200);
  gtk_window_move(GTK_WINDOW (Widget::Ins()->window), 270, 152);
  g_signal_connect ((Widget::Ins()->window), "delete-event", G_CALLBACK(toggleView), Widget::Ins());

  Widget::Ins()->button_box = gtk_button_box_new(GTK_ORIENTATION_VERTICAL);
  gtk_container_add(GTK_CONTAINER (Widget::Ins()->window), Widget::Ins()->button_box);

  //File Dialog button
  Widget::Ins()->openFileButton = gtk_button_new_with_label("Open File");
  g_signal_connect (Widget::Ins()->openFileButton, "clicked", G_CALLBACK(openFile), Widget::Ins());

  //Export as
  Widget::Ins()->exportAsButton = gtk_button_new_with_label("Export As");
  g_signal_connect (Widget::Ins()->exportAsButton, "clicked", G_CALLBACK(saveFile), Widget::Ins());

  //Algorithm Radio Buttons
  Widget::Ins()->box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 2);
  gtk_box_set_homogeneous(GTK_BOX (Widget::Ins()->box), TRUE);
  Widget::Ins()->fruchterman = gtk_radio_button_new_with_label_from_widget(NULL,
                                                                           "Fruchterman Reingold");
  Widget::Ins()->simpleForce =
      gtk_radio_button_new_with_label_from_widget(GTK_RADIO_BUTTON (Widget::Ins()->fruchterman),
                                                  "Simple Force Directed");
  Widget::Ins()->multiLevel = gtk_radio_button_new_with_label_from_widget(GTK_RADIO_BUTTON (Widget::Ins()->simpleForce),
                                                                          "Multi Level");
  // Pack them into a box, then show all the widgets
  gtk_box_pack_start(GTK_BOX (Widget::Ins()->box), Widget::Ins()->fruchterman, TRUE, TRUE, 2);
  gtk_box_pack_start(GTK_BOX (Widget::Ins()->box), Widget::Ins()->simpleForce, TRUE, TRUE, 2);
  gtk_box_pack_start(GTK_BOX (Widget::Ins()->box), Widget::Ins()->multiLevel, TRUE, TRUE, 2);
  gtk_container_add(GTK_CONTAINER (Widget::Ins()->window), Widget::Ins()->box);

  //Refresh Buttons
  Widget::Ins()->refreshButton = gtk_button_new_with_label("Refresh Graph");
  g_signal_connect (Widget::Ins()->refreshButton, "clicked", G_CALLBACK(refresh), Widget::Ins());

  // Exit button
  Widget::Ins()->exitButton = gtk_button_new_with_label("Exit");
  g_signal_connect (Widget::Ins()->exitButton, "clicked", G_CALLBACK(quitNetviz), Widget::Ins());

  // Separator
  Widget::Ins()->separator1 = gtk_separator_new(GTK_ORIENTATION_HORIZONTAL);
  Widget::Ins()->separator2 = gtk_separator_new(GTK_ORIENTATION_HORIZONTAL);
  Widget::Ins()->separator3 = gtk_separator_new(GTK_ORIENTATION_HORIZONTAL);

  // Colour Node
  Widget::Ins()->colourNodeLabel = gtk_label_new("Colouration: ");
  // Centrality
  Widget::Ins()->distanceCentralityButton = gtk_button_new_with_label("Distance Centrality");
  g_signal_connect (Widget::Ins()->distanceCentralityButton, "clicked", G_CALLBACK(distanceC), Widget::Ins());

  Widget::Ins()->degreeCentralityButton = gtk_button_new_with_label("Degree Centrality");
  g_signal_connect (Widget::Ins()->degreeCentralityButton, "clicked", G_CALLBACK(degreeC), Widget::Ins());

  GdkRGBA *def = new GdkRGBA;
  def->red = 1;
  def->green = 1;
  def->blue = 1;
  Widget::Ins()->colourNodeButton = (GtkColorChooser *) gtk_color_button_new_with_rgba(def);
  gtk_color_button_set_title((GtkColorButton *) Widget::Ins()->colourNodeButton, "Nodes");
  g_signal_connect (Widget::Ins()->colourNodeButton, "color-set", G_CALLBACK(colourChanged), Widget::Ins());
  delete (def);

  // Text Node
  Widget::Ins()->textNodeLabel = gtk_label_new("Add text to node");
  Widget::Ins()->textNodeEntry = gtk_entry_new();
  gtk_entry_set_text((GtkEntry *) Widget::Ins()->textNodeEntry, "Enter node text here");
  gtk_entry_set_max_length((GtkEntry *) Widget::Ins()->textNodeEntry, 64);
  g_signal_connect (Widget::Ins()->textNodeEntry, "changed", G_CALLBACK(textChanged), Widget::Ins());
  Widget::Ins()->textNodeText = (char *) gtk_entry_get_text((GtkEntry *) Widget::Ins()->textNodeEntry);

  // Text Edge
  Widget::Ins()->textEdgeLabel = gtk_label_new("Add text to Edge");
  Widget::Ins()->textEdgeEntry = gtk_entry_new();
  gtk_entry_set_text((GtkEntry *) Widget::Ins()->textEdgeEntry, "Enter Edge text here");
  gtk_entry_set_max_length((GtkEntry *) Widget::Ins()->textEdgeEntry, 64);
  g_signal_connect (Widget::Ins()->textEdgeEntry, "changed", G_CALLBACK(edgeTextChanged), Widget::Ins());
  Widget::Ins()->textEdgeText = (char *) gtk_entry_get_text((GtkEntry *) Widget::Ins()->textEdgeEntry);

  gtk_container_add(GTK_CONTAINER (Widget::Ins()->button_box), Widget::Ins()->openFileButton);
  gtk_container_add(GTK_CONTAINER (Widget::Ins()->button_box), Widget::Ins()->exportAsButton);
  gtk_container_add(GTK_CONTAINER (Widget::Ins()->button_box), Widget::Ins()->separator1);
  gtk_container_add(GTK_CONTAINER (Widget::Ins()->button_box), Widget::Ins()->box);
  gtk_container_add(GTK_CONTAINER (Widget::Ins()->button_box), Widget::Ins()->refreshButton);
  gtk_container_add(GTK_CONTAINER (Widget::Ins()->button_box), Widget::Ins()->separator2);

  //TODO
//  gtk_container_add(GTK_CONTAINER (Widget::Ins()->button_box), Widget::Ins()->deleteNodeButton);
//  gtk_container_add(GTK_CONTAINER (Widget::Ins()->button_box), Widget::Ins()->deleteEdgeButton);

  gtk_container_add(GTK_CONTAINER (Widget::Ins()->button_box), Widget::Ins()->colourNodeLabel);
  gtk_container_add(GTK_CONTAINER (Widget::Ins()->button_box), Widget::Ins()->degreeCentralityButton);
  gtk_container_add(GTK_CONTAINER (Widget::Ins()->button_box), Widget::Ins()->distanceCentralityButton);
  gtk_container_add(GTK_CONTAINER (Widget::Ins()->button_box), (GtkWidget *) Widget::Ins()->colourNodeButton);

  gtk_container_add(GTK_CONTAINER (Widget::Ins()->button_box), Widget::Ins()->textNodeLabel);
  gtk_container_add(GTK_CONTAINER (Widget::Ins()->button_box), Widget::Ins()->textNodeEntry);

  gtk_container_add(GTK_CONTAINER (Widget::Ins()->button_box), Widget::Ins()->textEdgeLabel);
  gtk_container_add(GTK_CONTAINER (Widget::Ins()->button_box), Widget::Ins()->textEdgeEntry);

//  gtk_container_add(GTK_CONTAINER (Widget::Ins()->button_box), Widget::Ins()->colourEdgeButton);
//  gtk_container_add(GTK_CONTAINER (Widget::Ins()->button_box), Widget::Ins()->filterButton);
  gtk_container_add(GTK_CONTAINER (Widget::Ins()->button_box), Widget::Ins()->separator3);
  gtk_container_add(GTK_CONTAINER (Widget::Ins()->button_box), Widget::Ins()->exitButton);

  gtk_widget_show_all(Widget::Ins()->window);

}

void Widget::distanceC() {
  DistanceCentrality c;
  c.calcApply(GLWindow::Ins()->graph);
}

void Widget::degreeC() {
  DegreeCentrality c;
  c.calcApply(GLWindow::Ins()->graph);
}

void Widget::openFile() {
  GtkFileChooserAction action = GTK_FILE_CHOOSER_ACTION_OPEN;
  gint res;

  Widget::Ins()->dialog =
      gtk_file_chooser_dialog_new("Open File",
                                  NULL,
                                  action,
                                  ("_Cancel"),
                                  GTK_RESPONSE_CANCEL,
                                  ("_Open"),
                                  GTK_RESPONSE_ACCEPT,
                                  NULL);

  res = gtk_dialog_run(GTK_DIALOG (Widget::Ins()->dialog));

  if (res == GTK_RESPONSE_ACCEPT) {
    GtkFileChooser *chooser = GTK_FILE_CHOOSER (Widget::Ins()->dialog);
    GLWindow::Ins()->graphFilePath = gtk_file_chooser_get_filename(chooser);
    //fprintf(stderr, "%s", gtk_file_chooser_get_filename(chooser));
  }

  if (res == GTK_RESPONSE_CANCEL) {
    gtk_widget_destroy(Widget::Ins()->dialog);
    return;
  }

  gtk_widget_destroy(Widget::Ins()->dialog);

  if (GLWindow::Ins()->graphFilePath)
    GLWindow::Ins()->loadGraph->execute();
}

void Widget::saveFile() {
  GtkWidget *dialog;
  GtkFileChooser *chooser;
  GtkFileChooserAction action = GTK_FILE_CHOOSER_ACTION_SAVE;
  SaveAsFileType res;

  dialog = gtk_file_chooser_dialog_new("Save File",
                                       NULL,
                                       action,
                                       ("_Cancel"),
                                       GTK_RESPONSE_CANCEL,
                                       ("_Save as Adjacency Matrix"),
                                       ADJACENCY,
                                       ("_Save as Edge List"),
                                       EDGELIST,
                                       ("_Save as PNG"),
                                       PNG,
                                       ("_Save as SVG"),
                                       SVG,
                                       NULL);
  chooser = GTK_FILE_CHOOSER (dialog);

  gtk_file_chooser_set_do_overwrite_confirmation(chooser, TRUE);
  gtk_file_chooser_set_current_name(chooser, "Untitled");

  res = (SaveAsFileType) gtk_dialog_run(GTK_DIALOG (dialog));

  char *filefile;
  filefile = gtk_file_chooser_get_filename(chooser);

  SaveGraph s(GLWindow::Ins(), res, filefile);
  s.execute();

  gtk_widget_destroy(dialog);
}

void Widget::updateColour() {
  GdkRGBA *colour = new GdkRGBA;
  gtk_color_chooser_get_rgba(Widget::Ins()->colourNodeButton, colour);

  Widget::Ins()->redColour = colour->red;
  Widget::Ins()->blueColour = colour->blue;
  Widget::Ins()->greenColour = colour->green;
}

void Widget::updateNodeDetails() {
  GdkRGBA *colour = new GdkRGBA;
  colour->alpha = 1;
  colour->red = Widget::Ins()->redColour;
  colour->green = Widget::Ins()->greenColour;
  colour->blue = Widget::Ins()->blueColour;

  gtk_color_chooser_set_rgba(Widget::Ins()->colourNodeButton, colour);

  gtk_entry_set_text((GtkEntry *) Widget::Ins()->textNodeEntry, Widget::Ins()->textNodeText);
}

void Widget::toggleView() {
  if (Widget::Ins()->visible) {
    Widget::Ins()->visible = false;
    gtk_widget_hide(Widget::Ins()->window);
  } else {
    gtk_widget_show(Widget::Ins()->window);
    Widget::Ins()->visible = true;
  }
}

void Widget::quitNetviz() {
  GLWindow::Ins()->quit();
}

void Widget::textChanged() {
  Widget::Ins()->textNodeText = (char *) gtk_entry_get_text((GtkEntry *) Widget::Ins()->textNodeEntry);
  if (GLWindow::Ins()->selectedNode)
    GLWindow::Ins()->selectedNode->setText(Widget::Ins()->textNodeText);
}

void Widget::edgeTextChanged() {
//  Widget::Ins()->textEdgeText = (char *) gtk_entry_get_text((GtkEntry *) Widget::Ins()->textEdgeEntry);
//  if (GLWindow::Ins()->selectedNode)
//    GLWindow::Ins()->selectedNode->setText(Widget::Ins()->textNodeText);
}

void Widget::colourChanged() {
  GdkRGBA *colour = new GdkRGBA;
  gtk_color_chooser_get_rgba(Widget::Ins()->colourNodeButton, colour);

  Widget::Ins()->redColour = colour->red;
  Widget::Ins()->blueColour = colour->blue;
  Widget::Ins()->greenColour = colour->green;

  if (GLWindow::Ins()->selectedNode)
    GLWindow::Ins()->selectedNode->setColour(colour->red, colour->green, colour->blue);
}

void Widget::refresh() {
  RefreshGraph c(GLWindow::Ins());
  c.execute();
}

int Widget::getAlgorithm() {
  if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(Widget::Ins()->fruchterman)) == TRUE)
    return FR;
  if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(Widget::Ins()->simpleForce)) == TRUE)
    return SMPL;
  if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(Widget::Ins()->multiLevel)) == TRUE)
    return MLT;
}



