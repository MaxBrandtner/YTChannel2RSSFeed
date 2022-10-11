#include <gtk/gtk.h>
#include <string.h>

#include "ip_lookup.h"
#include "callbacks.h"


#define APPLICATION_ID "com.github.maxbrandtner.YTChannel2RSSFeed"
#define APPLICATION_URI "/com/github/maxbrandtner/YTChannel2RSSFeed/"

#define URI_UI_MAIN APPLICATION_URI "main.ui"



static void app_startup(GApplication *application){
  mutex_init ();
}



static void app_activate(GApplication *application){
	GtkApplication *app = GTK_APPLICATION(application);

	GtkBuilder *main_builder = gtk_builder_new_from_resource(URI_UI_MAIN);

	GtkApplicationWindow *window = GTK_APPLICATION_WINDOW(gtk_builder_get_object(main_builder, "window"));

	gtk_window_set_application(GTK_WINDOW(window), app);


	GtkEntry *YT_URL_input_entry = GTK_ENTRY(gtk_builder_get_object(main_builder, "YT_URL"));

	g_signal_connect_swapped(GTK_WIDGET(YT_URL_input_entry), "changed", G_CALLBACK(changed_YT_URL_input_callback), YT_URL_input_entry);

  GtkButton *convert_button = GTK_BUTTON(gtk_builder_get_object(main_builder, "convert_button"));
  GtkStack *main_stack = GTK_STACK(gtk_builder_get_object(main_builder, "main_stack"));
  GtkBox *output_box = GTK_BOX(gtk_builder_get_object(main_builder, "output_box"));
  GtkBox *selection_box = GTK_BOX(gtk_builder_get_object(main_builder, "selection_box"));
  gtk_stack_add_named(GTK_STACK(main_stack), GTK_WIDGET(selection_box), "selection_box");
  gtk_stack_add_named(GTK_STACK(main_stack), GTK_WIDGET(output_box), "output_box");
  gtk_stack_set_visible_child_name(GTK_STACK(main_stack), "selection_box");

  GtkLabel *yt_rss_url_label = GTK_LABEL(gtk_builder_get_object(main_builder, "output_label"));

  GPT_STACK_ENTRY* convert_button_callback_stack_entry = gpt_stack_entry_new(main_stack, YT_URL_input_entry);
  GPT_Entry_Label* convert_button_callback_entry_label = gpt_entry_label_new (YT_URL_input_entry, yt_rss_url_label);

  g_signal_connect_swapped(GTK_WIDGET(convert_button), "clicked", G_CALLBACK(clicked_convert_button_switch_stackpage_callback), convert_button_callback_stack_entry);
  g_signal_connect_swapped(GTK_WIDGET(convert_button), "clicked", G_CALLBACK(clicked_convert_button_convert_callback), convert_button_callback_entry_label);

  GtkButton *restart_button = GTK_BUTTON(gtk_builder_get_object(main_builder, "restart_button"));

  g_signal_connect_swapped(GTK_BUTTON(restart_button), "clicked", G_CALLBACK(clicked_restart_button_callback), GTK_STACK(main_stack));

	if(!gtk_widget_get_visible(GTK_WIDGET(window))){
		gtk_widget_show(GTK_WIDGET(window));
	}
}



int main(int argc, char** argv){

	GtkApplication *app = gtk_application_new(APPLICATION_ID, G_APPLICATION_NON_UNIQUE);

	g_signal_connect(app, "startup", G_CALLBACK(app_startup), NULL);
	g_signal_connect(app, "activate", G_CALLBACK(app_activate), NULL);

	int status = g_application_run(G_APPLICATION(app), argc, argv);


	g_object_unref(app);

	return status;
}
