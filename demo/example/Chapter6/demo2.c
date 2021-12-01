#include <gtk/gtk.h> 
enum { 
	ID_COLUMN, //标号 -- 数字类型
	TOGGLE_COLUMN, //按钮 -- 按钮类型
	TEXT_COLUMN, //文字 -- 文本类型
	N_COLUMN //最后一项
};//定义枚举表示列项

typedef struct _listitem ListItem; 
struct _listitem{ 
	gint id; 
	gboolean toggle; 
	const gchar* text; 
};//定义每一行的数据结构

ListItem t[5] = {{1,TRUE,"小明"},{2,FALSE,"大宝"},{3,TRUE,"测试用名称"},{4,FALSE,"显示的文本"},{5,TRUE,"是可编辑的"} };//定义保存到表格中的数据

GtkListStore* create_list_model ( void ) //创建表格模型
{ 
	GtkListStore *list_store; 
	GtkTreeIter iter; 
	gint i; 
	//创建列表显示模型
	list_store = gtk_list_store_new(N_COLUMN, G_TYPE_INT, 
			G_TYPE_BOOLEAN,G_TYPE_STRING); 
	for(i=0;i<5;i++) 
	{ //向列表显示模型中添加数据
		gtk_list_store_append(list_store,&iter); 
		gtk_list_store_set(list_store,&iter, 
				ID_COLUMN,t[i].id, 
				TOGGLE_COLUMN,t[i].toggle, 
				TEXT_COLUMN,t[i].text,-1); 
	} 
	return list_store; 
}

GtkWidget* create_list (GtkListStore *list_store) 
{ 
	GtkWidget *view; 
	GtkTreeModel* model; 
	GtkCellRenderer *renderer; 
	GtkTreeViewColumn *column; 
	//创建列表显示
	model = GTK_TREE_MODEL(list_store); 
	view = gtk_tree_view_new_with_model(model); 
	renderer = gtk_cell_renderer_text_new();//创建文本型单元格
	column = gtk_tree_view_column_new_with_attributes( 
			"数字",renderer,"text",ID_COLUMN,NULL);//创建列
	gtk_tree_view_append_column(GTK_TREE_VIEW(view),column);//添加列
	renderer = gtk_cell_renderer_toggle_new();//创建按钮型单元格
	g_object_set(G_OBJECT(renderer),"activatable",TRUE);//可按
	gtk_cell_renderer_toggle_set_radio(GTK_CELL_RENDERER_TOGGLE(renderer),TRUE);//为单选按钮
	column = gtk_tree_view_column_new_with_attributes( 
			"按钮",renderer,"active",TOGGLE_COLUMN,NULL);//创建列
	gtk_tree_view_append_column(GTK_TREE_VIEW(view),column);//添加
	renderer = gtk_cell_renderer_text_new(); 
	g_object_set(G_OBJECT(renderer),"editable",TRUE);//可编辑
	column = gtk_tree_view_column_new_with_attributes( 
			"文本",renderer,"text",TEXT_COLUMN,NULL); 
	gtk_tree_view_append_column(GTK_TREE_VIEW(view),column); 
	return view; 
}

void show_list (void) 
{ //显示列表
	GtkWidget *window; 
	GtkWidget *frame; 
	GtkWidget *view; 
	GtkListStore *model; 
	window = gtk_window_new(GTK_WINDOW_TOPLEVEL); 
	g_signal_connect(G_OBJECT(window),"destroy", 
			G_CALLBACK(gtk_widget_destroy),window); 
	gtk_window_set_title(GTK_WINDOW(window),"TREEVIEW -- 使用LISTSTORE"); 
	gtk_window_set_position(GTK_WINDOW(window),GTK_WIN_POS_CENTER); 
	gtk_container_set_border_width(GTK_CONTAINER(window),10); 
	frame = gtk_frame_new("可编辑的列表"); 
	gtk_frame_set_label_align(GTK_FRAME(frame),1.0,0); 
	gtk_container_add(GTK_CONTAINER(window),frame); 
	model = create_list_model(); 
	view = create_list(model); 
	gtk_container_add(GTK_CONTAINER(frame),view); 
	gtk_widget_show_all(window); 
}

enum { 
	XCLASS_COLUMN, //班级
	LEADER_COLUMN, //班主任
	STUDENTS_COLUMN, //学生数
	GIRLS_COLUMN //女学生
};//定义树型列表项

typedef struct _treeitem TreeItem; 
struct _treeitem { 
	const char* xclass; 
	const char* leader; 
	gint students; 
	gint girls; 
};//定义树型列表显示的数据结构

TreeItem ti[3] = {{"一年级一班","李晓",40,20},{"一年级二班","张宏",44,18}, 
	{"一年级三班","刘丽",42,20}};//定义树型列表显示的数据

TreeItem tj[3] = {{"二年级一班","王可",34,16},{"二年级二班","赵前",34,18},{"一年级三班","由苛",38,20}};//定义树型列表显示的数据

GtkTreeStore* create_tree_model (void) 
{ 
	GtkTreeStore* treestore; 
	GtkTreeIter iter,parent; 
	gint i; 
	//创建树型显示模型
	treestore = gtk_tree_store_new(4,G_TYPE_STRING,G_TYPE_STRING, 
			G_TYPE_INT,G_TYPE_INT); 
	gtk_tree_store_append(treestore,&iter,NULL); 
	gtk_tree_store_set(treestore,&iter,0,"一年级",2,100,-1); 
	gtk_tree_store_append(treestore,&iter,NULL); 
	gtk_tree_store_set(treestore,&iter,0,"二年级",-1); 
	if(gtk_tree_model_get_iter_from_string(GTK_TREE_MODEL(treestore), &parent,"0")) 
		for(i=0; i<3; i++) 
		{ 
			gtk_tree_store_append(treestore,&iter,&parent); 
			gtk_tree_store_set(treestore,&iter, 
					XCLASS_COLUMN,ti[i].xclass, 
					LEADER_COLUMN,ti[i].leader, 
					STUDENTS_COLUMN,ti[i].students, 
					GIRLS_COLUMN,ti[i].girls,-1); 
		} 
	if(gtk_tree_model_get_iter_from_string(GTK_TREE_MODEL(treestore), &parent,"1")) 
		for(i=0; i<3; i++) 
		{ 
			gtk_tree_store_append(treestore,&iter,&parent); 
			gtk_tree_store_set(treestore,&iter, 
					XCLASS_COLUMN,tj[i].xclass, 
					LEADER_COLUMN,tj[i].leader, 
					STUDENTS_COLUMN,tj[i].students, 
					GIRLS_COLUMN,tj[i].girls,-1); 
		} 
	return treestore; 
} 
GtkWidget* create_tree (GtkTreeStore* treestore) 
{ 
	GtkWidget* view; 
	GtkCellRenderer *renderer; 
	GtkTreeViewColumn *column; 
	view = gtk_tree_view_new_with_model(GTK_TREE_MODEL(treestore)); 
	renderer = gtk_cell_renderer_text_new(); 
	column = gtk_tree_view_column_new_with_attributes( 
			"班级名称",renderer,"text",XCLASS_COLUMN,NULL); 
	gtk_tree_view_append_column(GTK_TREE_VIEW(view),column); 
	renderer = gtk_cell_renderer_text_new(); 
	column = gtk_tree_view_column_new_with_attributes( 
			"班主任",renderer,"text",LEADER_COLUMN,NULL); 
	gtk_tree_view_append_column(GTK_TREE_VIEW(view),column); 
	renderer = gtk_cell_renderer_text_new(); 
	column = gtk_tree_view_column_new_with_attributes( 
			"学生总数",renderer,"text",STUDENTS_COLUMN,NULL); 
	gtk_tree_view_append_column(GTK_TREE_VIEW(view),column); 
	renderer = gtk_cell_renderer_text_new(); 
	column = gtk_tree_view_column_new_with_attributes( 
			"女学生数",renderer,"text",GIRLS_COLUMN,NULL); 
	gtk_tree_view_append_column(GTK_TREE_VIEW(view),column); 
	return view; 
} 

void show_tree (void) 
{ 
	GtkWidget *window; 
	GtkWidget *frame; 
	GtkWidget *view; 
	GtkTreeStore *model; 
	window = gtk_window_new(GTK_WINDOW_TOPLEVEL); 
	g_signal_connect(G_OBJECT(window),"destroy", 
			G_CALLBACK(gtk_widget_destroy),window); 
	gtk_window_set_title(GTK_WINDOW(window),"TREEVIEW -- 使用TreeStore"); 
	gtk_window_set_position(GTK_WINDOW(window),GTK_WIN_POS_CENTER); 
	gtk_container_set_border_width(GTK_CONTAINER(window),10); 
	frame = gtk_frame_new("树型列表"); 
	gtk_container_add(GTK_CONTAINER(window),frame); 
	model = create_tree_model(); 
	view = create_tree(model); 
	gtk_container_add(GTK_CONTAINER(frame),view); 
	gtk_widget_show_all(window); 
}

int main ( int argc , char* argv[]) 
{ 
	GtkWidget *window,*vbox,*button; 
	gtk_init(&argc,&argv); 
	window = gtk_window_new(GTK_WINDOW_TOPLEVEL); 
	gtk_window_set_title(GTK_WINDOW(window),"TREEVIEW控件"); 
	g_signal_connect(G_OBJECT(window),"delete_event", 
			G_CALLBACK(gtk_main_quit),NULL); 
	vbox = gtk_vbox_new(FALSE,0); 
	gtk_container_add(GTK_CONTAINER(window),vbox); 
	button = gtk_button_new_with_label("创建列表显示"); 
	gtk_box_pack_start(GTK_BOX(vbox),button,FALSE,FALSE,5); 
	g_signal_connect(G_OBJECT(button),"clicked", 
			G_CALLBACK(show_list),NULL); 
	button = gtk_button_new_with_label("创建树型显示"); 
	gtk_box_pack_start(GTK_BOX(vbox),button,FALSE,FALSE,5); 
	g_signal_connect(G_OBJECT(button),"clicked", 
			G_CALLBACK(show_tree),NULL); 
	gtk_widget_show_all(window); 
	gtk_main(); 
	return FALSE; 
}
