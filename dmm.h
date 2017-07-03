#ifndef MUSIC_MANAGER
#define MUSIC_MANAGER

#include <stdio.h> 	/* printf, scanf, fgets 	*/
#include <stdlib.h> /* malloc, 			*/
#include <string.h> /* strtok, 			*/
#include <unistd.h>

#define TERMINATING_CHARACTER_SPACE 1
#define PRINT_ALL 'a'
#define PRINT_ONE 'o'
#define FILENAME "musicPlayList.csv"

#define LOAD 1
#define STORE 2
#define DISPLAY 3
#define EDIT 6
#define PLAY 9
#define EXIT 11

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

/* Points to the front of the linked list */
struct node *head;
struct node *traverse;

void print_menu();
void load();
void store();
Node *get_node_edit();
Node *get_node_by_num();
void rate();
void play();
void start_program();
void edit_prompt();
void pause_exec();
int insertFront();
void print_node(Node *, char);

void exit_program();
char *concatenate();
char *checkArtistName();
Node *createNode();


#endif
