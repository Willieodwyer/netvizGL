//
// Created by werl on 20/12/16.
//

#include "../inc/ButtonWidget.h"

ButtonWidget *ButtonWidget::instance = NULL;

ButtonWidget *ButtonWidget::Instance() {
  if (!instance)   // Only allow one instance of class to be generated.
    instance = new ButtonWidget();
  return instance;
}

ButtonWidget::ButtonWidget() {
  GtkApplication *app;
  int status;

  app = gtk_application_new("org.gtk.example", G_APPLICATION_FLAGS_NONE);
  g_signal_connect (app, "activate", G_CALLBACK(activate), NULL);
  status = g_application_run(G_APPLICATION (app), 0, 0);
  g_object_unref(app);
}

void ButtonWidget::activate(GtkApplication *app, gpointer user_data) {
  ButtonWidget::Instance()->window = gtk_application_window_new(app);
  gtk_window_set_title(GTK_WINDOW (ButtonWidget::Instance()->window), "Window");
  gtk_window_set_default_size(GTK_WINDOW (ButtonWidget::Instance()->window), 200, 200);

  ButtonWidget::Instance()->button_box = gtk_button_box_new(GTK_ORIENTATION_HORIZONTAL);
  gtk_container_add(GTK_CONTAINER (ButtonWidget::Instance()->window), ButtonWidget::Instance()->button_box);

  ButtonWidget::Instance()->button = gtk_button_new_with_label("Hello World");
  g_signal_connect (ButtonWidget::Instance()->button, "clicked", G_CALLBACK(doSomething), NULL);
  g_signal_connect_swapped (ButtonWidget::Instance()->button,
                            "clicked",
                            G_CALLBACK(gtk_widget_destroy),
                            ButtonWidget::Instance()->window);
  gtk_container_add(GTK_CONTAINER (ButtonWidget::Instance()->button_box), ButtonWidget::Instance()->button);

  gtk_widget_show_all(ButtonWidget::Instance()->window);
}

void ButtonWidget::doSomething() {

}

