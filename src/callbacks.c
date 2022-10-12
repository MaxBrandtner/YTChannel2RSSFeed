#include <gtk/gtk.h>
#include <string.h>

#include "ip_lookup.h"
#include "algorithms.h"


typedef struct{
  GtkEntry *entry;
  GtkLabel *label;
}GPT_Entry_Label;

typedef struct{
  GtkStack *stack;
  GtkEntry *entry;
}GPT_STACK_ENTRY;

GPT_Entry_Label* gpt_entry_label_new(GtkEntry *entry, GtkLabel *label){
  GPT_Entry_Label *entry_label = (GPT_Entry_Label*)calloc(1, sizeof(GPT_Entry_Label));
  entry_label->entry = entry;
  entry_label->label = label;

  return entry_label;
}


GPT_STACK_ENTRY* gpt_stack_entry_new(GtkStack *stack, GtkEntry *entry){
  GPT_STACK_ENTRY *stack_entry = (GPT_STACK_ENTRY*)calloc(1, sizeof(GPT_STACK_ENTRY));
  stack_entry->stack = stack;
  stack_entry->entry = entry;

  return stack_entry;
}


void changed_YT_URL_input_callback(GtkEntry *entry){
	GtkEntryBuffer *entry_buffer = gtk_entry_get_buffer(GTK_ENTRY(entry));
	char* name_buffer = (char*)gtk_entry_buffer_get_text(GTK_ENTRY_BUFFER(entry_buffer));

	name_buffer = FilterArray(name_buffer);


	GtkEntryBuffer *entry_buffer_filtered = gtk_entry_buffer_new(name_buffer, strlen(name_buffer));

	int entry_position = gtk_editable_get_position(GTK_EDITABLE(entry));
	gtk_entry_set_buffer(GTK_ENTRY(entry), GTK_ENTRY_BUFFER(entry_buffer_filtered));
	gtk_editable_set_position(GTK_EDITABLE(entry), entry_position);

  ip_lookup(entry, name_buffer);
}



void clicked_convert_button_switch_stackpage_callback(void *input_data){
  GPT_STACK_ENTRY *stack_entry = (GPT_STACK_ENTRY*)input_data;
  GtkStack  *stack = stack_entry->stack;
  GtkEntry *entry = stack_entry->entry;
  if(strcmp(gtk_entry_get_icon_name(entry, GTK_ENTRY_ICON_SECONDARY), "emblem-ok-symbolic") == 0){
    gtk_stack_set_visible_child_name(GTK_STACK(stack), "output_box");
  }
}



void clicked_convert_button_convert_callback(void *input_data){
  GPT_Entry_Label *entry_label = (GPT_Entry_Label*)input_data;


  GtkEntry *entry = (GtkEntry*)entry_label->entry;
  GtkLabel *label = entry_label->label;


  GtkEntryBuffer *entry_buffer = gtk_entry_get_buffer(entry);

  char *cmd = calloc(BUFSIZ + 1, sizeof(char));
  strcpy(cmd, "cd ");
  strcat(cmd, LOCAL_DIR);
  strcat(cmd, "src/");
  strcat(cmd, "; bash convert.sh ");

  char *input_text = (char*)gtk_entry_buffer_get_text(GTK_ENTRY_BUFFER(entry_buffer));
  strcat(cmd, input_text);


  char *buffer = calloc(BUFSIZ + 1, sizeof(char));

  FILE *content_buffer = popen(cmd,"r");

  if(content_buffer != NULL){

      fread(buffer, sizeof(char), BUFSIZ, content_buffer);

    gtk_label_set_text(GTK_LABEL(label), buffer);
  }

  pclose(content_buffer);
}



void clicked_restart_button_callback(GtkStack *stack){
  gtk_stack_set_visible_child_name (stack, "selection_box");
}
