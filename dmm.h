#ifndef MUSIC_MANAGER
#define MUSIC_MANAGER

#include <stdio.h> 	/* printf, scanf, fgets 	*/
#include <stdlib.h> /* malloc, 			*/
#include <string.h> /* strtok, 			*/


void print_menu();
void load();

typedef struct duration {
	int minutes;
	int seconds;
} Duration; 

typedef struct playlist {
	char *artist;
	char *album_title;
	char *song_title;
	char *genre; 
	Duration song_length; 
	int times_played;
	
	// Doubly Linked list previous and next addresses
	struct node *prev;
	struct node *next;
} Playlist; 

#endif
