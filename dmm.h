#ifndef MUSIC_MANAGER
#define MUSIC_MANAGER
/* NOTE-TO-SELF: Need to find a way to detect OS using preprocessor directive
* so that right libraries are included before runtime
*/
#include <stdio.h> 	/* printf, scanf, fgets, sscanf */
#include <stdlib.h> /* malloc, 					 	*/
#include <string.h> /* strtok, strdup,				*/
#include <Windows.h> /* Sleep						*/			
//#include <unistd.h> /* sleep, this library is for *nix only	*/

#define TERMINATING_CHARACTER_SPACE 1
#define PRINT_ALL 'a'
#define PRINT_ONE 'o'
#define FILENAME "musicPlayList.csv"

#define CLEAR_SCREEN system("cls")

#define LOAD 1
#define STORE 2
#define DISPLAY 3
#define INSERT 4
#define DELETE 5
#define EDIT 6
#define SORT 7
#define RATE 8
#define PLAY 9
#define SHUFFLE 10
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
	False, True
} Bool;



void print_menu(void);
void pause_exec(void);
int input_validation_int(void);
Bool isListEmpty(Node *list_head);
void start_program(void);
void load();
int insertRecordFront(Record input_data);
Record insert_record(void);
Node *createNode(Record insert_record); // borrowed
void print_node(Node *list_index, char print_type);
FILE *open_file(void);
int store(Node *linkedList_head);
Node *get_node_by_num(Node *list_head, int node_number);
char *input_validation_str(void);
Node *get_node_edit(Node *list_head);
void edit_prompt(Node *edit);
void rate(Node *changedNode);

void play(Node *song);
int deleteNode(Node *list_head);
void exit_program(Node *list_root);
char *concatenate(char *str1, char *str2);
char *checkArtistName(char *name);


#endif