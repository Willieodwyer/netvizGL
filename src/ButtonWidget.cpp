//
// Created by werl on 20/12/16.
//

#include "../inc/ButtonWidget.h"
#include "../inc/Window.h"
#include "../inc/FileReader.h"
#include "../inc/Graphs/EdgeGraph.h"

ButtonWidget *ButtonWidget::instance = NULL;

ButtonWidget *ButtonWidget::Instance() {
  if (!instance)   // Only allow one instance of class to be generated.
    instance = new ButtonWidget();
  return instance;
}

ButtonWidget::ButtonWidget() {
  visible = true;

  GtkApplication *app;
  int status;
  app = gtk_application_new("org.gtk.example", G_APPLICATION_FLAGS_NONE);
  g_signal_connect (app, "activate", G_CALLBACK(activate), NULL);
  status = g_application_run(G_APPLICATION (app), 0, 0);
  g_object_unref(app);
}

ButtonWidget::~ButtonWidget() {
}

void ButtonWidget::activate(GtkApplication *app, gpointer user_data) {
  ButtonWidget::Instance()->window = gtk_application_window_new(app);
  gtk_window_set_title(GTK_WINDOW (ButtonWidget::Instance()->window), "Toolbox");
  gtk_window_set_default_size(GTK_WINDOW (ButtonWidget::Instance()->window), 197, 200);
  gtk_window_move(GTK_WINDOW (ButtonWidget::Instance()->window), 270, 152);

  ButtonWidget::Instance()->button_box = gtk_button_box_new(GTK_ORIENTATION_VERTICAL);
  gtk_container_add(GTK_CONTAINER (ButtonWidget::Instance()->window), ButtonWidget::Instance()->button_box);

  //File Dialog button
  ButtonWidget::Instance()->openFileButton = gtk_button_new_with_label("Open File");
  g_signal_connect (ButtonWidget::Instance()->openFileButton, "clicked", G_CALLBACK(openFile), NULL);

  //Algorithm select button
  ButtonWidget::Instance()->algorithmButton = gtk_combo_box_new();
  //g_signal_connect (ButtonWidget::Instance()->openFileButton, "clicked", G_CALLBACK(openFile), NULL);

  // Exit button
  ButtonWidget::Instance()->exitButton = gtk_button_new_with_label("Exit");
  g_signal_connect (ButtonWidget::Instance()->exitButton, "clicked", G_CALLBACK(quitNetviz), NULL);

  // Separator
  ButtonWidget::Instance()->separator = gtk_separator_new(GTK_ORIENTATION_HORIZONTAL);
  g_signal_connect ((ButtonWidget::Instance()->window), "delete-event", G_CALLBACK(toggleView), NULL);

  gtk_container_add(GTK_CONTAINER (ButtonWidget::Instance()->button_box), ButtonWidget::Instance()->openFileButton);
  gtk_container_add(GTK_CONTAINER (ButtonWidget::Instance()->button_box), ButtonWidget::Instance()->algorithmButton);
  gtk_container_add(GTK_CONTAINER (ButtonWidget::Instance()->button_box), ButtonWidget::Instance()->exitButton);
  gtk_container_add(GTK_CONTAINER (ButtonWidget::Instance()->button_box), ButtonWidget::Instance()->separator);

  //TODO
//  gtk_container_add(GTK_CONTAINER (ButtonWidget::Instance()->button_box), ButtonWidget::Instance()->deleteNodeButton);
//  gtk_container_add(GTK_CONTAINER (ButtonWidget::Instance()->button_box), ButtonWidget::Instance()->deleteEdgeButton);
//  gtk_container_add(GTK_CONTAINER (ButtonWidget::Instance()->button_box), ButtonWidget::Instance()->colourNodeButton);
//  gtk_container_add(GTK_CONTAINER (ButtonWidget::Instance()->button_box), ButtonWidget::Instance()->colourEdgeButton);
//  gtk_container_add(GTK_CONTAINER (ButtonWidget::Instance()->button_box), ButtonWidget::Instance()->filterButton);
//  gtk_container_add(GTK_CONTAINER (ButtonWidget::Instance()->button_box), ButtonWidget::Instance()->runButton);

  gtk_widget_show_all(ButtonWidget::Instance()->window);

}

void ButtonWidget::openFile() {
  GtkFileChooserAction action = GTK_FILE_CHOOSER_ACTION_OPEN;
  gint res;

  ButtonWidget::Instance()->dialog =
      gtk_file_chooser_dialog_new("Open File",
                                  NULL,
                                  action,
                                  ("_Cancel"),
                                  GTK_RESPONSE_CANCEL,
                                  ("_Open"),
                                  GTK_RESPONSE_ACCEPT,
                                  NULL);

  res = gtk_dialog_run(GTK_DIALOG (ButtonWidget::Instance()->dialog));
  if (res == GTK_RESPONSE_ACCEPT) {
    string filePath;
    GtkFileChooser *chooser = GTK_FILE_CHOOSER (ButtonWidget::Instance()->dialog);
    filePath = gtk_file_chooser_get_filename(chooser);

    Window::Instance()->graph = new EdgeGraph((char *) filePath.c_str());
    if (Window::Instance()->algorithmThread) {
      Window::Instance()->endThread = true;
      Window::Instance()->algorithmThread->join();
      delete Window::Instance()->algorithmThread;
    }

    Window::Instance()->algorithm = new SimpleForceDirected(Window::Instance()->graph);
    Window::Instance()->endThread = false;
    Window::Instance()->algorithmThread = new thread(Window::algorithmFunction);
  }

  gtk_widget_destroy(ButtonWidget::Instance()->dialog);
}

void ButtonWidget::quitEvent() {
  fprintf(stderr, "%d", Window::Instance()->windowHeight);
  fprintf(stderr, "\nClosing widget\n");
  gtk_widget_destroy(GTK_WIDGET(ButtonWidget::Instance()->window));
}

void ButtonWidget::toggleView() {
  if (ButtonWidget::Instance()->visible) {
    ButtonWidget::Instance()->visible = false;
    gtk_widget_hide(ButtonWidget::Instance()->window);
  } else {
    gtk_widget_show(ButtonWidget::Instance()->window);
    ButtonWidget::Instance()->visible = true;
  }
}

void ButtonWidget::quitNetviz() {
  Window::Instance()->quit();
}

