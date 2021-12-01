#include <gtk/gtk.h> 
static GtkWidget *scale1; //滑块一
static GtkWidget *scale2; //滑块二
static GtkWidget *button; //按钮
static GtkWidget *label; //显示进度的标签
static GtkWidget *pbar1; //进度条
static GtkWidget *check, *check1, *check2; //3个多选按钮
static gint i ; 
static gint j ; 
static gdouble p = 0 ; 
gboolean ismode = TRUE; 
//当前滑块一的值改变时执行
void on_scale1_value_changed (GtkScale *scale, gpointer data) 
{ 
	i = (gint)gtk_range_get_value(GTK_RANGE(scale1)); 
	gtk_widget_set_usize(button,i,j); 
} 
//当前滑块二的值改变时执行
void on_scale2_value_changed (GtkScale *scale, gpointer data) 
{ 
	j = (gint)gtk_range_get_value(GTK_RANGE(scale2)); 
	gtk_widget_set_usize(button,i,j); 
} 
//进度开始
void progress_begin (void) 
{ 
	gchar buf[256]; 
	p = p + 0.01; 
	if(p > 1) 
		p = 0; 
	gtk_progress_bar_set_fraction(GTK_PROGRESS_BAR(pbar1),p); 
	//gtk_progress_set_value(GTK_PROGRESS(pbar1),p); 
	sprintf(buf,"此处显示进度状况：%.2f%%",p); 
	gtk_label_set_text(GTK_LABEL(label),buf); 
} 
void on_check (GtkButton *button,gpointer data) 
{ 
	if(GTK_TOGGLE_BUTTON(check)->active) 
		gtk_progress_bar_set_bar_style(GTK_PROGRESS_BAR(pbar1), 
				GTK_PROGRESS_DISCRETE); 
	else 
		gtk_progress_bar_set_bar_style(GTK_PROGRESS_BAR(pbar1), 
				GTK_PROGRESS_CONTINUOUS); 
} 
void on_check_text (GtkButton *button,gpointer data) 
{ 
	if(GTK_TOGGLE_BUTTON(check1)->active) 
		gtk_progress_set_format_string(GTK_PROGRESS(pbar1),"%v"); 
	else 
		gtk_progress_bar_set_text(GTK_PROGRESS_BAR(pbar1),"进度条"); 
} 
void on_check_active (GtkButton *button, gpointer data) 
{ 
	if(GTK_TOGGLE_BUTTON(check2)->active) 
	{ 
		gtk_progress_bar_set_activity_step(GTK_PROGRESS_BAR(pbar1),2); 
		gtk_progress_bar_set_activity_blocks(GTK_PROGRESS_BAR(pbar1),10); 
		gtk_progress_set_activity_mode(GTK_PROGRESS(pbar1),TRUE); 
	} 
	else 
		gtk_progress_set_activity_mode(GTK_PROGRESS(pbar1),FALSE); 
} 
int main ( int argc , char* argv[]) 
{ 
	GtkWidget *window; 
	GtkWidget *vbox, *hbox, *hbox1; 
	GtkWidget *fixed, *sep; 
	gtk_init(&argc,&argv); 
	window = gtk_window_new(GTK_WINDOW_TOPLEVEL); 
	g_signal_connect(G_OBJECT(window),"delete_event", 
			G_CALLBACK(gtk_main_quit),NULL); 
	gtk_window_set_title(GTK_WINDOW(window),"滑块与进度条"); 
	gtk_window_set_position(GTK_WINDOW(window),GTK_WIN_POS_CENTER); 
	gtk_container_set_border_width(GTK_CONTAINER(window),10); 
	hbox = gtk_hbox_new(FALSE,0); 
	gtk_container_add(GTK_CONTAINER(window),hbox); 
	vbox = gtk_vbox_new(FALSE,0); 
	gtk_box_pack_start(GTK_BOX(hbox),vbox,FALSE,FALSE,5); 
	scale1 = gtk_hscale_new_with_range(1,100,1); 
	g_signal_connect(G_OBJECT(scale1),"value_changed", 
			G_CALLBACK(on_scale1_value_changed),NULL); 
	gtk_box_pack_start(GTK_BOX(vbox),scale1,FALSE,FALSE,5); 

	hbox1 = gtk_hbox_new(FALSE,0); 
	gtk_box_pack_start(GTK_BOX(vbox),hbox1,TRUE,TRUE,5); 
	scale2 = gtk_vscale_new_with_range(1,100,1); 
	g_signal_connect(G_OBJECT(scale2),"value_changed", 
			G_CALLBACK(on_scale2_value_changed),NULL); 
	gtk_scale_set_value_pos(GTK_SCALE(scale2),GTK_POS_LEFT); 
	gtk_box_pack_start(GTK_BOX(hbox1),scale2,FALSE,FALSE,5); 
	fixed = gtk_fixed_new(); 
	button = gtk_button_new(); 
	gtk_widget_set_usize(button,100,100); 
	gtk_widget_set_usize(fixed,150,150); 
	gtk_box_pack_start(GTK_BOX(hbox1),fixed,FALSE,FALSE,5); 
	gtk_fixed_put(GTK_FIXED(fixed),button,30,30); 
	sep = gtk_vseparator_new(); 
	gtk_box_pack_start(GTK_BOX(hbox),sep,FALSE,FALSE,5); 
	vbox = gtk_vbox_new(FALSE,0); 
	gtk_box_pack_start(GTK_BOX(hbox),vbox,FALSE,FALSE,5); 
	sep = gtk_label_new("需要用户定义文字显示"); 
	gtk_box_pack_start(GTK_BOX(vbox),sep,FALSE,FALSE,5); 
	label = gtk_label_new("此处显示进度状况："); 
	gtk_box_pack_start(GTK_BOX(vbox),label,FALSE,FALSE,5); 
	pbar1 = gtk_progress_bar_new(); 
	gtk_progress_bar_set_text(GTK_PROGRESS_BAR(pbar1),"进度条"); 
	gtk_timeout_add(200,(GtkFunction)progress_begin,NULL); 
	gtk_box_pack_start(GTK_BOX(vbox),pbar1,FALSE,FALSE,5); 
	check = gtk_check_button_new_with_label("另一种风格"); 
	g_signal_connect(G_OBJECT(check),"clicked", 
			G_CALLBACK(on_check),NULL); 
	gtk_box_pack_start(GTK_BOX(vbox),check,FALSE,FALSE,5); 
	check1 = gtk_check_button_new_with_label("显示动态文字"); 
	g_signal_connect(G_OBJECT(check1),"clicked", 
			G_CALLBACK(on_check_text),NULL); 
	gtk_box_pack_start(GTK_BOX(vbox),check1,FALSE,FALSE,5); 
	check2 = gtk_check_button_new_with_label("活动方式"); 
	g_signal_connect(G_OBJECT(check2),"clicked", 
			G_CALLBACK(on_check_active),NULL); 
	gtk_box_pack_start(GTK_BOX(vbox),check2,FALSE,FALSE,5); 
	gtk_widget_show_all(window); 
	gtk_main(); 
	return FALSE; 
}
