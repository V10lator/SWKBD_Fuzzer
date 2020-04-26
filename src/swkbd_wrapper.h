/****************************************************************
 * This file is part of SWKBD_Fuzzer.                           *
 * (c) 2020 V10lator <v10lator@myway.de>                        *
 *                                                              *
 * Licensed under the MIT license (see LICENSE.txt for details) *
 ****************************************************************/

#ifndef SWKBDFU_SWKBD_MAPPER_H
#define SWKBDFU_SWKBD_MAPPER_H

#include <stdbool.h>
#include <stdint.h>

#include <nn/swkbd.h>

#ifdef __cplusplus
	extern "C" {
#endif

//Wrapper functions
uint32_t Swkbd_GetWorkMemorySize(uint32_t unk);
bool Swkbd_AppearInputForm();
bool Swkbd_Create();
void Swkbd_SetEnableOkButton(bool enable);
void Swkbd_Calc(VPADStatus vpad);
bool Swkbd_IsNeedCalcSubThreadFont();
void Swkbd_CalcSubThreadFont();
void Swkbd_DrawTV();
void Swkbd_DrawDRC();
bool Swkbd_DisappearInputForm();
void Swkbd_Destroy();

#ifdef __cplusplus
	}
#endif

#endif // ifndef ifndef SWKBDFU_SWKBD_MAPPER_H