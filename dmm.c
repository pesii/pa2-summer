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
	Node *newNode; // borrowed
	// Allocate memory for our data
	newNode = malloc(sizeof(*newNode));
	if (newNode != NULL) {
		//Store our data to the linked list
		//newNode->next = NULL; // This line in particular was borrowed
		newNode->Data.artist = newRecord.artist; // These were not.
		newNode->Data.album_title = newRecord.album_title;
		newNode->Data.song_title = newRecord.song_title;
		newNode->Data.genre = newRecord.genre;
		newNode->Data.song_length.minutes = newRecord.song_length.minutes;
		newNode->Data.song_length.seconds = newRecord.song_length.seconds;
		newNode->Data.times_played = newRecord.times_played;
		newNode->Data.rating = newRecord.rating;
	}
	
	
	//newNode->next = malloc(sizeof(*newNode));
	//printf("newNode (addr): %x\n", newNode);
	return newNode; // borrowed
}


void insert(Record Data)
{	
	//Node *mem = NULL;
	if (head == NULL) {
		head = createNode(Data);
		traverse = head;
		//printf("head (addr): %x\n", head);
		//printf("traverse (addr): %x\n", traverse);
		putchar('\n');
	} else {
		traverse->next = createNode(Data);
		traverse = traverse->next;
		//printf("traverse (addr): %x\n\n", traverse);
	}
}


void Print(Node *list)
{
	while(list != NULL) {
	///*
		printf("Artist: %s\n", list->Data.artist);
		printf("Album: %s\n", list->Data.album_title);
		printf("Song: %s\n", list->Data.song_title);
		printf("Genre: %s\n", list->Data.genre);
		printf("Length: %d:", list->Data.song_length.minutes);
		printf("%d\n", list->Data.song_length.seconds);
		printf("Times Played: %d\n", list->Data.times_played);
		printf("Rating: %d\n", list->Data.rating);
	//*/
		//printf("list (addr): %x\n", list);
		list = list->next;
		putchar('\n');
	}
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

void load(char *filename)
{
	

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


