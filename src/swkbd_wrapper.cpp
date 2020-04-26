/****************************************************************
 * This file is part of SWKBD_Fuzzer.                           *
 * (c) 2020 V10lator <v10lator@myway.de>                        *
 *                                                              *
 * Licensed under the MIT license (see LICENSE.txt for details) *
 ****************************************************************/

#include <stdint.h>
#include <cstring>

#include <coreinit/memdefaultheap.h>

#include "swkbd_wrapper.h"

uint32_t Swkbd_GetWorkMemorySize(uint32_t unk)
{
	return nn::swkbd::GetWorkMemorySize(unk);
}

bool Swkbd_AppearInputForm(const Swkbd_AppearArg args)
{
	return nn::swkbd::AppearInputForm(*(nn::swkbd::AppearArg*)&args);
}

bool Swkbd_Create(const Swkbd_CreateArg args)
{
	return nn::swkbd::Create(*(nn::swkbd::CreateArg*)&args);
}

void Swkbd_SetEnableOkButton(bool enable)
{
	nn::swkbd::SetEnableOkButton(enable);
}

void Swkbd_Calc(const Swkbd_ControllerInfo controllerInfo)
{
	nn::swkbd::Calc(*(nn::swkbd::ControllerInfo*)&controllerInfo);
}

bool Swkbd_IsNeedCalcSubThreadFont()
{
	return nn::swkbd::IsNeedCalcSubThreadFont();
}

void Swkbd_CalcSubThreadFont()
{
	nn::swkbd::CalcSubThreadFont();
}

void Swkbd_DrawTV()
{
	nn::swkbd::DrawTV();
}

void Swkbd_DrawDRC()
{
	nn::swkbd::DrawDRC();
}

bool Swkbd_DisappearInputForm()
{
	return nn::swkbd::DisappearInputForm();
}

void Swkbd_Destroy()
{
	nn::swkbd::Destroy();
}
