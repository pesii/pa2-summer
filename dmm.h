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

#define CLEAR_SCREEN system("clear")

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

typedef enum boolean
{
	false, true
} Bool;



void print_menu();
void print_node(Node *, char);

Node *get_node_edit();
Node *get_node_by_num();
Bool isListEmpty(Node *list_head);
void pause_exec();
void load();
void store();
void rate();
void play();
void start_program();
void edit_prompt();
int insertFront();

int input_validation_int();
char *input_validation_str();

FILE *openFile();
void exit_program();
char *concatenate();
char *checkArtistName();
Node *createNode();


#endif
