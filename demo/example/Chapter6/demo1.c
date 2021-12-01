#include <gtk/gtk.h> 
//创建信息对话框函数
void create_message_dialog (GtkMessageType type, gchar* message) 
{ 
	GtkWidget* dialogx; 
	dialogx = gtk_message_dialog_new(NULL, 
			GTK_DIALOG_MODAL | GTK_DIALOG_DESTROY_WITH_PARENT, 
			type ,GTK_BUTTONS_OK,message); 
	gtk_dialog_run(GTK_DIALOG(dialogx)); 
	gtk_widget_destroy(dialogx); 
} 
void on_button_clicked (GtkButton* button, gpointer data) 
{ 
	create_message_dialog(GTK_MESSAGE_INFO, 
			"这是由TEXTVIEW中的按钮触发的对话框。"); 
} 
int main ( int argc , char* argv[]) 
{ 
	GtkWidget *window, *scwin; 
	GtkWidget *vpaned, *view1, *view2; 
	GtkWidget *image, *button; 
	GdkPixbuf *pixbuf1, *pixbuf2, *pixbuf3, *pixbuf4; 
	GtkTextBuffer *buffer; 
	GtkTextIter start, end; 
	GtkTextChildAnchor *anchor; 
	gtk_init(&argc,&argv); 
	window = gtk_window_new(GTK_WINDOW_TOPLEVEL); 
	g_signal_connect(G_OBJECT(window),"delete_event", 
			G_CALLBACK(gtk_main_quit),NULL); 
	gtk_window_set_title(GTK_WINDOW(window),"使用textview控件"); 
	gtk_window_set_default_size(GTK_WINDOW(window),300,200); 
	gtk_window_set_position(GTK_WINDOW(window),GTK_WIN_POS_CENTER); 
	gtk_container_set_border_width(GTK_CONTAINER(window),10); 
	vpaned = gtk_vpaned_new(); 
	gtk_container_add(GTK_CONTAINER(window),vpaned); 
	//创建滚动窗口，并设定滚动条为自动显示
	scwin = gtk_scrolled_window_new(NULL,NULL); 
	gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(scwin), 
			GTK_POLICY_AUTOMATIC,GTK_POLICY_AUTOMATIC); 
	view1 = gtk_text_view_new(); 
	gtk_paned_add1(GTK_PANED(vpaned),scwin); 
	gtk_container_add(GTK_CONTAINER(scwin),view1); 
	//gtk_text_view_set_left_margin (GTK_TEXT_VIEW (view1), 30); 
	pixbuf1 = gdk_pixbuf_new_from_file("p1.bmp",NULL);//创建图像资源
	pixbuf2 = gdk_pixbuf_new_from_file("p2.bmp",NULL); 
	pixbuf3 = gdk_pixbuf_new_from_file("p3.bmp",NULL); 
	pixbuf4 = gdk_pixbuf_new_from_file("p4.bmp",NULL); 
	image = gtk_image_new_from_file("pp.gif"); //创建图像控件显示动画
	buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(view1)); 
	//取得文本显示的缓冲区
	gtk_text_buffer_create_tag(buffer, "blue_foreground", 
			"foreground", "blue", NULL);//创建前景标记
	gtk_text_buffer_create_tag(buffer, "yellow_background", 
			"background","yellow",NULL);//创建背景标记
	gtk_text_buffer_create_tag(buffer, "simhei", "family", "Simhei", 
			NULL); 
	gtk_text_buffer_create_tag(buffer, "sans", "family", "Sans",NULL); 
	//以上两行创建字体标记
	gtk_text_buffer_create_tag (buffer, "wide_margins", 
			"left_margin", 50, "right_margin", 50,NULL);//边距标记
	gtk_text_buffer_create_tag (buffer, "heading", 
			"justification",GTK_JUSTIFY_LEFT,NULL);//居左
	gtk_text_buffer_create_tag (buffer, "no_wrap", 
			"wrap_mode", GTK_WRAP_NONE, NULL);//不换行
	gtk_text_buffer_create_tag (buffer, "word_wrap", 
			"wrap_mode", GTK_WRAP_WORD, NULL);//以词为单位换行
	gtk_text_buffer_create_tag(buffer, "center", 
			"justification", GTK_JUSTIFY_CENTER, NULL);//居中
	gtk_text_buffer_create_tag(buffer, "right_justify", 
			"justification", GTK_JUSTIFY_RIGHT, NULL);//居右
	gtk_text_buffer_get_end_iter(buffer,&end); 
	gtk_text_buffer_insert(buffer,&end,"这是一段正常的文字。",-1); 
	//从此处开始带标记插入文字
	gtk_text_buffer_get_end_iter(buffer,&end); 
	gtk_text_buffer_insert_with_tags_by_name(buffer,&end,"这是一段设了标记的文字。\n",-1,"blue_foreground",NULL); 
	gtk_text_buffer_get_end_iter(buffer,&end); 
	gtk_text_buffer_insert_with_tags_by_name(buffer,&end,"这是一段背景是黄色的文字。", -1, "yellow_background",NULL); 
	gtk_text_buffer_get_end_iter(buffer,&end); 
	gtk_text_buffer_insert_with_tags_by_name(buffer,&end,"而这段是黑体字。\n",-1,"simhei",NULL); 
	gtk_text_buffer_get_end_iter(buffer,&end); 
	gtk_text_buffer_insert_with_tags_by_name(buffer,&end,"这一段文字是不换行的，所以它会使滚动条变长，不过这不影响程序的运行。",-1,"no_wrap",NULL); 
	gtk_text_buffer_get_end_iter(buffer,&end); 
	gtk_text_buffer_insert_with_tags_by_name(buffer,&end,"\n我们还可以向其中插入一大段文字，如下面这首诗：\n蓬头稚子学垂纶，侧坐莓苔草映身。路人借问遥招手，怕得鱼惊不应人。",-1,"wide_margins","word_wrap","center",NULL); 
	gtk_text_buffer_get_end_iter(buffer,&end); 
	gtk_text_buffer_insert_with_tags_by_name(buffer,&end,"\n这段文字是居左的；\n",-1,"wide_margins","heading","word_wrap",NULL); 
	gtk_text_buffer_get_end_iter(buffer,&end); 
	gtk_text_buffer_insert_with_tags_by_name(buffer,&end,"这段文字是居中的；\n",-1,"wide_margins","center","word_wrap",NULL); 
	gtk_text_buffer_get_end_iter(buffer,&end); 
	gtk_text_buffer_insert_with_tags_by_name(buffer,&end,"这段文字则是居右的。\n",-1,"wide_margins","right_justify","word_wrap",NULL); 
	gtk_text_buffer_get_end_iter(buffer,&end); 
	gtk_text_buffer_insert(buffer,&end,"这是四幅图像，由GDKPIXBUF资源创建的", -1); 
	gtk_text_buffer_get_end_iter(buffer,&end); 
	gtk_text_buffer_insert_pixbuf(buffer,&end,pixbuf1);//此处插入图像资源
	gtk_text_buffer_get_end_iter(buffer,&end); 
	gtk_text_buffer_insert_pixbuf(buffer,&end,pixbuf2); 
	gtk_text_buffer_get_end_iter(buffer,&end); 
	gtk_text_buffer_insert_pixbuf(buffer,&end,pixbuf3); 
	gtk_text_buffer_get_end_iter(buffer,&end); 
	gtk_text_buffer_insert_pixbuf(buffer,&end,pixbuf4); 
	gtk_text_buffer_get_end_iter(buffer,&end); 
	gtk_text_buffer_insert_with_tags_by_name(buffer,&end,"\n这段文字则用了三种标记。\n",-1,"blue_foreground","yellow_background","simhei",NULL); 
	gtk_text_buffer_get_end_iter(buffer,&end); 
	gtk_text_buffer_insert(buffer,&end,"这是一幅动画，它是以子控件形式出现的",-1); 
	anchor = gtk_text_buffer_create_child_anchor(buffer,&end); 
	//创建子控件的位置标记
	gtk_text_view_add_child_at_anchor(GTK_TEXT_VIEW(view1),image,anchor); 
	//向文本视图控件中添加控件
	gtk_text_buffer_get_end_iter(buffer,&end); 
	gtk_text_buffer_insert(buffer,&end,"\n其它控件也一样加入，如这个按钮",-1); 
	anchor = gtk_text_buffer_create_child_anchor(buffer,&end); 
	button = gtk_button_new_with_label("点击显示对话框"); 
	g_signal_connect(G_OBJECT(button),"clicked", 
			G_CALLBACK(on_button_clicked),NULL); 
	gtk_text_view_add_child_at_anchor(GTK_TEXT_VIEW(view1),button,anchor); 
	scwin = gtk_scrolled_window_new(NULL,NULL); 
	gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(scwin), 
			GTK_POLICY_AUTOMATIC,GTK_POLICY_AUTOMATIC); 
	//创建第二个滚动窗口
	view2 = gtk_text_view_new_with_buffer(buffer);//创建第二个文本视图控件
	gtk_paned_add2(GTK_PANED(vpaned),scwin); 
	gtk_container_add(GTK_CONTAINER(scwin),view2); 
	gtk_widget_show_all(window); 
	gtk_main(); 
	return FALSE; 
}
