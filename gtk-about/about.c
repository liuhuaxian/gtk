#include <stdlib.h>
#include <stdio.h>
#include <gtk/gtk.h>
 
void show_about_dialog(GtkWidget *button);
 
int main(int argc,char **argv)
{
    GtkWidget *window;
    GtkWidget *button;
     
    gtk_init(&argc,&argv);
 
    window=gtk_window_new(GTK_WINDOW_TOPLEVEL);
     
    button=gtk_button_new_with_label("Click me!");
    gtk_container_add(GTK_CONTAINER(window),button);
     
    g_signal_connect(G_OBJECT(button),"clicked",G_CALLBACK(show_about_dialog),NULL);
    g_signal_connect(G_OBJECT(window),"destroy",G_CALLBACK(gtk_main_quit),NULL);
 
    gtk_widget_show_all(window);
     
    gtk_main();
 
    return 0;
}
 
void show_about_dialog(GtkWidget *button)
{
    GtkWidget *about_dialog;
    GdkPixbuf *logo;
     
    about_dialog=gtk_about_dialog_new();
    logo=gdk_pixbuf_new_from_file("./demo.jpg",NULL);
    gtk_about_dialog_set_logo(GTK_ABOUT_DIALOG(about_dialog),logo);
    gtk_about_dialog_set_wrap_license(GTK_ABOUT_DIALOG(about_dialog), TRUE);
    gtk_about_dialog_set_license_type(GTK_ABOUT_DIALOG(about_dialog),GTK_LICENSE_GPL_2_0);
    gtk_about_dialog_set_website(GTK_ABOUT_DIALOG(about_dialog), "https://www.chinaredflag.cn");
    gtk_about_dialog_set_website_label(GTK_ABOUT_DIALOG(about_dialog), "https://www.chinaredflag.cn");

    gtk_widget_show(GTK_WIDGET(about_dialog));
    //gtk_dialog_run(GTK_DIALOG(about_dialog));
 
    //gtk_widget_destroy(about_dialog);
 
    return;
 
}
