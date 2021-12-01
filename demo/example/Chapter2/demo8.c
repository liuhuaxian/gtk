#include <gtk/gtk.h> 
static GtkWidget* entry; 
void on_menu_changed (GtkOptionMenu* option,gpointer data) 
{ 
	gchar buf[20]; 
	gint i; 
	i = gtk_option_menu_get_history(option); 
	sprintf(buf,"菜单项 %d",i+1); 
	gtk_entry_set_text(GTK_ENTRY(entry),buf); 
} 
int main (int argc, char* argv[]) 
{ 
	GtkWidget* window; 
	GtkWidget* option; 
	GtkWidget* hbox; 
	GtkWidget* menu; 
	GtkWidget* item; 
	gint i ; 
	gchar buf[20]; 
	gtk_init(&argc,&argv); 
	window = gtk_window_new(GTK_WINDOW_TOPLEVEL); 
	gtk_window_set_title(GTK_WINDOW(window),"条件菜单"); 
	g_signal_connect(G_OBJECT(window),"destroy", 
			G_CALLBACK(gtk_main_quit),NULL); 
	gtk_container_set_border_width(GTK_CONTAINER(window),20); 
	hbox = gtk_hbox_new(FALSE,0); 
	gtk_container_add(GTK_CONTAINER(window),hbox); 
	entry = gtk_entry_new(); 
	gtk_entry_set_text(GTK_ENTRY(entry),"菜单项 1"); 
	gtk_box_pack_start(GTK_BOX(hbox),entry,FALSE,FALSE,5); 
	menu = gtk_menu_new(); 
	for(i=1; i<8; i++) 
	{ 
		sprintf(buf,"菜单项 %d",i); 
		item = gtk_menu_item_new_with_label(buf); 
		gtk_menu_shell_append(GTK_MENU_SHELL(menu),item); 
	} 
	option = gtk_option_menu_new(); 
	gtk_option_menu_set_menu(GTK_OPTION_MENU(option),menu); 
	g_signal_connect(G_OBJECT(option),"changed", 
			G_CALLBACK(on_menu_changed),NULL); 
	gtk_box_pack_start(GTK_BOX(hbox),option,FALSE,FALSE,10); 
	gtk_widget_show_all(window); 
	gtk_main(); 
	return FALSE; 
}
