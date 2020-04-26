/****************************************************************
 * This file is part of SWKBD_Fuzzer.                           *
 * (c) 2020 V10lator <v10lator@myway.de>                        *
 *                                                              *
 * Licensed under the MIT license (see LICENSE.txt for details) *
 ****************************************************************/

#ifndef SWKBDFU_INPUT_H
#define SWKBDFU_INPUT_H

#include <stdbool.h>

#include <vpad/input.h>

#ifdef __cplusplus
	extern "C" {
#endif

extern VPADStatus vpad;

typedef enum
{
	CHECK_NONE,			//No check
	CHECK_NUMERICAL,	//Only numbers
	CHECK_HEXADECIMAL,	//Only hex
	CHECK_NOSPECIAL,	//Only letters or numbers
	CHECK_URL,
} KeyboardChecks;

typedef enum
{
	KEYBOARD_TYPE_RESTRICTED,
	KEYBOARD_TYPE_NORMAL
} KeyboardType;

bool SWKBD_Init();
void SWKBD_Shutdown();

void readInput();
bool showKeyboard();

#ifdef __cplusplus
	}
#endif

#endif //ifndef SWKBDFU_INPUT_H