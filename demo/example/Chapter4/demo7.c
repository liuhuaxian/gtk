#include <gtk/gtk.h> 
//以下几个控件定义为全局静态的，以便其他函数来使用或控制它们
static GtkWidget *window; 
static GdkColor color; 
static GtkWidget *drawarea; 
void on_ok_clicked (GtkButton* button,gpointer data) 
{ 
	GtkWidget *dialog ; 
	GtkColorSelection *colorsel; 
	gint response; 
	dialog = gtk_color_selection_dialog_new("选择颜色"); 
	gtk_window_set_transient_for (GTK_WINDOW (dialog), GTK_WINDOW (window)); 
	//注意：转换颜色选择对话框的颜色选择子控件
	colorsel = GTK_COLOR_SELECTION 
		(GTK_COLOR_SELECTION_DIALOG(dialog)->colorsel); 

	gtk_color_selection_set_has_opacity_control(colorsel,TRUE); 
	gtk_color_selection_set_has_palette(colorsel,TRUE); 
	gtk_signal_connect(GTK_OBJECT(dialog),"destroy", 
			GTK_SIGNAL_FUNC(gtk_widget_destroy),&dialog); 

	gtk_color_selection_set_previous_color (colorsel, &color); 
	gtk_color_selection_set_current_color (colorsel, &color); 
	response = gtk_dialog_run(GTK_DIALOG(dialog)); 
	//注意：此处需要用户判断对话框的运行结果，如果是确定按钮则改变颜色
	if(response == GTK_RESPONSE_OK ) 
	{ 
		gtk_color_selection_get_current_color (colorsel, &color); 
		gtk_widget_modify_bg (drawarea, GTK_STATE_NORMAL, &color); 
	} 
	gtk_widget_destroy(dialog); 
} 
int main ( int argc , char* argv[]) 
{ 
	GtkWidget *vbox; 
	GtkWidget *frame; 
	GtkWidget *button; 
	color.red = 0; 
	color.blue = 65535; 
	color.green = 0; 
	gtk_init(&argc,&argv); 
	window = gtk_window_new(GTK_WINDOW_TOPLEVEL); 
	g_signal_connect(G_OBJECT(window),"delete_event", 
			G_CALLBACK(gtk_main_quit),NULL); 
	gtk_window_set_title(GTK_WINDOW(window),"选择颜色"); 
	gtk_window_set_position(GTK_WINDOW(window),GTK_WIN_POS_CENTER); 
	gtk_container_set_border_width(GTK_CONTAINER(window),20); 
	vbox = gtk_vbox_new(FALSE,0); 
	gtk_container_add(GTK_CONTAINER(window),vbox); 
	frame = gtk_frame_new(NULL); 
	gtk_frame_set_shadow_type(GTK_FRAME(frame),GTK_SHADOW_IN); 
	gtk_box_pack_start(GTK_BOX(vbox),frame,TRUE,TRUE,5); 
	drawarea = gtk_drawing_area_new(); 
	gtk_widget_set_size_request(drawarea,200,200);//设定控件的大小
	gtk_widget_modify_bg (drawarea, GTK_STATE_NORMAL, &color); 
	//改变控件正常情况下的背景
	gtk_container_add(GTK_CONTAINER(frame),drawarea); 

	button = gtk_button_new_from_stock(GTK_STOCK_SELECT_COLOR); 
	gtk_box_pack_start(GTK_BOX(vbox),button,FALSE,FALSE,5); 
	g_signal_connect(G_OBJECT(button),"clicked", 
			G_CALLBACK(on_ok_clicked),NULL); 
	gtk_widget_show_all(window); 
	gtk_main(); 
	return FALSE; 
}
