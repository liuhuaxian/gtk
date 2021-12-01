#include <stdio.h>
#include <glib.h>

gboolean print(gpointer data)
{
	static int i = 1;

	if(i > 5)
		return FALSE;

	printf("-----i=[%d]\n", i++);
	return FALSE;
//	return TRUE;
}

gboolean terminal(gpointer data)
{
	GMainLoop *loop = data;

	printf("Before Quit-----------[%d]\n", g_main_loop_is_running(loop)); 

	g_main_loop_quit(loop);        
}

gboolean say_hello(gpointer data)
{  
	printf("Hello, %s\n", data);   
	return FALSE;     
}                         

gboolean say_goodbye(gpointer data)
{
	printf("Goodbye, %s\n", data); 
	//      return TRUE;
	return FALSE;
}


int main(int argc, char *argv[])
{
	GMainLoop *loop = g_main_loop_new(NULL, FALSE);

	g_timeout_add(500, print, NULL);
	g_timeout_add(5000, terminal, loop);

	g_idle_add(say_hello, "Li Lei");
	g_idle_add(say_goodbye, "Li Lei");

	g_main_loop_run(loop);

	printf("After loop------[%d]--\n", g_main_loop_is_running(loop));


	return 0;
}
