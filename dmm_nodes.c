#include "dmm.h"

/* 
 * This file contains all the functions necessary for creating nodes
 */

Bool isListEmpty(Node *list_head)
{
	if (list_head == NULL) {
		return True;
	} else {
		return False;
	}
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

		(head != NULL) ? (success = 1) : (success = 0);
	}
	return success;
}

/* This function allocates memory to store data extracted from a CSV file for the
* digital music manager.
*/
Node *createNode(Record new_data) // borrowed
{
	Node *newNode; // borrowed
				   // Allocate memory for our data
	newNode = malloc(sizeof(*newNode));

	if (newNode != NULL) {
		//Store our data to the linked list
		newNode->Data.artist = new_data.artist; // These were not.
		newNode->Data.album_title = new_data.album_title;
		newNode->Data.song_title = new_data.song_title;
		newNode->Data.genre = new_data.genre;
		newNode->Data.song_length.minutes = new_data.song_length.minutes;
		newNode->Data.song_length.seconds = new_data.song_length.seconds;
		newNode->Data.times_played = new_data.times_played;
		newNode->Data.rating = new_data.rating;

		newNode->next = head;
	}

	return newNode;
}
Node *get_node_by_num(Node *list_head, int node_number)
{
	Node *indexor = NULL;
	int i;

	indexor = list_head;

	i = 1;
	while (i < node_number) {
		indexor = indexor->next;
		if (indexor == NULL) {
			break;
		}
		i++;
	}

	return indexor;
}

/* Implemented later in PA3 */
int deleteNode(Node *list_head)
{

}
