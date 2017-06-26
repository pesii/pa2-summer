#include "dmm.h"

int main(void) 
{
	//print_menu();
	// filename: musicPlayList.csv
	//load("musicPlayList.csv");
	Record Data;

	FILE *infile = NULL;
	char line[100], *token, *filename = "musicPlayList.csv";
	
	infile = fopen(filename, "r");
	if(infile == NULL) {
		printf("Error\n");
		exit(1);
	}
	
	char *delim_1 = ",";
	
	/* while(!feof(file)) enters the loop an extra time than I like
	 */
	while (fgets(line,100,infile) != NULL) {
		//fgets(line, 90, infile);
		
		// Artist name field
		token = strtok(line, ",");
		if (token != NULL) {
		
			char *portionNameOne;
			portionNameOne = token;
		
			/* Checks artist name if there's a second delimiter */
			Data.artist = checkArtistName(token);
			if(Data.artist == NULL) {
				Data.artist = portionNameOne;
			}
		}
		
		
		/* Album name field */
		token = strtok(NULL, ",");
		if (token != NULL) {
			Data.album_title = token;
		}
		
		/* Song title field */
		token = strtok(NULL, ",");
		if (token != NULL) {
			Data.song_title = token;
		}

		/* Genre field */
		token = strtok(NULL, ",");
		if (token != NULL) {
			Data.genre = token;
		}
		
		/* Song length field */
		token = strtok(NULL, ":"); // length in minutes
		if (token != NULL) {
			Data.song_length.minutes = atoi(token);
			
			token = strtok(NULL, ","); // length in seconds
			if (token != NULL) {
				Data.song_length.seconds = atoi(token);
			}
		}

		/* Times played field */
		token = strtok(NULL, ",");
		if (token != NULL) {
			Data.times_played = atoi(token);
		}
		
		/* Ratings field */
		token = strtok(NULL, ",");
		if (token != NULL) {
			Data.rating = atoi(token);
		}
		
		insert(Data);
	}
	Node *test;
	test = head;
	Print(test);
	//printf("%s\n", head->Data.artist);
	//head = head->next;
	//printf("%s\n", head->Data.artist);

	/*
	char *test;
	test = concatenate("hi", " there");
	printf("%s\n", test);
	*/
}
