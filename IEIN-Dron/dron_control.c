/*
 * Copyright (c) 2017, Universidad Politecnica de Madrid - B105 Electronic Systems Lab
 * All rights reserved.

 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. All advertising materials mentioning features or use of this software
 *    must display the following acknowledgement:
 *    This product includes software developed by the B105 Electronic Systems Lab.
 * 4. Neither the name of the B105 Electronic Systems Lab nor the
 *    names of its contributors may be used to endorse or promote products
 *    derived from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY UNIVERSITY AND CONTRIBUTORS ''AS IS'' AND ANY
 * EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL <COPYRIGHT HOLDER> BE LIABLE FOR ANY
 * DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 *
 * dron_control.c
 *
 *  Created on: 24 de abr. de 2017
 *      Author: Roberto Rodriguez-Zurrunero  <r.rodriguezz@b105.upm.es>
 *
 */
/**
 * @file dron_control.c
 */

#include "dron_control.h"
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include "fsm.h"
#include "msg_list.h"

#define WRITE_FILENAME		"write_msg_file.txt"
#define READ_FILENAME		"read_msg_file.txt"
#define MSG_FORMAT			"%s\r\n"
#define MSG_MAX_SIZE		16

static volatile dron_fsm_t dron;

///////FSM TABLE FUNCTIONS//////
//CONDITION FUNCTIONS
//TODO Declaraci�n de funciones INPUT de la m�quina de estados. Condiciones para entrar en un estado
static int compruebaStart(fsm_t* fsm);
static int compruebaSubir(fsm_t* fsm);
static int compruebaAlturaMedia(fsm_t* fsm);
static int compruebaBajar(fsm_t* fsm);
static int compruebaStop(fsm_t* fsm);
static int compruebaLimSup(fsm_t* fsm);
static int compruebaLimInf(fsm_t* fsm);
static int compruebaEstable(fsm_t* fsm);


//OUTPUT FUNCTIONS
//TODO Declaraci�n de funciones OUTPUT de la m�quina de estados. Se ejecutan cuando se alcanza el estado.
static void asciende(fsm_t* fsm);
static void desciende(fsm_t* fsm);


// M�quina de estados: lista de transiciones
// { EstadoOrigen, CondicionDeDisparo, EstadoFinal, AccionesSiTransicion }
fsm_trans_t dron_transition_table[] = {
//TODO Rellenar tabla de transiciones de la m�quina de estados
		{STOPPED, compruebaStart, RISING, asciende },
		{RISING, compruebaSubir, RISING, asciende },
		{RISING, compruebaAlturaMedia, STABLE, NULL },
		{RISING, compruebaBajar, DESCENDING, desciende },
		{RISING, compruebaStop, DESCENDING, desciende },
		{RISING, compruebaEstable, STABLE, NULL },
		{DESCENDING, compruebaStop, STOPPED, desciende },
		{DESCENDING, compruebaBajar, DESCENDING, desciende },
		{DESCENDING, compruebaSubir, RISING, asciende },
		{DESCENDING, compruebaAlturaMedia, STABLE, NULL },
		{DESCENDING, compruebaEstable, STABLE, NULL },
		{STABLE, compruebaLimSup, DESCENDING, desciende },
		{STABLE, compruebaLimInf, RISING, asciende },
		{STABLE, compruebaSubir, RISING, asciende },
		{STABLE, compruebaBajar, DESCENDING, desciende },
		{-1, NULL, -1, NULL },
};


/////Dron FSM object functions//////
dron_fsm_t* new_dron_fsm(fsm_trans_t* dron_transition_table){
	dron_fsm_t* new_dron_fsm = (dron_fsm_t*) malloc(sizeof(dron_fsm_t));
	new_dron_fsm = fsm_new(STOPPED, dron_transition_table);
	new_dron_fsm->msg_list = msg_list_init();
	new_dron_fsm->current_height = 0;
	new_dron_fsm->modifier_height = 0;
	new_dron_fsm->started_flag = 0;
	new_dron_fsm->stopping_flag = 0;


	//TODO Inicializar...

	return new_dron_fsm;
}

int delete_dron_fsm(dron_fsm_t* dron_fsm){
	//TODO Borrar la lista de mensajes y el objeto dron_fsm
	msg_list_delete(dron_fsm->msg_list);
	free(dron_fsm);
	return 1;
}


int read_msg(dron_fsm_t* dron_fsm){

	//TODO Leer el fichero de entrada y guardar todos los mensajes que se encuentren en la lista de mensajes.
	//	   Eliminar el fichero una vez le�do por completo. Si no se puede abrir el fichero o no existe devolver -1
	char* cadena= malloc(16);
	FILE *f = fopen("read_msg_file.txt", "r");

	if (f == NULL){
		return -1;
	}
	while(fgets(cadena, MSG_MAX_SIZE, f) != NULL){
		msg_list_push_element(dron_fsm->msg_list, cadena);
	}

	fclose(f);
	//	remove("read_msg_file.txt");
	return 1;
}


int parse_and_update(dron_fsm_t* dron_fsm){
	//TODO Leer el mensaje m�s antiguo almacenado en la lista FIFO y parsearlo. Seg�n el tipo de mensaje que sea actualizar los flags internos del objeto dron_fsm. Devolver -1 si no hay mensajes en la lista.
	char command[16];
	strcpy(command, msg_list_pop_element(dron_fsm->msg_list));
	char valor[2];

if (strcmp(command, "START \n")==0){
	dron_fsm->started_flag = 1;
	dron_fsm->modifier_height=STABLE_HEIGHT;
	return 1;
}
if (strcmp(command, "STOP ")==0){
	dron_fsm->stopping_flag = 1;
	dron_fsm->modifier_height=-(dron_fsm->current_height);
	return 1;
}
if (command[1] == '+'){
	valor[0] = command[2];
	valor[1] = command[3];
	dron_fsm->modifier_height = atoi(valor);
	return 1;
}
if (command[1] == '-'){
	valor[0] = command[2];
		valor[1] = command[3];
		dron_fsm->modifier_height = -(atoi(valor));
}

	return 1;
}


///////FSM TABLE FUNCTIONS//////
//CONDITION FUNCTIONS
//TODO Implementaci�n de funciones INPUT de la m�quina de estados. Condiciones para entrar en un estado
static int compruebaStart(fsm_t* fsm){
	if(dron.started_flag == 1){
		return 1;
	}
return 0;
}

static int compruebaSubir(fsm_t* fsm){
	if(dron.modifier_height >0) {
		return 1;
	}
return 0;
}

static int compruebaAlturaMedia(fsm_t* fsm){
	if(dron.current_height == STABLE_HEIGHT){
		return 1;
	}
return 0;
}

static int compruebaBajar(fsm_t* fsm){
	if(dron.modifier_height <0) {
		return 1;
	}
return 0;
}

static int compruebaStop(fsm_t* fsm){
	if(dron.stopping_flag){
		return 1;
	}
return 0;
}

static int compruebaLimSup(fsm_t* fsm){
	if(dron.current_height > HEIGHT_LIMIT_HIGH){
		return 1;
	}
return 0;
}

static int compruebaLimInf(fsm_t* fsm){
	if(dron.current_height > HEIGHT_LIMIT_LOW){
		return 1;
	}
return 0;
}

static int compruebaEstable(fsm_t* fsm){
	if(dron.modifier_height == 0){
		return 1;
	}
return 0;
}

//OUTPUT FUNCTIONS
//TODO Implementaci�n de funciones OUTPUT de la m�quina de estados. Se ejecutan cuando se alcanza el estado. Se escribe en el fichero de salida el estado que se alcanza.
static void asciende(fsm_t* fsm){
	dron.current_height+=dron.modifier_height;
	dron.modifier_height=0;
	dron.started_flag = 0;
	dron.stopping_flag = 0;
	imprimeEstado(fsm);
}
static void desciende(fsm_t* fsm){
	dron.current_height+=dron.modifier_height;
	dron.modifier_height=0;
	dron.started_flag = 0;
	dron.stopping_flag = 0;
	imprimeEstado(fsm);
}
 void imprimeEstado(fsm_t* fsm){
	printf("%d", fsm->current_state);
	fflush(stdout);
}

