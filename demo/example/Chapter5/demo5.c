#include <gtk/gtk.h> 
//定义列表的列标题
static gchar* titles[5] = {"编号","姓名","性别","出生年月","电子邮件"}; 
const gchar *new_row[5] ;//定义字符串数组指针，指向要向表格中保存的数据
static GtkWidget *clist; //列表
static GtkWidget *add_win; //添加数据窗口
static GtkWidget *entry_id; //编号
static GtkWidget *entry_name; //姓名
static GtkWidget *entry_sex; //性别
static GtkWidget *entry_birthday; //出生年月
static GtkWidget *entry_email; //电子邮件
gint current_row = 0 ; //当前行
gint row_count = 0 ; //总行数
void on_ok_clicked (GtkButton *button,gpointer data) 
{ 
	new_row[0] = gtk_entry_get_text(GTK_ENTRY(entry_id)); 
	new_row[1] = gtk_entry_get_text(GTK_ENTRY(entry_name)); 
	new_row[2] = gtk_entry_get_text(GTK_ENTRY(entry_sex)); 
	new_row[3] = gtk_entry_get_text(GTK_ENTRY(entry_birthday)); 
	new_row[4] = gtk_entry_get_text(GTK_ENTRY(entry_email)); 
	//以上代码取得用户输入
	row_count++; 
	gtk_clist_append(GTK_CLIST(clist),new_row);//向表格中添加
	gtk_widget_destroy(add_win); 
} 
void on_cancel_clicked (GtkButton *button,gpointer data) 
{ 
	gtk_widget_destroy(add_win);//销毁添加数据的窗口
} 
GtkWidget* create_addwin (void) 
{ //创建添加数据窗口
	GtkWidget* win; 
	GtkWidget* vbox; 
	GtkWidget* table; 
	GtkWidget* bbox; 
	GtkWidget* label; 
	GtkWidget* button; 
	win = gtk_window_new(GTK_WINDOW_TOPLEVEL); 
	gtk_window_set_title(GTK_WINDOW(win),"添加记录"); 
	gtk_window_set_position(GTK_WINDOW(win),GTK_WIN_POS_CENTER); 
	g_signal_connect(G_OBJECT(win),"delete_event", 
			G_CALLBACK(gtk_widget_destroy),win); 
	gtk_container_set_border_width(GTK_CONTAINER(win),10); 
	vbox = gtk_vbox_new(FALSE,0); 
	gtk_container_add(GTK_CONTAINER(win),vbox); 
	table = gtk_table_new(5,2,FALSE); 
	gtk_box_pack_start(GTK_BOX(vbox),table,FALSE,FALSE,5); 
	label = gtk_label_new("编号"); 
	gtk_table_attach_defaults(GTK_TABLE(table),label,0,1,0,1); 
	entry_id = gtk_entry_new(); 
	gtk_table_attach_defaults(GTK_TABLE(table),entry_id,1,2,0,1); 

	label = gtk_label_new("姓名"); 
	gtk_table_attach_defaults(GTK_TABLE(table),label,0,1,1,2); 
	entry_name = gtk_entry_new(); 
	gtk_table_attach_defaults(GTK_TABLE(table),entry_name,1,2,1,2); 
	label = gtk_label_new("性别"); 
	gtk_table_attach_defaults(GTK_TABLE(table),label,0,1,2,3); 
	entry_sex = gtk_entry_new(); 
	gtk_table_attach_defaults(GTK_TABLE(table),entry_sex,1,2,2,3); 
	label = gtk_label_new("出生年月"); 
	gtk_table_attach_defaults(GTK_TABLE(table),label,0,1,3,4); 
	entry_birthday = gtk_entry_new(); 
	gtk_table_attach_defaults(GTK_TABLE(table),entry_birthday,1,2,3,
			4); 
	label = gtk_label_new("电子邮件"); 
	gtk_table_attach_defaults(GTK_TABLE(table),label,0,1,4,5); 
	entry_email = gtk_entry_new(); 
	gtk_table_attach_defaults(GTK_TABLE(table),entry_email,1,2,4,5); 
	bbox = gtk_hbutton_box_new(); 
	gtk_box_pack_start(GTK_BOX(vbox),bbox,FALSE,FALSE,5); 
	gtk_box_set_spacing(GTK_BOX(bbox),5); 
	gtk_button_box_set_layout(GTK_BUTTON_BOX(bbox),GTK_BUTTONBOX_END
			); 
	button = gtk_button_new_from_stock(GTK_STOCK_OK); 
	g_signal_connect(G_OBJECT(button),"clicked", 
			G_CALLBACK(on_ok_clicked),NULL); 
	gtk_box_pack_start(GTK_BOX(bbox),button,FALSE,FALSE,5); 
	button = gtk_button_new_from_stock(GTK_STOCK_CANCEL); 
	g_signal_connect(G_OBJECT(button),"clicked", 
			G_CALLBACK(on_cancel_clicked),NULL); 
	gtk_box_pack_start(GTK_BOX(bbox),button,FALSE,FALSE,5); 
	gtk_widget_show_all(win); 
	return win; 
} 
GtkWidget* create_button (gchar* stockid) 
{ //创建带图像的按钮
	GtkWidget *button; 
	GtkWidget *image; 
	image = gtk_image_new_from_stock(stockid,GTK_ICON_SIZE_MENU); 
	button = gtk_button_new(); 
	gtk_container_add(GTK_CONTAINER(button),image); 
	return button; 
} 
void goto_first (GtkButton *button,gpointer data) 
{ //转首行
	current_row = 0 ; 
	gtk_clist_select_row(GTK_CLIST(clist),current_row,0); 
} 
void goto_last (GtkButton *button,gpointer data) 
{ //转尾行
	current_row = row_count-1 ; 
	gtk_clist_select_row(GTK_CLIST(clist),current_row,0); 
} 
void go_back (GtkButton *button,gpointer data) 
{ //前一行
	current_row -- ; 
	if(current_row == -1) return ; 
	gtk_clist_select_row(GTK_CLIST(clist),current_row,0); 
} 
void go_forward (GtkButton *button,gpointer data) 
{ //下一行
	current_row ++; 
	if(current_row > row_count ) return; 
	gtk_clist_select_row(GTK_CLIST(clist),current_row,0); 
} 
void append_row (GtkButton *button,gpointer data) 
{ //添加数据
	add_win = create_addwin(); 
	gtk_widget_show(add_win); 
} 
int main ( int argc , char* argv[]) 
{ 
	GtkWidget *window; 
	GtkWidget *vbox; 
	GtkWidget *bbox; 
	GtkWidget *button; 
	GtkTooltips* button_tips; 
	gtk_init(&argc,&argv); 
	window = gtk_window_new(GTK_WINDOW_TOPLEVEL); 
	g_signal_connect(G_OBJECT(window),"delete_event", 
			G_CALLBACK(gtk_main_quit),NULL); 
	gtk_window_set_title(GTK_WINDOW(window),"列表软件"); 
	gtk_window_set_position(GTK_WINDOW(window),GTK_WIN_POS_CENTER); 
	gtk_container_set_border_width(GTK_CONTAINER(window),10); 
	vbox = gtk_vbox_new(FALSE,0); 
	gtk_container_add(GTK_CONTAINER(window),vbox); 
	clist = gtk_clist_new_with_titles(5,titles); 
	gtk_box_pack_start(GTK_BOX(vbox),clist,TRUE,TRUE,5); 

	bbox = gtk_hbutton_box_new(); 
	button_tips = gtk_tooltips_new(); 
	gtk_box_pack_start(GTK_BOX(vbox),bbox,FALSE,FALSE,5); 
	gtk_box_set_spacing(GTK_BOX(bbox),5); 
	gtk_button_box_set_layout(GTK_BUTTON_BOX(bbox),GTK_BUTTONBOX_END
			); 
	gtk_button_box_set_child_size(GTK_BUTTON_BOX(bbox),20,20); 
	button = create_button(GTK_STOCK_GOTO_FIRST); 
	gtk_tooltips_set_tip(GTK_TOOLTIPS(button_tips),button, 
			"转到首行","首行"); 
	g_signal_connect(G_OBJECT(button),"clicked", 
			G_CALLBACK(goto_first),NULL); 
	gtk_box_pack_start(GTK_BOX(bbox),button,FALSE,FALSE,2); 
	button = create_button(GTK_STOCK_GO_BACK); 
	gtk_tooltips_set_tip(GTK_TOOLTIPS(button_tips),button, 
			"转到前一行","前一行"); 
	g_signal_connect(G_OBJECT(button),"clicked", 
			G_CALLBACK(go_back),NULL); 
	gtk_box_pack_start(GTK_BOX(bbox),button,FALSE,FALSE,2); 
	button = create_button(GTK_STOCK_GO_FORWARD); 
	gtk_tooltips_set_tip(GTK_TOOLTIPS(button_tips),button, 
			"转到下一行","下一行"); 
	g_signal_connect(G_OBJECT(button),"clicked", 
			G_CALLBACK(go_forward),NULL); 
	gtk_box_pack_start(GTK_BOX(bbox),button,FALSE,FALSE,2); 
	button = create_button(GTK_STOCK_GOTO_LAST); 
	gtk_tooltips_set_tip(GTK_TOOLTIPS(button_tips),button, 
			"转到尾行","尾行"); 
	g_signal_connect(G_OBJECT(button),"clicked", 
			G_CALLBACK(goto_last),NULL); 
	gtk_box_pack_start(GTK_BOX(bbox),button,FALSE,FALSE,2); 
	button = create_button(GTK_STOCK_ADD); 
	gtk_tooltips_set_tip(GTK_TOOLTIPS(button_tips),button, 
			"新增一行","新增"); 
	g_signal_connect(G_OBJECT(button),"clicked", 
			G_CALLBACK(append_row),NULL); 
	gtk_box_pack_start(GTK_BOX(bbox),button,FALSE,FALSE,2); 
	button = create_button(GTK_STOCK_QUIT); 
	gtk_tooltips_set_tip(GTK_TOOLTIPS(button_tips),button, 
			"退出","退出"); 
	g_signal_connect(G_OBJECT(button),"clicked", 
			G_CALLBACK(gtk_main_quit),NULL); 
	gtk_box_pack_start(GTK_BOX(bbox),button,FALSE,FALSE,5); 
	gtk_widget_show_all(window); 
	gtk_main(); 
	return FALSE; 
}
