#include <gtk/gtk.h> 
#include <stdio.h>
static GtkWidget *notebook; //笔记本控件
static GtkWidget *button_prev; //上一步
static GtkWidget *button_next; //下一步
static GtkWidget *button_finish; //结束
static GtkWidget *button_exit; //退出
GtkWidget* create_button (gchar* title,gchar* stockid) 
{ //创建带图像的按钮
	GtkWidget *button; 
	GtkWidget *image; 
	GtkWidget *label; 
	GtkWidget *hbox; 
	image = gtk_image_new_from_stock(stockid,GTK_ICON_SIZE_MENU); 
	label = gtk_label_new(title); 
	hbox = gtk_hbox_new(FALSE,0); 
	gtk_box_pack_start(GTK_BOX(hbox),image,FALSE,FALSE,3); 
	gtk_box_pack_start(GTK_BOX(hbox),label,FALSE,FALSE,3); 

	button = gtk_button_new(); 
	gtk_container_add(GTK_CONTAINER(button),hbox); 
	return button; 
} 
void create_message_dialog (GtkMessageType type, gchar* message) 
{ //创建信息对话框
	GtkWidget* dialogx; 
	dialogx = gtk_message_dialog_new(NULL, 
			GTK_DIALOG_MODAL | GTK_DIALOG_DESTROY_WITH_PARENT, 
			type, GTK_BUTTONS_OK, message); 
	gtk_dialog_run(GTK_DIALOG(dialogx)); 
	gtk_widget_destroy(dialogx); 
} 
//创建向导的第一个显示页
GtkWidget* create_frame1 (void) 
{ 
	GtkWidget *frame, *vbox, *label; 
	frame = gtk_frame_new(NULL); 
	vbox = gtk_vbox_new(FALSE,0); 
	gtk_frame_set_shadow_type(GTK_FRAME(frame),GTK_SHADOW_ETCHED_OUT
			); 
	gtk_container_add(GTK_CONTAINER(frame),vbox); 
	label = gtk_label_new("欢迎使用本软件！\n本软件是一个......用途的软件，\n主要功能是......\n本软件使用C/C++语言开发，用到......工具库。\n本软件应用平台。\n版权所有：宋国伟 2002年\n联系方式：gwsong52@sohu.com"); 
		gtk_box_pack_start(GTK_BOX(vbox),label,FALSE,FALSE,5); 
	return frame; 
} 
//创建向导的第二个显示页
GtkWidget* create_frame2 (void) 
{ 
	GtkWidget *frame, *vbox, *label; 
	frame = gtk_frame_new(NULL); 
	vbox = gtk_vbox_new(FALSE,0); 
	gtk_frame_set_shadow_type(GTK_FRAME(frame),GTK_SHADOW_ETCHED_OUT
			); 
	gtk_container_add(GTK_CONTAINER(frame),vbox); 
	label = gtk_label_new("本软件遵循GPL2.0协议发行。\n你可以随意分发此软件而不收取任何费用。\n分发此软件时请保证此软件源代码的完整性。\n此软件可以免费用于商业用途。"); 
	gtk_box_pack_start(GTK_BOX(vbox),label,FALSE,FALSE,5); 
	return frame; 
} 
//创建向导的第三个显示页
GtkWidget* create_frame3 (void) 
{ 
	GtkWidget *frame, *vbox, *label, *button; 
	frame = gtk_frame_new(NULL); 
	vbox = gtk_vbox_new(FALSE,0); 
	gtk_container_set_border_width(GTK_CONTAINER(vbox),10); 
	gtk_frame_set_shadow_type(GTK_FRAME(frame),GTK_SHADOW_ETCHED_OUT
			); 
	gtk_container_add(GTK_CONTAINER(frame),vbox); 
	label = gtk_label_new("请选择你要安装的软件包："); 
	gtk_box_pack_start(GTK_BOX(vbox),label,FALSE,FALSE,5); 
	button = gtk_check_button_new_with_label("软件源代码包"); 
	GTK_TOGGLE_BUTTON(button)->active = TRUE; 
	gtk_box_pack_start(GTK_BOX(vbox),button,FALSE,FALSE,5); 
	button = gtk_check_button_new_with_label("软件可执行文件包"); 
	GTK_TOGGLE_BUTTON(button)->active = TRUE; 
	gtk_box_pack_start(GTK_BOX(vbox),button,FALSE,FALSE,5); 
	button = gtk_check_button_new_with_label("软件开发工具包"); 
	GTK_TOGGLE_BUTTON(button)->active = TRUE; 
	gtk_box_pack_start(GTK_BOX(vbox),button,FALSE,FALSE,5); 
	button = gtk_check_button_new_with_label("软件说明文档包"); 
	GTK_TOGGLE_BUTTON(button)->active = TRUE; 
	gtk_box_pack_start(GTK_BOX(vbox),button,FALSE,FALSE,5); 
	return frame; 
} 
//创建向导的第四个显示页
GtkWidget* create_frame4 (void) 
{ 
	GtkWidget *frame, *vbox, *label, *entry; 
	frame = gtk_frame_new("软件安装的路径"); 
	vbox = gtk_vbox_new(FALSE,0); 
	gtk_container_set_border_width(GTK_CONTAINER(vbox),10); 
	gtk_frame_set_shadow_type(GTK_FRAME(frame),GTK_SHADOW_ETCHED_OUT
			); 
	gtk_container_add(GTK_CONTAINER(frame),vbox); 
	label = gtk_label_new("可执行文件路径："); 
	gtk_box_pack_start(GTK_BOX(vbox),label,FALSE,FALSE,3); 
	entry = gtk_entry_new(); 
	gtk_box_pack_start(GTK_BOX(vbox),entry,FALSE,FALSE,3); 
	gtk_entry_set_text(GTK_ENTRY(entry),"~/bin"); 
	label = gtk_label_new("程序库文件路径："); 
	gtk_box_pack_start(GTK_BOX(vbox),label,FALSE,FALSE,3); 
	entry = gtk_entry_new(); 
	gtk_box_pack_start(GTK_BOX(vbox),entry,FALSE,FALSE,3); 
	gtk_entry_set_text(GTK_ENTRY(entry),"~/lib"); 
	label = gtk_label_new("说明文档路径："); 
	gtk_box_pack_start(GTK_BOX(vbox),label,FALSE,FALSE,3); 
	entry = gtk_entry_new(); 
	gtk_box_pack_start(GTK_BOX(vbox),entry,FALSE,FALSE,3); 
	gtk_entry_set_text(GTK_ENTRY(entry),"~/doc"); 
	return frame; 
} 
gboolean run_install (void) 
{ 
	return TRUE;//此处可以根据用户设置运行相关的安装程序
} 
//上一步
void on_button_prev (GtkButton* button,gpointer data) 
{ 
	gint id; 
	id = gtk_notebook_get_current_page(GTK_NOTEBOOK(notebook)); 
	printf("id = %d\n", id);
	if(id == 1) 
	{ 
		gtk_notebook_prev_page(GTK_NOTEBOOK(notebook)); 
		gtk_widget_set_sensitive(button_prev,FALSE); 
	} 
	else 
	{ 
		gtk_widget_set_sensitive(button_next,TRUE); 
		gtk_notebook_prev_page(GTK_NOTEBOOK(notebook)); 
	} 
} 
//下一步
void on_button_next (GtkButton* button,gpointer data) 
{ 
	gint id; 
	id = gtk_notebook_get_current_page(GTK_NOTEBOOK(notebook)); 
	printf("id = %d\n", id);
	if(id == 2) 
	{ 
		gtk_notebook_next_page(GTK_NOTEBOOK(notebook)); 
		gtk_widget_set_sensitive(button_next,FALSE); 
		gtk_widget_set_sensitive(button_finish,TRUE); 
	} 
	else 
	{ 
		gtk_widget_set_sensitive(button_prev,TRUE); 
		gtk_notebook_next_page(GTK_NOTEBOOK(notebook)); 
	} 
} 
//完成
void on_button_finish (GtkButton *button,gpointer data) 
{ 
	if(run_install()) 
		create_message_dialog(GTK_MESSAGE_INFO,"安装成功结束。"); 
	else 
		create_message_dialog(GTK_MESSAGE_ERROR,"安装过程中出错，退出安装！"); 
	gtk_main_quit(); 
} 
void on_button_exit (GtkButton *button,gpointer data) 
{ 
	create_message_dialog(GTK_MESSAGE_WARNING,"安装并未结束，退出此安装程序。"); 
	gtk_main_quit(); 
} 
int main ( int argc , char* argv[]) 
{ 
	GtkWidget *window; 
	GtkWidget *hbox; 
	GtkWidget *vbox; 
	GtkWidget *bbox; 
	GtkWidget *image; 
	GtkWidget *frame; 
	gtk_init(&argc,&argv); 
	window = gtk_window_new(GTK_WINDOW_TOPLEVEL); 
	g_signal_connect(G_OBJECT(window),"delete_event", 
			G_CALLBACK(on_button_exit),NULL); 
	gtk_window_set_title(GTK_WINDOW(window),"安装向导"); 
	gtk_window_set_position(GTK_WINDOW(window),GTK_WIN_POS_CENTER); 
	gtk_container_set_border_width(GTK_CONTAINER(window),10); 
	hbox = gtk_hbox_new(FALSE,0); 
	gtk_container_add(GTK_CONTAINER(window),hbox); 
	image = gtk_image_new_from_file("wizard.png"); 
	gtk_box_pack_start(GTK_BOX(hbox),image,FALSE,FALSE,5); 
	vbox = gtk_vbox_new(FALSE,0); 
	gtk_box_pack_start(GTK_BOX(hbox),vbox,FALSE,FALSE,5); 
	notebook = gtk_notebook_new(); 
	//gtk_notebook_set_show_tabs(GTK_NOTEBOOK(notebook),FALSE);//不显示页头
	gtk_box_pack_start(GTK_BOX(vbox),notebook,TRUE,TRUE,5); 
	frame = create_frame1(); 
	gtk_notebook_append_page(GTK_NOTEBOOK(notebook),frame,NULL); 
	frame = create_frame2(); 
	gtk_notebook_append_page(GTK_NOTEBOOK(notebook),frame,NULL); 
	frame = create_frame3(); 
	gtk_notebook_append_page(GTK_NOTEBOOK(notebook),frame,NULL); 
	frame = create_frame4(); 
	gtk_notebook_append_page(GTK_NOTEBOOK(notebook),frame,NULL); 
	bbox = gtk_hbutton_box_new(); 
	gtk_button_box_set_layout(GTK_BUTTON_BOX(bbox),GTK_BUTTONBOX_END); 
	gtk_box_set_spacing(GTK_BOX(bbox),5); 
	gtk_box_pack_start(GTK_BOX(vbox),bbox,FALSE,FALSE,5); 
	button_prev = create_button("上一步",GTK_STOCK_GO_BACK); 
	gtk_widget_set_sensitive(button_prev,FALSE); 
	g_signal_connect(G_OBJECT(button_prev),"clicked", 
			G_CALLBACK(on_button_prev),NULL); 
	gtk_box_pack_start(GTK_BOX(bbox),button_prev,FALSE,FALSE,5); 
	button_next = create_button("下一步",GTK_STOCK_GO_FORWARD); 
	g_signal_connect(G_OBJECT(button_next),"clicked", 
			G_CALLBACK(on_button_next),NULL); 
	gtk_box_pack_start(GTK_BOX(bbox),button_next,FALSE,FALSE,5); 
	button_finish = gtk_button_new_with_label("完成"); 
	gtk_widget_set_sensitive(button_finish,FALSE); 
	g_signal_connect(G_OBJECT(button_finish),"clicked", 
			G_CALLBACK(on_button_finish),NULL); 
	gtk_box_pack_start(GTK_BOX(bbox),button_finish,FALSE,FALSE,5); 

	button_exit = gtk_button_new_with_label("取消"); 
	g_signal_connect(G_OBJECT(button_exit),"clicked", 
			G_CALLBACK(on_button_exit),NULL); 
	gtk_box_pack_start(GTK_BOX(bbox),button_exit,FALSE,FALSE,5); 
	gtk_widget_show_all(window); 
	gtk_main(); 
	return FALSE; 
}
