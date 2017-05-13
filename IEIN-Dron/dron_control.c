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

#define WRITE_FILENAME		"write_msg_file.txt"
#define READ_FILENAME		"read_msg_file.txt"
#define MSG_FORMAT			"%s\r\n"
#define MSG_MAX_SIZE		16

///////FSM TABLE FUNCTIONS//////
//CONDITION FUNCTIONS
//TODO Declaración de funciones INPUT de la máquina de estados. Condiciones para entrar en un estado
static int input_example_func(fsm_t* fsm);


//OUTPUT FUNCTIONS
//TODO Declaración de funciones OUTPUT de la máquina de estados. Se ejecutan cuando se alcanza el estado.
static void output_example_func(fsm_t* fsm);


// Máquina de estados: lista de transiciones
// { EstadoOrigen, CondicionDeDisparo, EstadoFinal, AccionesSiTransicion }
fsm_trans_t dron_transition_table[] = {
//TODO Rellenar tabla de transiciones de la máquina de estados
  {-1, NULL, -1, NULL },
};


/////Dron FSM object functions//////
dron_fsm_t* new_dron_fsm(fsm_trans_t* dron_transition_table){
	dron_fsm_t* new_dron_fsm = (dron_fsm_t*) malloc(sizeof(dron_fsm_t));
	//TODO Inicializar...

	return new_dron_fsm;
}

int delete_dron_fsm(dron_fsm_t* dron_fsm){
	//TODO Borrar la lista de mensajes y el objeto dron_fsm
	return 1;
}


int read_msg(dron_fsm_t* dron_fsm){

	//TODO Leer el fichero de entrada y guardar todos los mensajes que se encuentren en la lista de mensajes.
	//	   Eliminar el fichero una vez leído por completo. Si no se puede abrir el fichero o no existe devolver -1
	return 1;
}


int parse_and_update(dron_fsm_t* dron_fsm){
	//TODO Leer el mensaje más antiguo almacenado en la lista FIFO y parsearlo. Según el tipo de mensaje que sea actualizar los flags internos del objeto dron_fsm. Devolver -1 si no hay mensajes en la lista.
	return 1;
}


///////FSM TABLE FUNCTIONS//////
//CONDITION FUNCTIONS
//TODO Implementación de funciones INPUT de la máquina de estados. Condiciones para entrar en un estado
static int input_example_func(fsm_t* fsm){
	return 0;
}

//OUTPUT FUNCTIONS
//TODO Implementación de funciones OUTPUT de la máquina de estados. Se ejecutan cuando se alcanza el estado. Se escribe en el fichero de salida el estado que se alcanza.
static void output_example_func(fsm_t* fsm){

}
