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

bool SWKBD_Init();
void SWKBD_Shutdown();

bool showKeyboard();

#ifdef __cplusplus
	}
#endif

#endif //ifndef SWKBDFU_INPUT_H