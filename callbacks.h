#ifndef CALLBACKS_H
#define CALLBACKS_H


typedef struct{
  GtkEntry *entry;
  GtkLabel *label;
}GPT_Entry_Label;


typedef struct{
  GtkStack *stack;
  GtkEntry *entry;
}GPT_STACK_ENTRY;



GPT_Entry_Label* gpt_entry_label_new(GtkEntry *entry, GtkLabel *label);



GPT_STACK_ENTRY* gpt_stack_entry_new(GtkStack *stack, GtkEntry *entry);



void changed_YT_URL_input_callback(GtkEntry *entry);



void clicked_convert_button_switch_stackpage_callback(void *input_data);



void clicked_convert_button_convert_callback(void *input_data);



void clicked_restart_button_callback(GtkStack *stack);


#endif /*CALLBACKS_H*/
