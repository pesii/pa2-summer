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

/* Takes two strings as argument, concatenates them and returns a string
 */
char *concatenate(char *str1, char *str2)
{
	char *joined_string;
	int terminating_char = 1;
	
	// allocates enough space to fit the two strings
	joined_string = malloc( strlen(str1) + strlen(str2) + terminating_char );
	
	strcpy( joined_string, str1 );
	// don't overwrite str1 with str2, but write str2 after str1
	strcpy( joined_string + strlen(str1), str2 );
	
	
	return joined_string;
}

/* Some of this function's code was borrowed from lecture codes called LinkedList3
 * posted on eecs.wsu.edu/~aofallon by the instructor.
 * I'll make my own implementation once I'm comfortable with linked list and dynamic memory
 * Strictly using this implementation to understand the concept a bit better
 * ==================================================================
 * This function allocates memory to store data extracted from a CSV file for the 
 * digital music manager.
 */
Node *createNode(Record newRecord) // borrowed
{
	Node *pMem = NULL; // borrowed
	// Allocate memory for our data
	pMem = (Node *) malloc(sizeof(Node));
	if(pMem != NULL) { // borrowed
		// Store our data to the linked list
		pMem->next = NULL; // This line in particular was borrowed
		pMem->Data.artist = newRecord.artist; // These were not.
		pMem->Data.album_title = newRecord.album_title;
		pMem->Data.song_title = newRecord.song_title;
		pMem->Data.genre = newRecord.genre;
		pMem->Data.song_length.minutes = newRecord.song_length.minutes;
		pMem->Data.times_played = newRecord.times_played;
	}
	
	return pMem; // borrowed
}

void load(char *filename)
{
	Record Data;

	FILE *infile = NULL;
	char line[100], *token;
	
	infile = fopen(filename, "r");
	if(infile == NULL) {
		printf("Error\n");
		exit(1);
	}
	
	char *delim_1 = ",";
	char delim_2 = '\"';
	
	while (!feof(infile)) {
		fgets(line, 90, infile);
		
		// First field
		token = strtok(line, ",");
		if (token != NULL) {
			//printf("%s", token);
		}
		char *portionNameOne;
		portionNameOne = token;
		

		/* Checks if a single field is separated by a comma, then cocatenates the strings
		 * portionName and the new token, else just stores the old token for artist name
		 */
		char *isOneField = strchr(line, delim_2);
		if (isOneField != NULL) {
			// Second portion of the first field for artist name
			token = strtok(NULL, ",");
			if (token != NULL) {
				char *portionNameTwo = concatenate(",", token);
				/* stores artist's fullname in one string */
				Data.artist = concatenate(portionNameOne, portionNameTwo);
			}
		} else {
			Data.artist = portionNameOne;
		}
		
		/* Album name field */
		token = strtok(NULL, ",");
		if (token != NULL) {
			//printf("%s\n", token);
			Data.album_title = token;
		}
		
		/* Song title field */
		token = strtok(NULL, ",");
		if (token != NULL) {
			//printf("%s\n", token);
			Data.song_title = token;
		}

		/* Genre field */
		token = strtok(NULL, ",");
		if (token != NULL) {
			//printf("%s\n", token);
			Data.genre = token;
		}
		
		/* Song length field */
		token = strtok(NULL, ":");
		// first token gets the minutes
		if (token != NULL) {
			//printf("%d\n", atoi(token));
			Data.song_length.minutes = atoi(token);
			
			// second token gets the seconds
			token = strtok(NULL, ",");
			//printf("%d\n\n", atoi(token));
			Data.song_length.seconds = atoi(token);
		}

		/* Times played field */
		token = strtok(NULL, ",");
		if (token != NULL) {
			//printf("%s\n", token);
			Data.times_played = atoi(token);
		}
		
		/* Ratings field */
		token = strtok(NULL, ",");
		if (token != NULL) {
			//printf("%s\n", token);
			Data.rating = atoi(token);
		}
		
		createNode(Data);
		//putchar('\n');
	}

}


/*
	printf("Artist: %s\n", Data.artist);
	printf("Album: %s\n", Data.album_title);
	printf("Song: %s\n", Data.song_title);
	printf("Genre: %s\n", Data.genre);
	printf("Length: %d:", Data.song_length.minutes);
	printf("%d\n", Data.song_length.seconds);
	printf("Times Played: %d\n", Data.times_played);
	printf("Rating: %d\n", Data.rating);
*/


