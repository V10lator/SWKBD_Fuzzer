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

// Enums copied from https://github.com/devkitPro/wut/blob/master/include/nn/swkbd/swkbd_cpp.h
typedef enum
{
   Swkbd_LanguageType__Japanese = 0,
   Swkbd_LanguageType__English  = 1,
} Swkbd_LanguageType;

typedef enum
{
	Swkbd_RegionType__Japan    = 0,
	Swkbd_RegionType__USA      = 1,
	Swkbd_RegionType__Europe   = 2,
} Swkbd_RegionType;

//Structs also from the link above
typedef struct
{
   Swkbd_LanguageType languageType;
   uint32_t unk_0x04;
   uint32_t unk_0x08;
   uint32_t unk_0x0C;
   uint32_t unk_0x10;
   int32_t unk_0x14;
   WUT_UNKNOWN_BYTES(0x9C - 0x18);
   uint32_t unk_0x9C;
   WUT_UNKNOWN_BYTES(4);
   int32_t unk_0xA4;
} Swkbd_ConfigArg;
WUT_CHECK_OFFSET(Swkbd_ConfigArg, 0x00, languageType);
WUT_CHECK_OFFSET(Swkbd_ConfigArg, 0x04, unk_0x04);
WUT_CHECK_OFFSET(Swkbd_ConfigArg, 0x08, unk_0x08);
WUT_CHECK_OFFSET(Swkbd_ConfigArg, 0x0C, unk_0x0C);
WUT_CHECK_OFFSET(Swkbd_ConfigArg, 0x10, unk_0x10);
WUT_CHECK_OFFSET(Swkbd_ConfigArg, 0x14, unk_0x14);
WUT_CHECK_OFFSET(Swkbd_ConfigArg, 0x9C, unk_0x9C);
WUT_CHECK_OFFSET(Swkbd_ConfigArg, 0xA4, unk_0xA4);
WUT_CHECK_SIZE(Swkbd_ConfigArg, 0xA8);

typedef struct
{
	uint32_t unk_0x00;
	uint32_t unk_0x04;
	uint32_t unk_0x08;
	int32_t unk_0x0C;
	uint32_t unk_0x10;
	int32_t unk_0x14;
} Swkbd_ReceiverArg;
WUT_CHECK_OFFSET(Swkbd_ReceiverArg, 0x00, unk_0x00);
WUT_CHECK_OFFSET(Swkbd_ReceiverArg, 0x04, unk_0x04);
WUT_CHECK_OFFSET(Swkbd_ReceiverArg, 0x08, unk_0x08);
WUT_CHECK_OFFSET(Swkbd_ReceiverArg, 0x0C, unk_0x0C);
WUT_CHECK_OFFSET(Swkbd_ReceiverArg, 0x10, unk_0x10);
WUT_CHECK_OFFSET(Swkbd_ReceiverArg, 0x14, unk_0x14);
WUT_CHECK_SIZE(Swkbd_ReceiverArg, 0x18);

typedef struct
{
   Swkbd_ConfigArg configArg;
   Swkbd_ReceiverArg receiverArg;
} Swkbd_KeyboardArg;
WUT_CHECK_SIZE(Swkbd_KeyboardArg, 0xC0);

typedef struct
{
   uint32_t unk_0x00;
   int32_t unk_0x04;
   uint32_t unk_0x08;
   uint32_t unk_0x0C;
   int32_t maxTextLength;
   uint32_t unk_0x14;
   uint32_t unk_0x18;
   bool unk_0x1C;
   bool unk_0x1D;
   bool unk_0x1E;
   WUT_PADDING_BYTES(1);
} Swkbd_InputFormArg;
WUT_CHECK_OFFSET(Swkbd_InputFormArg, 0x00, unk_0x00);
WUT_CHECK_OFFSET(Swkbd_InputFormArg, 0x04, unk_0x04);
WUT_CHECK_OFFSET(Swkbd_InputFormArg, 0x08, unk_0x08);
WUT_CHECK_OFFSET(Swkbd_InputFormArg, 0x0C, unk_0x0C);
WUT_CHECK_OFFSET(Swkbd_InputFormArg, 0x10, maxTextLength);
WUT_CHECK_OFFSET(Swkbd_InputFormArg, 0x14, unk_0x14);
WUT_CHECK_OFFSET(Swkbd_InputFormArg, 0x18, unk_0x18);
WUT_CHECK_OFFSET(Swkbd_InputFormArg, 0x1C, unk_0x1C);
WUT_CHECK_OFFSET(Swkbd_InputFormArg, 0x1D, unk_0x1D);
WUT_CHECK_OFFSET(Swkbd_InputFormArg, 0x1E, unk_0x1E);
WUT_CHECK_SIZE(Swkbd_InputFormArg, 0x20);

typedef struct
{
   Swkbd_KeyboardArg keyboardArg;
   Swkbd_InputFormArg inputFormArg;
} Swkbd_AppearArg;
WUT_CHECK_SIZE(Swkbd_AppearArg, 0xE0);

typedef struct
{
   void *workMemory;
   Swkbd_RegionType regionType;
   uint32_t unk_0x08;
   FSClient *fsClient;
} Swkbd_CreateArg;
WUT_CHECK_OFFSET(Swkbd_CreateArg, 0x00, workMemory);
WUT_CHECK_OFFSET(Swkbd_CreateArg, 0x04, regionType);
WUT_CHECK_OFFSET(Swkbd_CreateArg, 0x08, unk_0x08);
WUT_CHECK_OFFSET(Swkbd_CreateArg, 0x0C, fsClient);
WUT_CHECK_SIZE(Swkbd_CreateArg, 0x10);

typedef struct
{
   VPADStatus *vpad;
   KPADStatus *kpad[4];
} Swkbd_ControllerInfo;
WUT_CHECK_OFFSET(Swkbd_ControllerInfo, 0x00, vpad);
WUT_CHECK_OFFSET(Swkbd_ControllerInfo, 0x04, kpad);
WUT_CHECK_SIZE(Swkbd_ControllerInfo, 0x14);

//Wrapper functions
uint32_t Swkbd_GetWorkMemorySize(uint32_t unk);
bool Swkbd_AppearInputForm(const Swkbd_AppearArg args);
bool Swkbd_Create(const Swkbd_CreateArg args);
void Swkbd_SetEnableOkButton(bool enable);
char *Swkbd_GetInputFormString();
void Swkbd_SetInputFormString(const char *str);
void Swkbd_Calc(const Swkbd_ControllerInfo controllerInfo);
bool Swkbd_IsNeedCalcSubThreadFont();
void Swkbd_CalcSubThreadFont();
void Swkbd_DrawTV();
void Swkbd_DrawDRC();
bool Swkbd_IsDecideOkButton(bool *outIsSelected);
bool Swkbd_IsDecideCancelButton(bool *outIsSelected);
bool Swkbd_DisappearInputForm();
void Swkbd_Destroy();

#ifdef __cplusplus
	}
#endif

#endif // ifndef ifndef SWKBDFU_SWKBD_MAPPER_H