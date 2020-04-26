/****************************************************************
 * This file is part of SWKBD_Fuzzer.                           *
 * (c) 2020 V10lator <v10lator@myway.de>                        *
 *                                                              *
 * Licensed under the MIT license (see LICENSE.txt for details) *
 ****************************************************************/

#ifndef SWKBDFU_GUI_WRAPPER_H
#define SWKBDFU_GUI_WRAPPER_H

#include <stdbool.h>

#ifdef __cplusplus
	extern "C" {
#endif

void initScreen();
void shutdownScreen();
void drawFrame(bool bkd);

#ifdef __cplusplus
	}
#endif

#endif // ifndef SWKBDFU_GUI_WRAPPER_H
