#include "dmm.h"

void print_menu(void)
{
	printf("# # # # # # # # # # # # # \n");
	printf("Digital Music Manager\n");
	printf("# # # # # # # # # # # # # \n\n");

	printf("Options:\n");
	printf("\t1: Load\n");
	printf("\t2: Store\n");
	printf("\t3: Display\n");
	printf("\t4: Insert\n");
	printf("\t5: Delete\n");
	printf("\t6: Edit\n");
	printf("\t7: Sort\n");
	printf("\t8: Rate\n");

	printf("\t9: Play\n");
	printf("\t10: Shuffle\n");
	printf("\t11: Exit\n");

}

void load(char *filename)
{
	FILE *infile = NULL;
	char line[100], *token;
	
	infile = fopen(filename, "r");
	if(infile == NULL) {
		printf("Error\n");
		exit(1);
	}
	
	while (!feof(infile)) {
		fgets(line, 100, infile);
		token = strtok(line, ",");

		char *tmp = strchr(line, '\"');
		if (tmp != NULL) {
			token = strtok(NULL, ",");
			if (token != NULL) 
				printf("%s\n", token);
	
			token = strtok(NULL, ",");
			if (token != NULL) 
				printf("%s\n", token);
	
			token = strtok(NULL, ",");
			if (token != NULL) 
				printf("%s\n", token);		
		} else {
	/*
			if(token != NULL) {
				printf("%s ", token);
			}
		
			token = strtok(NULL, ",");
			if(token != NULL) {
				printf("%s\n", token);
			}
		*/
		}
	}
	
}

