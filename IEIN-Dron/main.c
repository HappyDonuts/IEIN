/*
 * main.c
 *
 *  Created on: 26 de abr. de 2017
 *      Author: Yo
 */

#include "dron_control.h"

#define CLK_MS 				100
#define MAX_TEST_TIME		5000

extern fsm_trans_t dron_transition_table[];

int main ()
{
	unsigned long long time = 0;	//Time count in ms

	fsm_t* fsm = (fsm_t*) new_dron_fsm(dron_transition_table);

	while (time < MAX_TEST_TIME) {

		read_msg((dron_fsm_t*) fsm);				//Leo los mensajes de entrada y los almaceno
		parse_and_update((dron_fsm_t*) fsm);		//Leo el primer comando almacenado

		fsm_fire (fsm);

		usleep(CLK_MS*1000);
		time += CLK_MS;
	}

	delete_dron_fsm((dron_fsm_t*) fsm);
}
