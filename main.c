#include "dmm.h"

int main(void) 
{
	//print_menu();
	// filename: musicPlayList.csv
	//load("musicPlayList.csv");
	
	FILE *infile = NULL;
	char *token, *filename = "musicPlayList.csv";
	
	infile = fopen(filename, "r");
	if(infile == NULL) {
		printf("Error\n");
		exit(1);
	}
	
	char line[100];
	Record Data;
	
	char *delim_1 = ",";

	/* while(!feof(file)) enters the loop an extra time than I like
	 * while(fgets()) does the job better as it exits once it can't read any more lines
	 */
	while (fgets(line,100,infile) != NULL) {

		// Artist name field
		token = strtok(line, ",");
		if (token != NULL) {
		
			char *portionNameOne;
			portionNameOne = strdup(token);
		
			/* Checks artist name if there's a second delimiter */
			Data.artist = checkArtistName(token);
			if(Data.artist == NULL) {
				Data.artist = strdup(portionNameOne);
			}
		}
		
		
		/* Album name field */
		token = strtok(NULL, ",");
		if (token != NULL) {
			Data.album_title = strdup(token);
		}
		
		/* Song title field */
		token = strtok(NULL, ",");
		if (token != NULL) {
			Data.song_title = strdup(token);
		}

		/* Genre field */
		token = strtok(NULL, ",");
		if (token != NULL) {
			Data.genre = strdup(token);
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

	Node *browse;
	browse = head;
	Print(browse);
	
	
	
	
	
	
}
