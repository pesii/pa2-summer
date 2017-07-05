#include "dmm.h"

/*
 * Pesi ~ Summer ~ CPTS122
 * All testing/debugging were done exlusively on a linux machine
 * Functionalities that aren't supported on Windows includes 'system("clear")'-type statements and unistd.h header
 * 
 * The goal behind this was to get a working code that satisfies most of the assignment's rubric
 * As a result, little regards were given to assuring efficiency/neatness of code
 */


void print_menu(void)
{
	printf(" _______________________\n");
	printf("| Digital Music Manager |\n");
	printf(" ~~~~~~~~~~~~~~~~~~~~~~~\n\n");

	printf(" _______________________\n");
	printf("| Options: \t\t|\n");
	printf("|\t1: Load \t|\n");
	printf("|\t2: Store \t|\n");
	printf("|\t3: Display \t|\n");
	printf("|\t4: Insert \t|\n");
	printf("|\t5: Delete \t|\n");
	printf("|\t6: Edit \t|\n");
	printf("|\t7: Sort \t|\n");
	printf("|\t8: Rate \t|\n");
	printf("|\t9: Play \t|\n");
	printf("|\t10: Shuffle \t|\n");
	printf("|\t11: Exit \t|\n");
	printf(" ~~~~~~~~~~~~~~~~~~~~~~~\n");
	printf(">>> ");
}

void pause_exec(void)
{
	char c;
	printf("Press ENTER to continue...\n");
	c = getchar();
}

/* Gets user input as a string, validates it, 
 * convert to integer and return the integer 
 */
int input_validation_int(void) 
{
	char user_input_str[10] = {'\0'};
	int user_input_int = 0;
	
	fgets(user_input_str, 10, stdin);
	sscanf(user_input_str, " %d", &user_input_int);
	
	return user_input_int;
}

Bool isListEmpty(Node *list_head)
{
	if (list_head == NULL) {
		return true;
	} else {
		return false;
	}
}

void start_program(void)
{
	int choice = 0, hasLoaded = 0;
	
	Record playlist_data;
	Node *user_defined = NULL, *song = NULL;
	
	while(1) {
		print_menu();
		choice = input_validation_int();
	
		if(choice == LOAD) {
			if(!hasLoaded) {
				// Check is the load function was run before
				load(playlist_data);
				hasLoaded = 1;
				printf("Your paylist is loaded!\n");
			} else {
				printf("The playlist was already loaded!\n");
			}
		
		} else if (choice == STORE) {
			store(head);
		
		} else if (choice == DISPLAY) {
			
			if ( !isListEmpty(head) ) {
				print_node(head, PRINT_ALL);
			} else {
				printf("No playlist loaded... try loading a CSV playlist file!\n");
			}
			
		} else if (choice == INSERT) {
			newRecord();
		
		} else if (choice == DELETE) {
		
		} else if (choice == EDIT) {
			Node *modifiedNode = NULL;
			modifiedNode = get_node_edit(head); // Gets the node corresponding to artist name
			if (modifiedNode != NULL) {
				edit_prompt(modifiedNode);
			}
			
		} else if (choice == SORT) {
		
		} else if (choice == RATE) {
		
		} else if (choice == PLAY) {
			if (head != NULL) {
				print_node(head, PRINT_ALL);
			
				int song_num = 0;
				printf("Which song # do you want to play? ");
				song_num = input_validation_int();
				
				song = get_node_by_num(head, song_num);
				if (song != NULL) {
					play(song);
				}
			} else {
				printf("Your playlist is empty... try loading it!\n");
			}
		
		} else if (choice == SHUFFLE) {
			
		} else if (choice == EXIT) {
			exit_program(head);
		} else {
			printf("Invalid input... try again!\n");
		}
		choice = 0; // resets choice
		pause_exec();
	}
}

void load(Record add_data)
{
	FILE *infile = NULL;
	infile = openFile();
	
	char *token, line[100];

	/* while(!feof(file)) enters the loop an extra time than I like
	 * while(fgets()) does the job better as it exits once it can't read any more lines
	 */
	while (fgets(line,100,infile) != NULL) {

		/* Artist name field */
		token = strtok(line, ",");
		if (token != NULL) {
		
			char *portionNameOne;
			portionNameOne = strdup(token);
		
			/* Checks artist name if there's a second delimiter */
			add_data.artist = checkArtistName(token);
			if(add_data.artist == NULL) {
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
}

int insertRecordFront(Record input_data)
{
	Node *temp = NULL, *traverse = NULL;
	int success = 0;
	
	if (head == NULL) {
		head = createNode(input_data);
		traverse = head;
	} else {
		temp = head;
		head = createNode(input_data);
		head->next = temp;
		
		(head != NULL)?(success=1):(success=0);
	}
	return success;
}

Record newRecord(void)
{
	Record new_data;
	
	printf("Enter a new artist: ");
	new_data.artist = input_validation_str();
	
	printf("Enter a new album title: ");
	new_data.album_title = input_validation_str();
	
	printf("Enter a new song title: ");
	new_data.song_title = input_validation_str();
	
	printf("Enter a new genre: ");
	new_data.genre = input_validation_str();
	
	printf("Song duration\n");
	printf("How many minutes? ");
	new_data.song_length.minutes = input_validation_int();
	
	printf("How many seconds? ");
	new_data.song_length.seconds = input_validation_int();
	
	printf("How many times was the song played? ");
	new_data.times_played = input_validation_int();
	
	printf("What's the song's rating: ");
	new_data.rating = input_validation_int();
	
	insertRecordFront(new_data);
	
}

/* This function allocates memory to store data extracted from a CSV file for the 
 * digital music manager.
 */
 
Node *createNode(Record newRecord) // borrowed
{
	Node *newNode; // borrowed
	// Allocate memory for our data
	newNode = malloc(sizeof(*newNode));
	
	if (newNode != NULL) {
		//Store our data to the linked list
		newNode->Data.artist = newRecord.artist; // These were not.
		newNode->Data.album_title = newRecord.album_title;
		newNode->Data.song_title = newRecord.song_title;
		newNode->Data.genre = newRecord.genre;
		newNode->Data.song_length.minutes = newRecord.song_length.minutes;
		newNode->Data.song_length.seconds = newRecord.song_length.seconds;
		newNode->Data.times_played = newRecord.times_played;
		newNode->Data.rating = newRecord.rating;
		
		newNode->next = head;
	}
	
	return newNode;
}


void print_node(Node *list_index, char print_type)
{
	Node *list = list_index;
	
	if (print_type == PRINT_ALL) {
		int i = 1;
		while(list != NULL) {
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

FILE *openFile(void)
{
	FILE *infile = NULL;
	
	infile = fopen(FILENAME, "r");
	if(infile == NULL) {
		printf("Error\n");
		exit(1);
	}
	
	return infile;
}

/* Takes as argument the head pointer of the linked list
 * then creates a file stream to write all the current records in the Linked List to
 */
int store(Node *linkedList_head) 
{
	Node *indexor = linkedList_head;
	FILE *outFile = NULL;
	int success = 0;
	
	if ( !isListEmpty(linkedList_head) ) {
		outFile = fopen("output.csv", "w");
		// If NULL, exit, otherwise, do nothing and proceed on
		(outFile != NULL) ? :exit(1);
	
		while (indexor != NULL) {
			fprintf(outFile, "%s,%s,%s,%s,%d:%d,%d,%d\n",indexor->Data.artist, indexor->Data.album_title,
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

Node *get_node_by_num(Node *list_head, int node_number)
{
	Node *indexor = NULL;
	int i;
	
	indexor = list_head;
	
	i = 1;
	while(i < node_number) {
		indexor = indexor->next;
		if(indexor == NULL) {
			break;
		}
		i++;
	}
	
	return indexor;
}

char *input_validation_str(void) 
{
	char *return_str;
	char artist_name[50];
	
	fgets(artist_name, 50, stdin);
	
	// Detects if the user pressed ENTER without any input data
	if(strcmp(artist_name, "\n") == 0){
		printf("You didn't enter anything\n");
	}
	
	// Strip newline from stdin
	if(artist_name[strlen(artist_name) - 1] == '\n'){
		artist_name[strlen(artist_name) - 1] = '\0';
	}
	
	return_str = strdup(artist_name);
	
	return return_str;
}

// Find a record by artist
Node *get_node_edit(Node *list_head) 
{
	Node *indexor = NULL, *modified_node = NULL;
	char *artist;
	int isRecordOverOne=0, isArtist=0, singleNode=0, i=0;
	
	indexor = list_head;
	printf("Search artist: ");
	artist = input_validation_str(); // gets artist name
	
	singleNode=0; 
	i=0;
	while (indexor != NULL) {
		i++; // Position of node
		if( strcmp(indexor->Data.artist, artist) == 0 ) {
			++isRecordOverOne;
			
			printf("Record # %d: \"%s\" from the album \"%s\" \n", i, indexor->Data.song_title, indexor->Data.album_title);
			//print_node(indexor, PRINT_ONE);

			singleNode = i;	
			isArtist = 1;
		}
		indexor = indexor->next;
	}
	
	// Determines if there were multiple records of an artist
	if (isRecordOverOne > 1) {
		int tmp = 0;
		printf("Which record number would you like to edit: ");
		tmp = input_validation_int();
		modified_node = get_node_by_num(list_head, tmp);

	} else if (isArtist) {
		modified_node = get_node_by_num(list_head, singleNode);

	} else {
		printf("No such artist in the records\n");

	}
	
	return modified_node;
}

void edit_prompt(Node *edit)
{	
	int attribute_number = 0, duration = 0, tmp = 0;
	char *new_str;
	
	printf("Edit attributes of: \n");
	print_node(edit, PRINT_ONE);
	printf("Specify which attribute number you'd like to edit\n");
	printf("For example, attribute 1 correspond to artist name\n");
	printf("attribute 2 correspond the album title, etc...\n");
	
	printf(">>>");
	attribute_number = input_validation_int();
	
	switch(attribute_number) {
		case 1:
			printf("Enter a new artist name: ");
			new_str = input_validation_str();
			
			strcpy(edit->Data.artist, new_str);
			break;
		case 2:
			printf("Enter a new album title: ");
			new_str = input_validation_str();
			
			strcpy(edit->Data.album_title, new_str);
			break;
		case 3: 
			printf("Enter a new song title: ");
			new_str = input_validation_str();
			
			strcpy(edit->Data.song_title, new_str);
			break;
		case 4:
			printf("Enter a genre: ");
			new_str = input_validation_str();
			
			strcpy(edit->Data.genre, new_str);
			break;
		case 5:
			printf("Enter a new duration\n");
			printf("New minutes: ");
			duration = input_validation_int();
			edit->Data.song_length.minutes = duration;
			
			printf("New seconds: ");
			duration = input_validation_int();
			edit->Data.song_length.seconds = duration;
			
			break;
		case 6:
			printf("Enter a new times played: ");
			tmp = input_validation_int();
			
			edit->Data.times_played = tmp;					
			break;
		case 7:
			rate(edit);
			break;
		default:
			printf("Invalid choice\n");
			break;
	}
	
	
}

void rate(Node *changedNode)
{
	int new_rating = 0;
	char input[4];
	
	printf("Enter a new rating (1-5): ");
	
	fgets(input, 2, stdin);
	sscanf(input, " %d", &new_rating);
	
	switch (new_rating) {
		case 1:
			changedNode->Data.rating = 1;
			break;
		case 2:
			changedNode->Data.rating = 2;
			break;
		case 3:
			changedNode->Data.rating = 3;
			break;
		case 4:
			changedNode->Data.rating = 4;
			break;
		case 5:
			changedNode->Data.rating = 5;
			break;
		default:
			printf("INVALID INPUT: ratings field... no changes made\n");
			break;
	}
}

void play(Node *song)
{
	Node *playlist = song;
	
	while(playlist != NULL) {
		CLEAR_SCREEN;
		printf("Now playing...\n");
		
		print_node(playlist, PRINT_ONE);
		sleep(5);
		playlist = playlist->next;
	}
	free(playlist);
	printf("playlist ended!\n");
	pause_exec();
	
}

int deleteNode(Node *list_head)
{

}

/* Save the LinkedList to output.csv and terminate */
void exit_program(Node *list_root)
{
	printf("Saving list and terminating...\n");
	store(list_root);
	
	exit(0);
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

/* Checks if the field Artist Name is separated  by a comma.
 * If so, it breaks the field into two, then concatenates them,
 * otherwise it returns NULL
 */
char *checkArtistName(char *name) 
{
	char delimiter = '\"';
	char *isOneField, *token;
	
	/* strchr returns NULL if delimiter is NOT in name */
	isOneField = strchr(name, delimiter);
	if (isOneField) { /* If delimiter is in the string */
		// Second portion of the first field for artist name
		token = strtok(NULL, ",");
		if (token != NULL) {
			char *portionNameTwo = concatenate(",", token);
			
			/* Returns artist's fullname in one string */
			return concatenate(name, portionNameTwo);
		}
	} else {
		return NULL;
	}
}


