//
// Created by werl on 20/12/16.
//

#include "../inc/Widget.h"
#include "../inc/GLWindow.h"

Widget *Widget::instance = NULL;

Widget *Widget::Instance()
{
    if (!instance)   // Only allow one instance of class to be generated.
        instance = new Widget();
    return instance;
}

Widget::Widget()
{
    visible = true;
    app = gtk_application_new("org.gtk.Netviz", G_APPLICATION_FLAGS_NONE);
    g_signal_connect(app, "activate", G_CALLBACK(activate), NULL);
    g_application_run(G_APPLICATION(app), 0, 0);
    g_object_unref(app);
}

Widget::~Widget()
{
}

void Widget::activate(GtkApplication *app, gpointer user_data)
{
    Widget::Instance()->window = gtk_application_window_new(app);
    gtk_window_set_title(GTK_WINDOW (Widget::Instance()->window), "Toolbox");
    gtk_window_set_default_size(GTK_WINDOW (Widget::Instance()->window), 197, 200);
    gtk_window_move(GTK_WINDOW (Widget::Instance()->window), 270, 152);
    g_signal_connect ((Widget::Instance()->window), "delete-event", G_CALLBACK(toggleView), Widget::Instance());

    Widget::Instance()->button_box = gtk_button_box_new(GTK_ORIENTATION_VERTICAL);
    gtk_container_add(GTK_CONTAINER (Widget::Instance()->window), Widget::Instance()->button_box);

    //File Dialog button
    Widget::Instance()->openFileButton = gtk_button_new_with_label("Open File");
    g_signal_connect (Widget::Instance()->openFileButton, "clicked", G_CALLBACK(openFile), Widget::Instance());

    //Algorithm select button
    Widget::Instance()->algorithmButton = gtk_combo_box_new();

    // Exit button
    Widget::Instance()->exitButton = gtk_button_new_with_label("Exit");
    g_signal_connect (Widget::Instance()->exitButton, "clicked", G_CALLBACK(quitNetviz), Widget::Instance());

    // Separator
    Widget::Instance()->separator = gtk_separator_new(GTK_ORIENTATION_HORIZONTAL);

    // Colour Node
    Widget::Instance()->colourNodeLabel = gtk_label_new("Colour Node");
    Widget::Instance()->colourNodeButton = (GtkColorChooser *) gtk_color_button_new();

    // Text Node
    Widget::Instance()->textNodeLabel = gtk_label_new("Add text to node");
    Widget::Instance()->textNodeEntry = gtk_entry_new();
    gtk_entry_set_text((GtkEntry *) Widget::Instance()->textNodeEntry, "Enter node text here");
    gtk_entry_set_max_length((GtkEntry *) Widget::Instance()->textNodeEntry, 64);
    g_signal_connect (Widget::Instance()->textNodeEntry, "changed", G_CALLBACK(textChanged), Widget::Instance());
    Widget::Instance()->textNodeText = (char *) gtk_entry_get_text((GtkEntry *) Widget::Instance()->textNodeEntry);

    gtk_container_add(GTK_CONTAINER (Widget::Instance()->button_box), Widget::Instance()->openFileButton);
    gtk_container_add(GTK_CONTAINER (Widget::Instance()->button_box), Widget::Instance()->algorithmButton);
    gtk_container_add(GTK_CONTAINER (Widget::Instance()->button_box), Widget::Instance()->exitButton);
    gtk_container_add(GTK_CONTAINER (Widget::Instance()->button_box), Widget::Instance()->separator);

    //TODO
//  gtk_container_add(GTK_CONTAINER (Widget::Instance()->button_box), Widget::Instance()->deleteNodeButton);
//  gtk_container_add(GTK_CONTAINER (Widget::Instance()->button_box), Widget::Instance()->deleteEdgeButton);

    gtk_container_add(GTK_CONTAINER (Widget::Instance()->button_box), Widget::Instance()->colourNodeLabel);
    gtk_container_add(GTK_CONTAINER (Widget::Instance()->button_box),
                      (GtkWidget *) Widget::Instance()->colourNodeButton);

    gtk_container_add(GTK_CONTAINER (Widget::Instance()->button_box), Widget::Instance()->textNodeLabel);
    gtk_container_add(GTK_CONTAINER (Widget::Instance()->button_box), Widget::Instance()->textNodeEntry);

//  gtk_container_add(GTK_CONTAINER (Widget::Instance()->button_box), Widget::Instance()->colourEdgeButton);
//  gtk_container_add(GTK_CONTAINER (Widget::Instance()->button_box), Widget::Instance()->filterButton);
//  gtk_container_add(GTK_CONTAINER (Widget::Instance()->button_box), Widget::Instance()->runButton);

    gtk_widget_show_all(Widget::Instance()->window);

}

void Widget::openFile()
{
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
        //fprintf(stderr, "%s", gtk_file_chooser_get_filename(chooser));
    }

    if (res == GTK_RESPONSE_CANCEL) {
        gtk_widget_destroy(Widget::Instance()->dialog);
        return;
    }

    gtk_widget_destroy(Widget::Instance()->dialog);

    if (GLWindow::Instance()->graphFilePath)
        GLWindow::Instance()->loadGraph->execute();
}

void Widget::updateColour()
{
    GdkRGBA *colour = new GdkRGBA;
    gtk_color_chooser_get_rgba(Widget::Instance()->colourNodeButton, colour);

    Widget::Instance()->redColour = colour->red;
    Widget::Instance()->blueColour = colour->blue;
    Widget::Instance()->greenColour = colour->green;
}

void Widget::toggleView()
{
    if (Widget::Instance()->visible) {
        Widget::Instance()->visible = false;
        gtk_widget_hide(Widget::Instance()->window);
    }
    else {
        gtk_widget_show(Widget::Instance()->window);
        Widget::Instance()->visible = true;
    }
}

void Widget::quitNetviz()
{
    GLWindow::Instance()->quit();
}

void Widget::textChanged()
{
    Widget::Instance()->textNodeText = (char *) gtk_entry_get_text((GtkEntry *) Widget::Instance()->textNodeEntry);
}

