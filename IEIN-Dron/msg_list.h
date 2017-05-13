/*
 * msg_list.h
 *
 *  Created on: 26 de abr. de 2017
 *      Author: Yo
 */

#ifndef MSG_LIST_H_
#define MSG_LIST_H_

typedef struct msg_list{
	char* msg;
	struct msg_list* next;
}msg_list_t;

msg_list_t* msg_list_init(void);
int msg_list_delete(msg_list_t* msg_list);	//IMPORTANTE LIBERAR EL ESPACIO DE MEMORIA DE CADA MENSAJE char*

int msg_list_push_element(msg_list_t* msg_list, char* msg);	// Se introduce en la cola FIFO el puntero a una cadena de caracteres msg. El espacio para esta cadena debe haber sido reservado anteriormente
char* msg_list_pop_element(msg_list_t* msg_list);			//Devuelve el puntero al elemento más antiguo de la lista y elimina la referencia de la lista. Tras usar el mensaje este deberá ser liberado.

#endif /* MSG_LIST_H_ */
