#include <gtk/gtk.h> 
#include "callbacks.h" 
#include "interface.h" 
int main (int argc , gchar* argv[]) 
{ 
	GtkWidget * window ; 
	gtk_init(&argc,&argv); 
	window = create_window(); 
	g_signal_connect(G_OBJECT(window),"delete_event", 
			G_CALLBACK(on_window_delete_event),NULL); 
	gtk_widget_show(window); 
	gtk_main(); 
	return FALSE; 
}
