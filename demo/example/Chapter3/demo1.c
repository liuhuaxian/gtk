#include <gtk/gtk.h> 
GtkWidget* create_button (gint i) 
{ 
	GtkWidget *image; 
	GtkWidget *button; 
	GtkWidget *vbox; 
	GtkWidget *label; 
	switch(i) 
	{ 
		case 1 : 
			image = gtk_image_new_from_stock 
				(GTK_STOCK_YES,GTK_ICON_SIZE_MENU); 
			label = gtk_label_new("是"); 
			break; 
		case 2 : 
			image = 
				gtk_image_new_from_stock(GTK_STOCK_NO,GTK_ICON_SIZE_MENU); 
			label = gtk_label_new("否"); 
			break; 
		case 3 : 
			image = gtk_image_new_from_stock 
				(GTK_STOCK_HELP,GTK_ICON_SIZE_MENU); 
			label = gtk_label_new("帮助"); 
			break; 
	} 
	button = gtk_button_new(); 
	vbox = gtk_vbox_new(FALSE,0); 
	gtk_container_add(GTK_CONTAINER(button),vbox); 
	gtk_box_pack_start(GTK_BOX(vbox),image,FALSE,FALSE,0); 
	gtk_box_pack_start(GTK_BOX(vbox),label,FALSE,FALSE,0); 
	return button; 
}

GtkWidget* create_button_box (gboolean ish, 
		GtkButtonBoxStyle style, 
		const gchar* title) 
{ 
	GtkWidget *frame; 
	GtkWidget *button; 
	GtkWidget *bbox; 
	frame = gtk_frame_new(title);//"居中")); 
	if(ish == TRUE) 
		bbox = gtk_hbutton_box_new(); 
	else 
		bbox = gtk_vbutton_box_new(); 
	gtk_box_set_spacing(GTK_BOX(bbox),5); 
	gtk_button_box_set_layout(GTK_BUTTON_BOX(bbox),style); 
	gtk_container_set_border_width(GTK_CONTAINER(bbox),5); 
	gtk_container_add(GTK_CONTAINER(frame),bbox); 

	button = create_button(1); 
	gtk_box_pack_start(GTK_BOX(bbox),button,FALSE,FALSE,2); 
	button = create_button(2); 
	gtk_box_pack_start(GTK_BOX(bbox),button,FALSE,FALSE,2); 
	button = create_button(3); 
	gtk_box_pack_start(GTK_BOX(bbox),button,FALSE,FALSE,2); 
	return frame; 
} 
int main ( int argc , char* argv[]) 
{ 
	GtkWidget *window; 
	GtkWidget *vbox; 
	GtkWidget *hbox; 
	GtkWidget *frame; 
	gtk_init(&argc,&argv); 
	window = gtk_window_new(GTK_WINDOW_TOPLEVEL); 
	g_signal_connect(G_OBJECT(window),"delete_event", 
			G_CALLBACK(gtk_main_quit),NULL); 
	gtk_window_set_title(GTK_WINDOW(window),"按钮盒"); 
	gtk_window_set_position(GTK_WINDOW(window),GTK_WIN_POS_CENTER); 

	hbox = gtk_hbox_new(FALSE,0); 
	gtk_container_add(GTK_CONTAINER(window),hbox); 
	vbox = gtk_vbox_new(FALSE,0); 
	gtk_box_pack_start(GTK_BOX(hbox),vbox,FALSE,FALSE,2); 
	frame = create_button_box(TRUE,GTK_BUTTONBOX_EDGE,"居中"); 
	gtk_box_pack_start(GTK_BOX(vbox),frame,FALSE,FALSE,2); 
	frame = create_button_box(TRUE,GTK_BUTTONBOX_SPREAD,"紧密"); 
	gtk_box_pack_start(GTK_BOX(vbox),frame,FALSE,FALSE,2); 
	frame = create_button_box(TRUE,GTK_BUTTONBOX_END,"尾对齐"); 
	gtk_box_pack_start(GTK_BOX(vbox),frame,FALSE,FALSE,2); 

	frame = create_button_box(TRUE,GTK_BUTTONBOX_START,"首对齐"); 
	gtk_box_pack_start(GTK_BOX(vbox),frame,FALSE,FALSE,2); 
	frame = create_button_box(FALSE,GTK_BUTTONBOX_EDGE,"居中"); 
	gtk_box_pack_start(GTK_BOX(hbox),frame,FALSE,FALSE,2); 
	frame = create_button_box(FALSE,GTK_BUTTONBOX_SPREAD,"紧密"); 
	gtk_box_pack_start(GTK_BOX(hbox),frame,FALSE,FALSE,2); 

	frame = create_button_box(FALSE,GTK_BUTTONBOX_END,"尾对齐"); 
	gtk_box_pack_start(GTK_BOX(hbox),frame,FALSE,FALSE,2); 
	frame = create_button_box(FALSE,GTK_BUTTONBOX_START,"首对齐"); 
	gtk_box_pack_start(GTK_BOX(hbox),frame,FALSE,FALSE,2); 

	gtk_widget_show_all(window); 
	gtk_main(); 
	return FALSE; 
}
