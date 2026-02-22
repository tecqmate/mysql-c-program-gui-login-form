#include <gtk/gtk.h>
#include "ui.h"

int main(int argc, char *argv[]) {

    g_setenv("GDK_SCALE", "2", TRUE);
    g_setenv("GDK_DPI_SCALE", "1.0", TRUE);

    gtk_init(&argc, &argv);

    GtkBuilder *builder = gtk_builder_new_from_file("resources/login.ui");

    GtkWidget *window = GTK_WIDGET(
        gtk_builder_get_object(builder, "main_window")
    );

    init_ui(builder);

    // Load CSS
    GtkCssProvider *provider = gtk_css_provider_new();
    gtk_css_provider_load_from_path(provider, "resources/style.css", NULL);
    gtk_style_context_add_provider_for_screen(
        gdk_screen_get_default(),
        GTK_STYLE_PROVIDER(provider),
        GTK_STYLE_PROVIDER_PRIORITY_USER
    );

    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);
    gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);

    gtk_widget_show_all(window);
    gtk_main();

    return 0;
}
