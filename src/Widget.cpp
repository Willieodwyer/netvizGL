//
// Created by werl on 20/12/16.
//

#include "../inc/Widget.h"
#include "../inc/GLWindow.h"
#include "../inc/FileReader.h"
#include "../inc/Graphs/EdgeGraph.h"

Widget *Widget::instance = NULL;

Widget *Widget::Instance() {
  if (!instance)   // Only allow one instance of class to be generated.
    instance = new Widget();
  return instance;
}

Widget::Widget() {
  visible = true;

  GtkApplication *app;
  int status;
  app = gtk_application_new("org.gtk.example", G_APPLICATION_FLAGS_NONE);
  g_signal_connect (app, "activate", G_CALLBACK(activate), NULL);
  status = g_application_run(G_APPLICATION (app), 0, 0);
  g_object_unref(app);
}

Widget::~Widget() {
}

void Widget::activate(GtkApplication *app, gpointer user_data) {
  Widget::Instance()->window = gtk_application_window_new(app);
  gtk_window_set_title(GTK_WINDOW (Widget::Instance()->window), "Toolbox");
  gtk_window_set_default_size(GTK_WINDOW (Widget::Instance()->window), 197, 200);
  gtk_window_move(GTK_WINDOW (Widget::Instance()->window), 270, 152);

  Widget::Instance()->button_box = gtk_button_box_new(GTK_ORIENTATION_VERTICAL);
  gtk_container_add(GTK_CONTAINER (Widget::Instance()->window), Widget::Instance()->button_box);

  //File Dialog button
  Widget::Instance()->openFileButton = gtk_button_new_with_label("Open File");
  g_signal_connect (Widget::Instance()->openFileButton, "clicked", G_CALLBACK(openFile), NULL);

  //Algorithm select button
  Widget::Instance()->algorithmButton = gtk_combo_box_new();
  //g_signal_connect (Widget::Instance()->openFileButton, "clicked", G_CALLBACK(openFile), NULL);

  // Exit button
  Widget::Instance()->exitButton = gtk_button_new_with_label("Exit");
  g_signal_connect (Widget::Instance()->exitButton, "clicked", G_CALLBACK(quitNetviz), NULL);

  // Separator
  Widget::Instance()->separator = gtk_separator_new(GTK_ORIENTATION_HORIZONTAL);
  g_signal_connect ((Widget::Instance()->window), "delete-event", G_CALLBACK(toggleView), NULL);

  gtk_container_add(GTK_CONTAINER (Widget::Instance()->button_box), Widget::Instance()->openFileButton);
  gtk_container_add(GTK_CONTAINER (Widget::Instance()->button_box), Widget::Instance()->algorithmButton);
  gtk_container_add(GTK_CONTAINER (Widget::Instance()->button_box), Widget::Instance()->exitButton);
  gtk_container_add(GTK_CONTAINER (Widget::Instance()->button_box), Widget::Instance()->separator);

  //TODO
//  gtk_container_add(GTK_CONTAINER (Widget::Instance()->button_box), Widget::Instance()->deleteNodeButton);
//  gtk_container_add(GTK_CONTAINER (Widget::Instance()->button_box), Widget::Instance()->deleteEdgeButton);
//  gtk_container_add(GTK_CONTAINER (Widget::Instance()->button_box), Widget::Instance()->colourNodeButton);
//  gtk_container_add(GTK_CONTAINER (Widget::Instance()->button_box), Widget::Instance()->colourEdgeButton);
//  gtk_container_add(GTK_CONTAINER (Widget::Instance()->button_box), Widget::Instance()->filterButton);
//  gtk_container_add(GTK_CONTAINER (Widget::Instance()->button_box), Widget::Instance()->runButton);

  gtk_widget_show_all(Widget::Instance()->window);

}

void Widget::openFile() {
  GtkFileChooserAction action = GTK_FILE_CHOOSER_ACTION_OPEN;
  gint res;

  Widget::Instance()->dialog =
      gtk_file_chooser_dialog_new("Open File",
                                  NULL,
                                  action,
                                  ("_Cancel"),
                                  GTK_RESPONSE_CANCEL,
                                  ("_Open"),
                                  GTK_RESPONSE_ACCEPT,
                                  NULL);

  res = gtk_dialog_run(GTK_DIALOG (Widget::Instance()->dialog));
  if (res == GTK_RESPONSE_ACCEPT) {
    GtkFileChooser *chooser = GTK_FILE_CHOOSER (Widget::Instance()->dialog);
    GLWindow::Instance()->graphFilePath = gtk_file_chooser_get_filename(chooser);
  }

  gtk_widget_destroy(Widget::Instance()->dialog);

  GLWindow::Instance()->loadGraph->execute();
}

void Widget::quitEvent() {
  fprintf(stderr, "%d", GLWindow::Instance()->windowHeight);
  fprintf(stderr, "\nClosing widgetFunction\n");
  gtk_widget_destroy(GTK_WIDGET(Widget::Instance()->window));
}

void Widget::toggleView() {
  if (Widget::Instance()->visible) {
    Widget::Instance()->visible = false;
    gtk_widget_hide(Widget::Instance()->window);
  } else {
    gtk_widget_show(Widget::Instance()->window);
    Widget::Instance()->visible = true;
  }
}

void Widget::quitNetviz() {
  GLWindow::Instance()->quit();
}

