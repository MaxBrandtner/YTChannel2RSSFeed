#include <gtk/gtk.h>
#include <string.h>
#include <pthread.h>



typedef struct{
	GtkEntry *entry;
	char *string;
}ip_lookup_parameters;


pthread_mutex_t mutex;


static void* ip_lookup_thread(void* arg){
	pthread_mutex_lock(&mutex);

	ip_lookup_parameters *thread_parameters = arg;
	GtkEntry *entry = (GtkEntry*)thread_parameters->entry;
	char *string = calloc(BUFSIZ + 1, sizeof(char));
	string = (char*)thread_parameters->string;

	char* ip_lookup_cmd = calloc(BUFSIZ + 1, sizeof(char));
	strcpy(ip_lookup_cmd, "curl -L ");
	strcat(ip_lookup_cmd, string);
	strcat(ip_lookup_cmd, " 2>/dev/null | grep channelId > /dev/null");

	int status = system(ip_lookup_cmd);
	if(status == 0){
		gtk_entry_set_icon_from_icon_name(GTK_ENTRY(entry), GTK_ENTRY_ICON_SECONDARY, "emblem-ok-symbolic");
		gtk_entry_set_icon_tooltip_text(GTK_ENTRY(entry), GTK_ENTRY_ICON_SECONDARY, "domain exists");

	}else{
		gtk_entry_set_icon_from_icon_name(GTK_ENTRY(entry), GTK_ENTRY_ICON_SECONDARY, "emblem-important-symbolic");
		gtk_entry_set_icon_tooltip_text(GTK_ENTRY(entry), GTK_ENTRY_ICON_SECONDARY, "invalid URL");
	}

	pthread_mutex_unlock(&mutex);

	return NULL;
}



void ip_lookup(GtkEntry *entry, char* string){
	pthread_t thread_1;
	ip_lookup_parameters *thread_parameters = calloc(1, sizeof(ip_lookup_parameters));
	thread_parameters->entry = entry;
	thread_parameters->string = string;

	pthread_create(&thread_1, NULL, &ip_lookup_thread, thread_parameters);
}



void mutex_init(){
	pthread_mutex_init(&mutex, NULL);
}
