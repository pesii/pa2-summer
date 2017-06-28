#ifndef MUSIC_MANAGER
#define MUSIC_MANAGER

#include <stdio.h> 	/* printf, scanf, fgets 	*/
#include <stdlib.h> /* malloc, 			*/
#include <string.h> /* strtok, 			*/

#define TERMINATING_CHARACTER_SPACE 1

typedef struct duration 
{
	int minutes;
	int seconds;
} Duration;

typedef struct record 
{
	char *artist;
	char *album_title;
	char *song_title;
	char *genre;
	Duration song_length;
	int times_played;
	int rating;
} Record;

typedef struct node
{
	Record Data;
	//Pointers to previous and next node
	struct node *prev;
	struct node *next;
} Node;


struct node *head;
struct node *traverse;
struct node *test;


void print_menu();
void load();
void insert();
void display();
char *concatenate();
char *checkArtistName();
Node *createNode();


#endif
