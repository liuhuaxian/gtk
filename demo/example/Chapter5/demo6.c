#include <gtk/gtk.h> 
static gchar *title[2] = {"班级","人数"}; 
//表示打开状态的图像数据
static char * book_open_xpm[] = { 
	"16 16 4 1", 
	" c None s None", 
	". c black", 
	"X c #808080", 
	"o c white", 
	" ", 
	" .. ", 
	" .Xo. ... ", 
	" .Xoo. ..oo. ", 
	" .Xooo.Xooo... ", 
	" .Xooo.oooo.X. ", 
	" .Xooo.Xooo.X. ", 
	" .Xooo.oooo.X. ", 
	" .Xooo.Xooo.X. ", 
	" .Xooo.oooo.X. ", 
	" .Xoo.Xoo..X. ", 
	" .Xo.o..ooX. ", 
	" .X..XXXXX. ", 
	" ..X....... ", 
	" .. ", 
	" "}; 
//表示关闭状态的图像数据
static char * book_closed_xpm[] = { 
	"16 16 6 1", 
	" c None s None", 
	". c black", 
	"X c red", 
	"o c yellow", 
	"O c #808080", 
	"# c white", 
	" ", 
	" .. ", 
	" ..XX. ", 
	" ..XXXXX. ", 
	" ..XXXXXXXX. ", 
	".ooXXXXXXXXX. ", 
	"..ooXXXXXXXXX. ", 
	".X.ooXXXXXXXXX. ", 
	".XX.ooXXXXXX.. ", 
	" .XX.ooXXX..#O ", 
	" .XX.oo..##OO. ", 
	" .XX..##OO.. ", 
	" .X.#OO.. ", 
	" ..O.. ", 
	" .. ", 
	" "}; 
//表示最后一级的图像数据
static char * mini_page_xpm[] = { 
	"16 16 4 1", 
	" c None s None", 
	". c black", 
	"X c white", 
	"o c #808080", 
	" ", 
	" ....... ", 
	" .XXXXX.. ", 
	" .XoooX.X. ", 
	" .XXXXX.... ", 
	" .XooooXoo.o ", 
	" .XXXXXXXX.o ", 
	" .XooooooX.o ", 
	" .XXXXXXXX.o ", 
	" .XooooooX.o ", 
	" .XXXXXXXX.o ", 
	" .XooooooX.o ", 
	" .XXXXXXXX.o ", 
	" ..........o ", 
	" oooooooooo ", 
	" "}; 
int main ( int argc , char* argv[]) 
{ 
	GtkWidget *window, *vbox; 
	GdkPixmap *pix1,*pix2,*pix3; 
	GtkWidget *ctree, *button; 
	GtkCTreeNode *parent,*child; 
	gchar *root[2], *text1[2], *text2[2], *sub1[2], *sub2[2], *sub3[2]; 
	root[0] = "一年级"; 
	root[1] = "学生总数：120人"; 
	text1[0] = "女生"; 
	text1[1] = "20人"; 
	text2[0] = "男生"; 
	text2[1] = "20人"; 
	sub1[0] = "一年一班"; 
	sub1[1] = "40人"; 
	sub2[0] = "一年二班"; 
	sub2[1] = "40人"; 
	sub3[0] = "一年三班"; 
	sub3[1] = "40人"; 
	gtk_init(&argc,&argv); 
	window = gtk_window_new(GTK_WINDOW_TOPLEVEL); 
	g_signal_connect(G_OBJECT(window),"delete_event", 
			G_CALLBACK(gtk_main_quit),NULL); 
	gtk_window_set_title(GTK_WINDOW(window),"树状列表"); 
	gtk_window_set_position(GTK_WINDOW(window),GTK_WIN_POS_CENTER); 
	gtk_container_set_border_width(GTK_CONTAINER(window),10); 
	gtk_widget_realize(window);//如此之后即可创建图像
	pix1 = gdk_pixmap_create_from_xpm_d(window->window, 
			NULL,&GTK_WIDGET(window)->style->white,book_open_xpm); 
	pix2 = gdk_pixmap_create_from_xpm_d(window->window, 
			NULL,&GTK_WIDGET(window)->style->white,book_closed_xpm); 
	pix3 = gdk_pixmap_create_from_xpm_d(window->window, 
			NULL,&GTK_WIDGET(window)->style->white,mini_page_xpm); 
	//以上创建三幅图像
	vbox = gtk_vbox_new(FALSE,0); 
	gtk_container_add(GTK_CONTAINER(window),vbox); 
	ctree = gtk_ctree_new_with_titles(2,0,title); 
	gtk_clist_set_column_width(GTK_CLIST(ctree),0,150); 
	gtk_clist_set_column_width(GTK_CLIST(ctree),1,200); 
	gtk_box_pack_start(GTK_BOX(vbox),ctree,TRUE,TRUE,5); 
	parent = gtk_ctree_insert_node(GTK_CTREE(ctree),NULL,NULL,root,5, 
			pix2,NULL,pix1,NULL,FALSE,TRUE);//根节点
	child = gtk_ctree_insert_node(GTK_CTREE(ctree),parent,NULL,sub1,5, 
				pix2,NULL,pix1,NULL,FALSE,TRUE);//子节点一
	gtk_ctree_insert_node(GTK_CTREE(ctree),child,NULL,text1,5, 
			pix3,NULL,NULL,NULL,TRUE,TRUE);//叶一
	gtk_ctree_insert_node(GTK_CTREE(ctree),child,NULL,text2,5, 
			pix3,NULL,NULL,NULL,TRUE,TRUE);//叶二
	child = gtk_ctree_insert_node(GTK_CTREE(ctree),parent,NULL,sub2,5, 
				pix2,NULL,pix1,NULL,FALSE,TRUE);//子节点二
	gtk_ctree_insert_node(GTK_CTREE(ctree),child,NULL,text1,5, 
			pix3,NULL,NULL,NULL,TRUE,TRUE); 
	gtk_ctree_insert_node(GTK_CTREE(ctree),child,NULL,text2,5, 
			pix3,NULL,NULL,NULL,TRUE,TRUE); 
	child = gtk_ctree_insert_node(GTK_CTREE(ctree),parent,NULL,sub3,5, 
				pix2,NULL,pix1,NULL,FALSE,TRUE);//子节点三
	gtk_ctree_insert_node(GTK_CTREE(ctree),child,NULL,text1,5, 
			pix3,NULL,NULL,NULL,TRUE,TRUE); 
	gtk_ctree_insert_node(GTK_CTREE(ctree),child,NULL,text2,5, 
			pix3,NULL,NULL,NULL,TRUE,TRUE); 
	button = gtk_button_new_from_stock(GTK_STOCK_QUIT); 
	g_signal_connect(G_OBJECT(button),"clicked", 
			G_CALLBACK(gtk_main_quit),NULL); 
	gtk_box_pack_start(GTK_BOX(vbox),button,FALSE,FALSE,5); 
	gtk_widget_show_all(window); 
	gtk_main(); 
	return FALSE; 
}
