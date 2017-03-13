/*
 * comunicaciones.c
 *
 *  Created on: 13 de mar. de 2017
 *      Author: Javi
 */

int recPacket(char msg[]){

	int i=0;
	int length=0;

	// Contamos el numero de bytes que hay en el array
	for (i=0;i<14;i++){
		if (msg[i] == 0x0F){
			length=i+1;
			break;}
	}

	// El array debe tener entre 4 y 13 bytes y acaba en 0x0F
	if (length < 4 || length > 13 || msg[length-1] != 0x0F){
		return 0;}

	// El segundo byte tiene que ser uno de estos 4
	switch(msg[1]) {
		case 't':
			return 11;
		case 'l':
			return 12;
		case 'p':
			return 13;
		case 'r':
			return 14;
		default:
			return 0;
	}

	if (msg[1] != 0x45) {
			return 20;}
}
