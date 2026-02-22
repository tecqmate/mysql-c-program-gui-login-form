#include <gtk/gtk.h>
#include <string.h>
#include <regex.h>
#include "ui.h"
#include "auth.h"

static GtkWidget *entry_username;
static GtkWidget *entry_password;
static GtkWidget *lbl_status;

static gboolean is_valid_username(const char *username) {
    if (!username || strlen(username) < 4) return FALSE;

    regex_t regex;
    regcomp(&regex, "^[a-zA-Z0-9_]+$", REG_EXTENDED);
    int result = regexec(&regex, username, 0, NULL, 0);
    regfree(&regex);

    return result == 0;
}

static gboolean is_valid_password(const char *password) {
    return password && strlen(password) >= 1;
}

static void show_error(const char *message) {
    gtk_label_set_text(GTK_LABEL(lbl_status), message);
    gtk_widget_set_name(lbl_status, "error_label");
}

static void show_success(const char *message) {
    gtk_label_set_text(GTK_LABEL(lbl_status), message);
    gtk_widget_set_name(lbl_status, "success_label");
}

static void on_login_clicked(GtkButton *button, gpointer user_data) {

    const char *username =
        gtk_entry_get_text(GTK_ENTRY(entry_username));

    const char *password =
        gtk_entry_get_text(GTK_ENTRY(entry_password));

    if (strlen(username) == 0 || strlen(password) == 0) {
        show_error("Fields cannot be empty.");
        return;
    }

    if (!is_valid_username(username)) {
        show_error("Invalid username format.");
        return;
    }

    if (!is_valid_password(password)) {
        show_error("Password is required");
        return;
    }

    if (auth_login(username, password)) {
        show_success("Login Successful.");
    } else {
        show_error("Invalid credentials.");
    }
}

static void on_exit_clicked(GtkButton *button, gpointer user_data) {
    gtk_main_quit();
}

void init_ui(GtkBuilder *builder) {

    entry_username =
        GTK_WIDGET(gtk_builder_get_object(builder, "entry_username"));

    entry_password =
        GTK_WIDGET(gtk_builder_get_object(builder, "entry_password"));

    lbl_status =
        GTK_WIDGET(gtk_builder_get_object(builder, "lbl_status"));

    GtkWidget *btn_login =
        GTK_WIDGET(gtk_builder_get_object(builder, "btn_login"));

    GtkWidget *btn_exit =
        GTK_WIDGET(gtk_builder_get_object(builder, "btn_exit"));

    g_signal_connect(btn_login,
                     "clicked",
                     G_CALLBACK(on_login_clicked),
                     NULL);

    g_signal_connect(btn_exit,
                     "clicked",
                     G_CALLBACK(on_exit_clicked),
                     NULL);
}
