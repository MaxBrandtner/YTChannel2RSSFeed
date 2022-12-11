#include <stdio.h>
#include <stdlib.h>
#include <string.h>



char* FilterArray(char* input_array){

	int CharCheck(char input){
		int dec_input = (int)input;

		if((dec_input == 45)||(dec_input == 46)||(dec_input == 47)||(dec_input == 58)||(dec_input == 95)||(dec_input >= 48 && dec_input <= 57)||(dec_input >= 65 && dec_input <= 90)||(dec_input >= 97 && dec_input <= 122)||(dec_input == 45)||(dec_input == 95)||(dec_input == 127)||(dec_input == 255)||(dec_input == 64)){

			return 1;
		}else{

			return 0;
		}
	}


	unsigned int invalid_chars = 0;

	char* buffer_array = calloc(strlen(input_array), sizeof(char));


	for(int i = 0; i < strlen(input_array); i ++){
		if(CharCheck(input_array[i]) == 1){
			buffer_array[i - invalid_chars] = input_array[i];

		}else{
			invalid_chars ++;
		}
	}

	return buffer_array;
}
