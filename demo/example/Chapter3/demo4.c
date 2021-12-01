#include <gtk/gtk.h> 
static int i = 1 ; 
GtkWidget *list; 
void list_add(GtkWidget *widget, gpointer data) 
{ 
	gchar buf[100]; 
	GtkContainer *container; 
	GtkWidget *item; 

	sprintf(buf,"列表项 %d",i); 
	container = GTK_CONTAINER(list); 
	item = gtk_list_item_new_with_label(buf); 
	gtk_container_add(container,item); 
	gtk_widget_show(item); 
	i++; 
} 
void list_clear (GtkButton *button,gpointer data) 
{ 
	gtk_list_clear_items(GTK_LIST(list),0,-1); 
} 
int main ( int argc , char* argv[]) 
{ 
	GtkWidget *window; 
	GtkWidget *vbox; 
	GtkWidget *hbox; 
	GtkWidget *button; 
	GtkWidget *view; 

	gtk_init(&argc,&argv); 
	window = gtk_window_new(GTK_WINDOW_TOPLEVEL); 
	g_signal_connect(G_OBJECT(window),"delete_event", 
			G_CALLBACK(gtk_main_quit),NULL); 
	gtk_window_set_title(GTK_WINDOW(window),"列表控件"); 
	gtk_window_set_position(GTK_WINDOW(window),GTK_WIN_POS_CENTER); 
	gtk_container_set_border_width(GTK_CONTAINER(window),10); 
	vbox = gtk_vbox_new(FALSE,0); 
	gtk_container_add(GTK_CONTAINER(window),vbox); 
	view = gtk_viewport_new(NULL,NULL); 
	gtk_box_pack_start(GTK_BOX(vbox),view,TRUE,TRUE,5); 
	list = gtk_list_new(); 
	gtk_container_add(GTK_CONTAINER(view),list); 
	gtk_list_set_selection_mode(GTK_LIST(list),GTK_SELECTION_MULTIPLE/*GTK_SELECTION_SINGLE*/); 
	hbox = gtk_hbox_new(FALSE,0); 
	gtk_box_pack_start(GTK_BOX(vbox),hbox,FALSE,FALSE,5); 
	button = gtk_button_new_with_label("插入"); 
	g_signal_connect(G_OBJECT(button),"clicked", 
			G_CALLBACK(list_add),NULL); 
	gtk_box_pack_start(GTK_BOX(hbox),button,FALSE,FALSE,5); 
	button = gtk_button_new_with_label("清除"); 
	g_signal_connect(G_OBJECT(button),"clicked", 
			G_CALLBACK(list_clear),NULL); 
	gtk_box_pack_start(GTK_BOX(hbox),button,FALSE,FALSE,5); 

	gtk_widget_show_all(window); 
	gtk_main(); 
	return FALSE; 
}
