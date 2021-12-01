#include <gtk/gtk.h> 
gint i = 2 ; 
static GtkWidget *menu; 
static GtkWidget *item ; 
void add_menu (GtkButton* button,gpointer data) 
{ 
	gchar newitem[1024]; 
	gint len; 
	len = g_list_length(GTK_MENU_SHELL(menu)->children); 
	sprintf(newitem,"菜单项 %d",len+1); 
	item = gtk_menu_item_new_with_label(newitem); 
	gtk_widget_show(item); 
	gtk_menu_shell_append(GTK_MENU_SHELL(menu),item); 
	i++; 
} 
void remove_menu (GtkButton* button,gpointer data) 
{ 
	GList *list=NULL; 
	if ( i == 0 ) return ; 
	list = g_list_last(GTK_MENU_SHELL(menu)->children); 
	GTK_MENU_SHELL(menu)->children = g_list_remove 
		(GTK_MENU_SHELL(menu)->children,list->data); 
	i--; 
} 
//主函数
int main (int argc, char *argv[]) 
{ 
	GtkWidget* window; 
	GtkWidget* vbox; 
	GtkWidget* hbox; 
	GtkWidget* button; 
	GtkWidget *rootmenu,*menubar; //,*item; 
	gtk_init(&argc,&argv); 
	window = gtk_window_new(GTK_WINDOW_TOPLEVEL); 
	gtk_window_set_title(GTK_WINDOW(window),"动态添加菜单"); 
	gtk_container_set_border_width(GTK_CONTAINER(window),5); 
	g_signal_connect(G_OBJECT(window),"destroy", 
			G_CALLBACK(gtk_main_quit),NULL); 
	vbox = gtk_vbox_new(FALSE,0); 
	gtk_container_add(GTK_CONTAINER(window),vbox); 
	menubar = gtk_menu_bar_new(); 
	gtk_box_pack_start(GTK_BOX(vbox),menubar,FALSE,FALSE,5); 
	menu = gtk_menu_new(); 
	rootmenu = gtk_menu_item_new_with_label("根菜单"); 
	item = gtk_menu_item_new_with_label("菜单项 1"); 
	gtk_menu_shell_append(GTK_MENU_SHELL(menu),item); 
	item = gtk_menu_item_new_with_label("菜单项 2"); 
	gtk_menu_shell_append(GTK_MENU_SHELL(menu),item); 
	gtk_menu_item_set_submenu(GTK_MENU_ITEM(rootmenu),menu); 
	gtk_menu_shell_append(GTK_MENU_SHELL(menubar),rootmenu); 
	hbox = gtk_hbox_new(FALSE,0); 
	gtk_box_pack_start(GTK_BOX(vbox),hbox,FALSE,FALSE,5); 
	button = gtk_button_new_with_label("添加"); 
	g_signal_connect(G_OBJECT(button),"clicked", 
			G_CALLBACK(add_menu),NULL); 
	gtk_box_pack_start(GTK_BOX(hbox),button,TRUE,TRUE,5); 
	button = gtk_button_new_with_label("删除"); 
	g_signal_connect(G_OBJECT(button),"clicked", 
			G_CALLBACK(remove_menu),NULL); 
	gtk_box_pack_start(GTK_BOX(hbox),button,TRUE,TRUE,5); 
	gtk_widget_show_all(window); 
	gtk_main(); 
	return FALSE; 
}
