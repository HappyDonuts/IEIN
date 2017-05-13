/*
 * dron_control.h
 *
 *  Created on: 26 de abr. de 2017
 *      Author: Yo
 */

#ifndef DRON_CONTROL_H_
#define DRON_CONTROL_H_

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include "fsm.h"
#include "msg_list.h"

#define STABLE_HEIGHT		100
#define HEIGHT_LIMIT_LOW	80
#define HEIGHT_LIMIT_HIGH	120
#define ZERO_HEIGHT			0


typedef enum fsm_state {
	//TODO	Posibles estados de la máquina de estados del dron
	STOPPED,
	RISING,
	STABLE,
	DESCENDING,
}dron_fsm_state_t;


typedef struct dron_fsm_{
	fsm_t fsm;				//Herencia
	int started_flag;		//Flags necesarios y altura actual
	int stopping_flag;
	int current_height;
	msg_list_t* msg_list;	//Lista de mensajes
}dron_fsm_t;

dron_fsm_t* new_dron_fsm(fsm_trans_t* dron_transition_table);
int delete_dron_fsm(dron_fsm_t* dron_fsm);

int read_msg(dron_fsm_t* dron_fsm);				//LEO el fichero y almaceno en la cola de mensages todos los mensajes del fichero
int parse_and_update(dron_fsm_t* dron_fsm);		//Leo UN mensaje de la lista, lo traduzco y actualizo los flags según corresponda


#endif /* DRON_CONTROL_H_ */
