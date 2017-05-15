/*
 * msg_list.c
 *
 *  Created on: 26 de abr. de 2017
 *      Author: Yo
 */

#include "msg_list.h"
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include "fsm.h"
#include "msg_list.h"

msg_list_t* msg_list_init(void){
	msg_list_t* new_msg_list = (msg_list_t*) malloc(sizeof(msg_list_t));
	new_msg_list->msg = NULL;
	new_msg_list->next = NULL;
	return new_msg_list;
}

int msg_list_delete(msg_list_t* msg_list){

	msg_list_t* aux;

	while ((msg_list) ->next != NULL) {
		aux = msg_list->next;
		msg_list->next = aux->next;
		free(aux);
	}
	free(msg_list);
	return 1;
}


int msg_list_push_element(msg_list_t *msg_list, char msg[16]){

	msg_list_t *newItem;
	newItem = (msg_list_t *) malloc(sizeof(msg_list_t));
	if(newItem == NULL) {
		printf ("no hay memoria\n");
		return 0;
	}

	newItem->next = msg_list->next;
	msg_list->next = newItem;

	newItem->msg = msg;

	return 1;
}


char* msg_list_pop_element(msg_list_t* msg_list){	//Devolver NULL si la lista est� vac�a

	msg_list_t* aux = msg_list->next;
	msg_list_t* prev = msg_list;

	if(aux != NULL){
		while(aux->next != NULL){
			prev = aux;
			aux = aux->next;
		}
		prev->next = NULL;
		return aux->msg;
	}
	return NULL;
}
