#include "dmm.h"

/* 
 * This file contains all the functions load, store, display,
 * insert, delete, edit, sort, rate, play, shuffle, exit
 */


void load()
{
	FILE *infile = NULL;
	infile = open_file(FILENAME);
	Record add_data;

	char *token, line[100];

	if (infile != NULL) {
		/* while(!feof(file)) enters the loop an extra time than I like
		* while(fgets()) does the job better as it exits once it can't read any more lines
		*/
		while (fgets(line, 100, infile) != NULL) {

			/* Artist name field */
			token = strtok(line, ",");
			if (token != NULL) {

				char *portionNameOne;
				portionNameOne = strdup(token);

				/* Checks artist name if there's a second delimiter */
				add_data.artist = checkArtistName(token);
				if (add_data.artist == NULL) {
					add_data.artist = strdup(portionNameOne);
				}
			}


			/* Album name field */
			token = strtok(NULL, ",");
			if (token != NULL) {
				add_data.album_title = strdup(token);
			}

			/* Song title field */
			token = strtok(NULL, ",");
			if (token != NULL) {
				add_data.song_title = strdup(token);
			}

			/* Genre field */
			token = strtok(NULL, ",");
			if (token != NULL) {
				add_data.genre = strdup(token);
			}

			/* Song length field */
			token = strtok(NULL, ":"); //<-- length in minutes
			if (token != NULL) {
				add_data.song_length.minutes = atoi(token);

				token = strtok(NULL, ","); //<-- length in seconds
				if (token != NULL) {
					add_data.song_length.seconds = atoi(token);
				}
			}

			/* Times played field */
			token = strtok(NULL, ",");
			if (token != NULL) {
				add_data.times_played = atoi(token);
			}

			/* Ratings field */
			token = strtok(NULL, ",");
			if (token != NULL) {
				add_data.rating = atoi(token);
			}

			insertRecordFront(add_data);
		}

		fclose(infile); // close file
	} else {

		return NULL;
	}
}

/* Takes as argument the head pointer of the linked list
* then creates a file stream to write all the current records in the Linked List to
*/
int store(Node *linkedList_head)
{
	Node *indexor = linkedList_head;
	FILE *outFile = NULL;
	int success = 0;

	if (!isListEmpty(linkedList_head)) {
		outFile = fopen("output.csv", "w");
		// If NULL, exit, otherwise, do nothing and proceed on
		if (outFile == NULL) {
			exit(1);
		}

		while (indexor != NULL) {
			fprintf(outFile, "%s,%s,%s,%s,%d:%d,%d,%d\n", indexor->Data.artist, indexor->Data.album_title,
				indexor->Data.song_title, indexor->Data.genre,
				indexor->Data.song_length.minutes, indexor->Data.song_length.seconds,
				indexor->Data.times_played, indexor->Data.rating);

			indexor = indexor->next;
		}
		fclose(outFile);

		success = 1;
		return success;
	} else {
		return success;
	}
}

void print_node(Node *list_index, char print_type)
{
	Node *list = list_index;

	if (print_type == PRINT_ALL) {
		int i = 1;
		while (list != NULL) {
			printf("Song %d:\n", i);
			printf("\t1. Artist: %s\n", list->Data.artist);
			printf("\t2. Album: %s\n", list->Data.album_title);
			printf("\t3. Song: %s\n", list->Data.song_title);
			printf("\t4. Genre: %s\n", list->Data.genre);
			printf("\t5. Length: %d:", list->Data.song_length.minutes);
			printf("%d\n", list->Data.song_length.seconds);
			printf("\t6. Times Played: %d\n", list->Data.times_played);
			printf("\t7. Rating: %d\n", list->Data.rating);

			list = list->next;
			putchar('\n');
			i++;
		}
	} else if (print_type == PRINT_ONE) {
		printf("\t1. Artist: %s\n", list->Data.artist);
		printf("\t2. Album: %s\n", list->Data.album_title);
		printf("\t3. Song: %s\n", list->Data.song_title);
		printf("\t4. Genre: %s\n", list->Data.genre);
		printf("\t5. Length: %d:", list->Data.song_length.minutes);
		printf("%d\n", list->Data.song_length.seconds);
		printf("\t6. Times Played: %d\n", list->Data.times_played);
		printf("\t7. Rating: %d\n", list->Data.rating);
	} else {
		printf("Failed to select a print type\n");
	}
}

/* Save the LinkedList to output.csv and terminate */
void exit_program(Node *list_root)
{
	printf("Saving list and terminating...\n");
	store(list_root);

	exit(0);
}

void play(Node *song)
{
	Node *playlist = song;

	while (playlist != NULL) {
		CLEAR_SCREEN;
		printf("Now playing...\n");

		print_node(playlist, PRINT_ONE);
		Sleep(5000);
		playlist = playlist->next;
	}
	free(playlist);
	printf("playlist ended!\n");
	pause_exec();

}

void rate(Node *changedNode)
{
	int new_rating = 0;
	char input[4];

	printf("Enter a new rating (1-5): ");

	new_rating = input_validation_int();
	if ((new_rating <= 5) && (new_rating >= 1)) {
		changedNode->Data.rating = new_rating;
	} else {
		printf("INVALID INPUT: ratings field... no changes made\n");
	}
}

