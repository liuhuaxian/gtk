#include <gtk/gtk.h> 
static GtkWidget *main_window; //主窗口
static GtkWidget *sub_window; //子窗口
gboolean ishide = FALSE; //是否隐藏
void on_show (GtkButton* button,gpointer data) 
{ //如果未隐藏则恢复显示，由图标恢复为窗口
	if(ishide ==FALSE) 
		gtk_window_deiconify (GTK_WINDOW(sub_window)); 
	else 
	{//如果隐藏则显示
		gtk_widget_show(sub_window); 
		ishide = FALSE; 
	} 
} 
void on_hide (GtkButton* button,gpointer data) 
{ //图标最小化
	gtk_window_iconify (GTK_WINDOW(sub_window)); 
} 
void on_sub_delete (GtkWidget *window,GdkEvent *event,gpointer 
		data) 
{ //隐藏
	gtk_widget_hide(window); 
	ishide = TRUE; 
} 
GtkWidget* create_main_window () 
{ //创建主窗口
	GtkWidget *window; 
	GtkWidget *hbox; 
	GtkWidget *button; 
	window = gtk_window_new(GTK_WINDOW_TOPLEVEL); 
	g_signal_connect(G_OBJECT(window),"delete_event", 
			G_CALLBACK(gtk_main_quit),NULL); 
	gtk_window_set_title(GTK_WINDOW(window),"主窗口"); 
	gtk_container_set_border_width(GTK_CONTAINER(window),10); 
	hbox = gtk_hbox_new(FALSE,0); 
	gtk_container_add(GTK_CONTAINER(window),hbox); 
	button = gtk_button_new_with_label("显示子窗口"); 
	g_signal_connect(G_OBJECT(button),"clicked", 
			G_CALLBACK(on_show),NULL); 
	gtk_box_pack_start(GTK_BOX(hbox),button,FALSE,FALSE,5); 
	button = gtk_button_new_with_label("隐藏子窗口"); 
	g_signal_connect(G_OBJECT(button),"clicked", 
			G_CALLBACK(on_hide),NULL); 
	gtk_box_pack_start(GTK_BOX(hbox),button,FALSE,FALSE,5); 
	gtk_widget_show_all(window); 
	return window ; 
} 
GtkWidget* create_sub_window () 
{ //创建子窗口
	GtkWidget *window1; 
	GtkWidget *viewport; 
	GtkWidget *label; 
	window1 = gtk_window_new(GTK_WINDOW_TOPLEVEL); 
	g_signal_connect(G_OBJECT(window1),"delete_event", 
			G_CALLBACK(on_sub_delete),window1); 
	gtk_window_set_title(GTK_WINDOW(window1),"子窗口"); 
	gtk_window_set_default_size(GTK_WINDOW(window1),500,100); 
	gtk_window_set_position(GTK_WINDOW(window1),GTK_WIN_POS_CENTER); 
	gtk_container_set_border_width(GTK_CONTAINER(window1),10); 
	viewport = gtk_viewport_new(NULL,NULL); 
	gtk_container_add(GTK_CONTAINER(window1),viewport); 
	label = gtk_label_new("此窗口是子窗口\n它的显示和隐藏可由主窗口控制。"); 
	gtk_container_add(GTK_CONTAINER(viewport),label); 
	gtk_widget_show_all(window1); 
	return window1; 
} 
int main ( int argc , char* argv[]) 
{ 
	gtk_init(&argc,&argv); 
	main_window = create_main_window(); 
	gtk_widget_show(main_window); 
	gtk_window_move(GTK_WINDOW(main_window),0,0);//移动窗口
	sub_window = create_sub_window(); 
	gtk_widget_show(sub_window); 
	gtk_main(); 
	return FALSE; 
}
