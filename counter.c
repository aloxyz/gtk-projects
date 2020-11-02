#include <gtk/gtk.h>
#include <stdio.h>
int count = 0;
char buffer[24];

GtkWidget *window, *label, *button, *grid;

void do_count() {
    count++;
    sprintf(buffer, "%d", count);
    gtk_label_set_text(GTK_LABEL(label), buffer);
}

static void activate (GtkApplication* app, gpointer user_data) {

    window = gtk_application_window_new(app);
    gtk_window_set_title(GTK_WINDOW(window), "Counter");
    gtk_window_set_default_size(GTK_WINDOW(window), 200, 30);

    grid = gtk_grid_new();
    gtk_grid_set_column_homogeneous(GTK_GRID(grid), TRUE);

    label = gtk_label_new("0");
    gtk_grid_attach(GTK_GRID(grid), label, 0, 0, 1, 1);

    button = gtk_button_new_with_label("Count");
    gtk_grid_attach(GTK_GRID(grid), button, 1, 0, 1, 1);
    g_signal_connect(button, "clicked", G_CALLBACK(do_count), NULL);

    gtk_container_add(GTK_CONTAINER(window), grid);
    gtk_widget_show_all(window);
}


int main (int argc, char **argv) {
    GtkApplication *app;
    int status;

    app = gtk_application_new("org.gtk.counter", G_APPLICATION_FLAGS_NONE);
    g_signal_connect(app, "activate", G_CALLBACK (activate), NULL);
    status = g_application_run (G_APPLICATION(app), argc, argv);
    g_object_unref(app);

    return status;
}
