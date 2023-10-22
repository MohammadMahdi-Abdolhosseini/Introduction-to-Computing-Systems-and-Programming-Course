#include <stdio.h>
#include <stdlib.h>

#define ZERO 0
#define ONE 1

typedef struct icsp_student icsp_std;

char* read_line_from_input_file(FILE* input) {
	int line_length = ZERO;
	char* line = (char*)malloc(sizeof(char));
	*(line) = '0';
	char temp_char[1] = {' '};
	while (true) {
		fread(temp_char, sizeof(char), ONE, input);
		line_length++;
		line = (char*)realloc(line, sizeof(char) * line_length);
		line[line_length - ONE] = NULL;
		switch (temp_char[ZERO]){
			case '\n' :
				return line;
				break;
			case EOF : 
				return line;
				break;
			default:
				line[line_length - ONE] = temp_char[ZERO];
				break;
		}	
	}
}

icsp_std** read_students_credentials_from_file(char* file_name) {
	FILE* input;
	if (input = fopen(file_name, "r")) {
		int num_of_lines = atoi(read_line_from_input_file(input));
		icsp_std** students = (icsp_student**)malloc(sizeof(icsp_std*) * num_of_lines);
		for (int i = 0; i < num_of_lines; i++) {
			icsp_std* std = (icsp_std*)malloc(sizeof(icsp_std));
			std->first_name = read_line_from_input_file(input);
			std->last_name = read_line_from_input_file(input);
			std->student_number = read_line_from_input_file(input);
			std->mid_term_exam_score = atof(read_line_from_input_file(input));
			std->final_exam_score = atof(read_line_from_input_file(input));
			std->homework_score = atof(read_line_from_input_file(input));
			// Somthing is missing. find it! <<-----------------------------------------------------------------------------------------------------<<
			students[i] = std;
		}
		fclose(input);
		return students;
	}
	return NULL;
}
