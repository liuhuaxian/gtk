#include <gtk/gtk.h>

int main ( int argc , char* argv[])
{
        GtkWidget *window, *scwin;
        GtkWidget *vpaned, *view1, *view2;
        GtkWidget *image, *button;
        GdkPixbuf *pixbuf1, *pixbuf2, *pixbuf3, *pixbuf4;
        GtkTextBuffer *buffer;
        GtkTextIter start, end;
        GtkTextChildAnchor *anchor;
        gtk_init(&argc,&argv);
        window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
        g_signal_connect(G_OBJECT(window),"delete_event",
                        G_CALLBACK(gtk_main_quit),NULL);
        gtk_window_set_title(GTK_WINDOW(window),"使用textview控件");
        gtk_window_set_default_size(GTK_WINDOW(window),300,200);
        gtk_window_set_position(GTK_WINDOW(window),GTK_WIN_POS_CENTER);
        gtk_container_set_border_width(GTK_CONTAINER(window),10);
        vpaned = gtk_vpaned_new();
        gtk_container_add(GTK_CONTAINER(window),vpaned);
#if 0
	scwin = gtk_scrolled_window_new(NULL,NULL);
        gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(scwin),
                        GTK_POLICY_AUTOMATIC,GTK_POLICY_AUTOMATIC);
        view1 = gtk_text_view_new();
        gtk_paned_add1(GTK_PANED(vpaned),scwin);
        gtk_container_add(GTK_CONTAINER(scwin),view1);
#endif
	gtk_widget_show_all(window);
	gtk_main();
	return 0;

}
