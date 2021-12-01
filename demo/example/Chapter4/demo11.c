#include <gtk/gtk.h> 
static GtkWidget* credits_window; 
GtkWidget* create_credits () 
{ 
	GtkWidget *window; 
	GtkWidget *vbox; 
	GtkWidget *notebook; 
	GtkWidget *page; 
	GtkWidget *label; 
	window = gtk_window_new(GTK_WINDOW_TOPLEVEL); 
	gtk_window_set_title(GTK_WINDOW(window),"开发人员"); 
	vbox = gtk_vbox_new(FALSE,0); 
	gtk_container_add(GTK_CONTAINER(window),vbox); 
	notebook = gtk_notebook_new(); 
	gtk_box_pack_start(GTK_BOX(vbox),notebook,TRUE,TRUE,5); 
	page = gtk_vbox_new(FALSE,0); 
	label = gtk_label_new("杨文齐，ywq51305@fm365.com"); 
	gtk_box_pack_start(GTK_BOX(page),label,FALSE,FALSE,5); 
	label = gtk_label_new("宋国伟，gwsong52@sohu.com"); 
	gtk_box_pack_start(GTK_BOX(page),label,FALSE,FALSE,5); 
	label = gtk_label_new("编辑"); 
	gtk_notebook_append_page(GTK_NOTEBOOK(notebook),page,label); 
	page = gtk_vbox_new(FALSE,0); 
	label = gtk_label_new("郝春艳，gwsong_jl@sohu.com"); 
	gtk_box_pack_start(GTK_BOX(page),label,FALSE,FALSE,5); 
	label = gtk_label_new("测试"); 
	gtk_notebook_append_page(GTK_NOTEBOOK(notebook),page,label); 
	gtk_widget_show_all(window); 
	return window; 
} 
void show_credits () 
{ 
	credits_window = create_credits(); 
	gtk_widget_show(credits_window); 
} 
int main ( int argc , char* argv[]) 
{ 
	GtkWidget *window; 
	GtkWidget *bbox; 
	GtkWidget *vbox; 
	GtkWidget *label; 
	GtkWidget *image; 
	GtkWidget *sep; 
	GtkWidget *button; 
	gtk_init(&argc,&argv); 
	window = gtk_window_new(GTK_WINDOW_TOPLEVEL); 
	g_signal_connect(G_OBJECT(window),"delete_event", 
			G_CALLBACK(gtk_main_quit),NULL); 
	gtk_window_set_title(GTK_WINDOW(window),"关于对话框"); 
	gtk_window_set_position(GTK_WINDOW(window),GTK_WIN_POS_CENTER); 
	gtk_container_set_border_width(GTK_CONTAINER(window),10); 

	vbox = gtk_vbox_new(FALSE,0); 
	gtk_container_add(GTK_CONTAINER(window),vbox); 
	image = gtk_image_new_from_file("gnome-gmush.png"); 
	gtk_box_pack_start(GTK_BOX(vbox),image,FALSE,FALSE,5); 
	label = gtk_label_new(NULL); 
	gtk_label_set_markup(GTK_LABEL(label),"<span><big>GTK+2.0 实例编程</big></span>"); 
	gtk_box_pack_start(GTK_BOX(vbox),label,FALSE,FALSE,5); 
	label = gtk_label_new("版权所有：清华大学出版社\n作者：宋国伟"); 
	gtk_box_pack_start(GTK_BOX(vbox),label,FALSE,FALSE,5); 
	sep = gtk_hseparator_new(); 
	gtk_box_pack_start(GTK_BOX(vbox),sep,FALSE,FALSE,5); 
	bbox = gtk_hbutton_box_new(); 
	gtk_button_box_set_layout(GTK_BUTTON_BOX(bbox),GTK_BUTTONBOX_EDGE); 
	gtk_box_pack_start(GTK_BOX(vbox),bbox,FALSE,FALSE,5); 
	button = gtk_button_new_with_label("开发人员"); 
	gtk_box_pack_start(GTK_BOX(bbox),button,FALSE,FALSE,25); 
	g_signal_connect(G_OBJECT(button),"clicked", 
			G_CALLBACK(show_credits),NULL); 
	button = gtk_button_new_from_stock(GTK_STOCK_OK); 
	g_signal_connect(G_OBJECT(button),"clicked", 
			G_CALLBACK(gtk_main_quit),NULL); 
	gtk_box_pack_start(GTK_BOX(bbox),button,FALSE,FALSE,35); 
	gtk_widget_show_all(window); 
	gtk_main(); 
	return FALSE; 
}
