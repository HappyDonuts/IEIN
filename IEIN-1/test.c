/*
 * test.c
 *
 *  Created on: 6/3/2017
 *      Author: Elena
 */


#include <stdio.h>
#include "comunicaciones.h"


int main (){

	int result;

	char msg[11] = {0x45, 't', '0','0','0','0','0','0','0','0',0x0F};

	result = recPacket(msg);

	printf("recPacket devuelve %d\n", result);

	return 0;
}
