#include <gtk/gtk.h> 
GtkWidget *da; //定义绘图区以改变光标
/* 这些数据是X bitmap格式的，可以用bitmap实用程序创建 */ 
#define cursor1_width 16 
#define cursor1_height 16 
static unsigned char cursor1_bits[] = { 
	0x80, 0x01, 0x40, 0x02, 0x20, 0x04, 0x10, 0x08, 0x08, 0x10, 0x04, 0x20, 
	0x82, 0x41, 0x41, 0x82, 0x41, 0x82, 0x82, 0x41, 0x04, 0x20, 0x08, 0x10, 
	0x10, 0x08, 0x20, 0x04, 0x40, 0x02, 0x80, 0x01}; 
static unsigned char cursor1mask_bits[] = { 
	0x80, 0x01, 0xc0, 0x03, 0x60, 0x06, 0x30, 0x0c, 0x18, 0x18, 0x8c, 0x31, 
	0xc6, 0x63, 0x63, 0xc6, 0x63, 0xc6, 0xc6, 0x63, 0x8c, 0x31, 0x18, 0x18, 
	0x30, 0x0c, 0x60, 0x06, 0xc0, 0x03, 0x80, 0x01}; 
void on_change (GtkButton* button,gpointer data) 
{ 
	GdkCursor *cursor; /* 定义光标 */ 
	GdkPixmap *source, *mask; 
	GdkColor fg = { 0, 65535, 0, 0 }; /* 前景：红色 */ 
	GdkColor bg = { 0, 0, 0, 65535 }; /* 背景：蓝色 */ 
	//创建GDKPIXMAP图像
	source = gdk_bitmap_create_from_data (NULL, cursor1_bits, 
			cursor1_width, cursor1_height); 
	mask = gdk_bitmap_create_from_data (NULL, cursor1mask_bits, 
			cursor1_width, cursor1_height); 
	//由GDKPIXMAP创建光标
	cursor = gdk_cursor_new_from_pixmap (source, mask, &fg, &bg, 8, 8); 
	gdk_pixmap_unref (source); 
	gdk_pixmap_unref (mask); 
	//设定按钮按钮控件上鼠标的形状
	gdk_window_set_cursor(GTK_WIDGET(button)->window,cursor); 
} 
//当滚动按钮的值变化时执行
void on_spin_value_changed (GtkSpinButton *spin, gpointer data) 
{ 
	GdkCursor *cursor; 
	gint id = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(spin)); 
	cursor = gdk_cursor_new(id);//创建光标
	//设定绘图区的鼠标光标的形状
	gdk_window_set_cursor(GTK_WIDGET(da)->window,cursor); 
} 
int main ( int argc , char* argv[]) 
{ 
	GtkWidget *window; 
	GtkWidget *vbox; 
	GtkWidget *button; 
	GtkWidget *spin; 
	GtkWidget *viewport; 
	gtk_init(&argc,&argv); 
	window = gtk_window_new(GTK_WINDOW_TOPLEVEL); 
	g_signal_connect(G_OBJECT(window),"delete_event", 
			G_CALLBACK(gtk_main_quit),NULL); 
	gtk_window_set_title(GTK_WINDOW(window),"多种样式的光标"); 
	gtk_window_set_position(GTK_WINDOW(window),GTK_WIN_POS_CENTER); 
	gtk_container_set_border_width(GTK_CONTAINER(window),10); 
	vbox = gtk_vbox_new(FALSE,0); 
	gtk_container_add(GTK_CONTAINER(window),vbox); 
	spin = gtk_spin_button_new_with_range(0,152,2); 
	g_signal_connect(G_OBJECT(spin),"value_changed", 
			G_CALLBACK(on_spin_value_changed),NULL); 
	gtk_box_pack_start(GTK_BOX(vbox),spin,FALSE,FALSE,5); 
	da = gtk_drawing_area_new(); 
	gtk_widget_set_size_request(da,100,100); 
	viewport = gtk_viewport_new(NULL,NULL); 
	gtk_container_add(GTK_CONTAINER(viewport),da); 
	gtk_box_pack_start(GTK_BOX(vbox),viewport,FALSE,FALSE,5); 
	button = gtk_button_new_with_label("单击这里改变光标\n这个光标是由自己的资源创建的"); 
	g_signal_connect(G_OBJECT(button),"clicked", 
			G_CALLBACK(on_change),NULL); 
	gtk_box_pack_start(GTK_BOX(vbox),button,FALSE,FALSE,5); 
	button = gtk_button_new_with_label("退出"); 
	gtk_box_pack_start(GTK_BOX(vbox),button,FALSE,FALSE,5); 
	g_signal_connect(G_OBJECT(button),"clicked", 
			G_CALLBACK(gtk_main_quit),NULL); 
	gtk_widget_show_all(window); 
	gtk_main(); 
	return FALSE; 
}
