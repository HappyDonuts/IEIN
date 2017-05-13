/*
 * msg_list.c
 *
 *  Created on: 26 de abr. de 2017
 *      Author: Yo
 */

#include "msg_list.h"
#include <unistd.h>
#include <stdlib.h>

msg_list_t* msg_list_init(void){
	msg_list_t* new_msg_list = (msg_list_t*) malloc(sizeof(msg_list_t));
	new_msg_list->msg = NULL;
	new_msg_list->next = NULL;
	return new_msg_list;
}

int msg_list_delete(msg_list_t* msg_list){

	msg_list_t* aux;

	//TODO

	return 1;
}


int msg_list_push_element(msg_list_t* msg_list, char* msg){

	//TODO

	return 1;
}


char* msg_list_pop_element(msg_list_t* msg_list){	//Devolver NULL si la lista está vacía

	//TODO

	return NULL;
}
