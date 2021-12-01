#include <gtk/gtk.h> 
static gboolean 
button_press_callback (GtkWidget *event_box, 
		GdkEventButton *event, 
		gpointer data) 
{ 
	if(event->button == 1)//判断是否为鼠标左键
		system("galeon our.html");//打开our.html文件
	return TRUE; 
} 
int main ( int argc , char* argv[]) 
{ 
	GtkWidget *window; 
	GtkWidget *vbox; 
	GtkWidget *hbox; 
	GtkWidget *label; 
	GtkWidget *image; 
	GtkWidget *eventbox; 

	gtk_init(&argc,&argv); 
	window = gtk_window_new(GTK_WINDOW_TOPLEVEL); 
	g_signal_connect(G_OBJECT(window),"delete_event", 
			G_CALLBACK(gtk_main_quit),NULL); 
	gtk_window_set_title(GTK_WINDOW(window),"URL链接"); 
	gtk_window_set_position(GTK_WINDOW(window),GTK_WIN_POS_CENTER); 
	gtk_container_set_border_width(GTK_CONTAINER(window),10); 

	vbox = gtk_vbox_new(FALSE,0); 
	gtk_container_add(GTK_CONTAINER(window),vbox); 
	label = gtk_label_new("以下为两种形式的超链接："); 
	gtk_box_pack_start(GTK_BOX(vbox),label,FALSE,FALSE,5); 
	hbox = gtk_hbox_new(FALSE,0); 
	gtk_box_pack_start(GTK_BOX(vbox),hbox,FALSE,FALSE,5); 

	eventbox = gtk_event_box_new(); 
	g_signal_connect (G_OBJECT (eventbox),"button_press_event", 
			G_CALLBACK (button_press_callback),image); 
	gtk_box_pack_start(GTK_BOX(hbox),eventbox,FALSE,FALSE,15); 
	label = gtk_label_new("欢迎参观我的网页...");//这是其中的一个链接
	gtk_container_add(GTK_CONTAINER(eventbox),label); 

	eventbox = gtk_event_box_new(); 
	g_signal_connect (G_OBJECT (eventbox),"button_press_event", 
			G_CALLBACK (button_press_callback),image); 
	gtk_box_pack_start(GTK_BOX(hbox),eventbox,FALSE,FALSE,15); 
	image = gtk_image_new_from_file("linkicon.gif");//图像链接
	gtk_container_add(GTK_CONTAINER(eventbox),image); 

	gtk_widget_show_all(window); 
	gtk_main(); 
	return FALSE; 
}
