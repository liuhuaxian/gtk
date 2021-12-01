#include <gtk/gtk.h> 
GtkWidget *create_item (gint i) 
{ 
	GtkWidget* item; 
	GtkWidget* hbox; 
	GtkWidget* image; 
	GtkWidget* label; 

	hbox = gtk_hbox_new(FALSE,0); 
	switch(i) 
	{ 
		case 1 : 
			image = gtk_image_new_from_stock 
				(GTK_STOCK_YES,GTK_ICON_SIZE_MENU); 
			label = gtk_label_new("列表项一"); 
			break; 
		case 2 : 
			image = 
				gtk_image_new_from_stock(GTK_STOCK_NO,GTK_ICON_SIZE_MENU); 
			label = gtk_label_new("列表项二"); 
			break; 
		case 3 : 
			image = gtk_image_new_from_stock 
				(GTK_STOCK_HELP,GTK_ICON_SIZE_MENU); 
			label = gtk_label_new("列表项三"); 
			break; 
		case 4 : 
			image = 
				gtk_image_new_from_stock(GTK_STOCK_OK,GTK_ICON_SIZE_MENU); 
			label = gtk_label_new("列表项四"); 
			break; 
		case 5 : 
			image = gtk_image_new_from_stock 
				(GTK_STOCK_CANCEL,GTK_ICON_SIZE_MENU); 
			label = gtk_label_new("列表项五"); 
			break; 
	} 
	gtk_box_pack_start(GTK_BOX(hbox),image,FALSE,FALSE,2); 
	gtk_box_pack_start(GTK_BOX(hbox),label,FALSE,FALSE,2); 

	item = gtk_list_item_new(); 
	gtk_container_add(GTK_CONTAINER(item),hbox); 
	gtk_widget_show_all(item); 
	return item; 
} 
int main ( int argc , char* argv[]) 
{ 
	GtkWidget *window; 
	GtkWidget *combo; 
	GtkWidget *vbox; 
	GtkWidget *label; 
	GList* items = NULL; 
	GtkWidget *item; 

	items = g_list_append(items,"列表项 A"); 
	items = g_list_append(items,"列表项 B"); 
	items = g_list_append(items,"列表项 C"); 
	items = g_list_append(items,"列表项 D"); 
	items = g_list_append(items,"列表项 E"); 
	gtk_init(&argc,&argv); 
	window = gtk_window_new(GTK_WINDOW_TOPLEVEL); 
	g_signal_connect(G_OBJECT(window),"delete_event", G_CALLBACK(gtk_main_quit),NULL); 
	gtk_window_set_title(GTK_WINDOW(window),"下拉列表框"); 
	gtk_window_set_position(GTK_WINDOW(window),GTK_WIN_POS_CENTER); 
	gtk_container_set_border_width(GTK_CONTAINER(window),20); 

	vbox = gtk_vbox_new(FALSE,0); 
	gtk_container_add(GTK_CONTAINER(window),vbox); 
	label = gtk_label_new("请选择下列中的一项:"); 
	gtk_box_pack_start(GTK_BOX(vbox),label,FALSE,FALSE,5); 
	combo = gtk_combo_new(); 
	gtk_box_pack_start(GTK_BOX(vbox),combo,FALSE,FALSE,5); 
	gtk_combo_set_popdown_strings(GTK_COMBO(combo),items); 

	label = gtk_label_new("另一种选择方式："); 
	gtk_box_pack_start(GTK_BOX(vbox),label,FALSE,FALSE,5); 
	combo = gtk_combo_new(); 
	gtk_box_pack_start(GTK_BOX(vbox),combo,FALSE,FALSE,5); 
	item = create_item(1); 
	gtk_combo_set_item_string(GTK_COMBO(combo),GTK_ITEM(item),"项目一"); 
	gtk_container_add(GTK_CONTAINER(GTK_COMBO(combo)->list),item); 
	item = create_item(2); 
	gtk_combo_set_item_string(GTK_COMBO(combo),GTK_ITEM(item),"项目二"); 
	gtk_container_add(GTK_CONTAINER(GTK_COMBO(combo)->list),item); 
	item = create_item(3); 
	gtk_combo_set_item_string(GTK_COMBO(combo),GTK_ITEM(item),"项目三"); 
	gtk_container_add(GTK_CONTAINER(GTK_COMBO(combo)->list),item); 
	item = create_item(4); 
	gtk_combo_set_item_string(GTK_COMBO(combo),GTK_ITEM(item),"项目四"); 
	gtk_container_add(GTK_CONTAINER(GTK_COMBO(combo)->list),item); 
	item = create_item(5); 
	gtk_combo_set_item_string(GTK_COMBO(combo),GTK_ITEM(item),"项目五"); 
	gtk_container_add(GTK_CONTAINER(GTK_COMBO(combo)->list),item); 

	gtk_widget_show_all(window); 
	gtk_main(); 
	return FALSE; 
}
