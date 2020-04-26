/****************************************************************
 * This file is part of SWKBD_Fuzzer.                           *
 * (c) 2020 V10lator <v10lator@myway.de>                        *
 *                                                              *
 * Licensed under the MIT license (see LICENSE.txt for details) *
 ****************************************************************/

#include <stdint.h> // Workaround for libgui bug libgui/include/gui/memory.h:35:39: error: 'uint32_t' was not declared in this scope
#include <gui/memory.h>
#include <gui/video/CVideo.h>

#include <stdbool.h>

#include "guiWrapper.h"
#include "input.h"
#include "swkbd_wrapper.h"

CVideo *renderer;

void initScreen()
{
	libgui_memoryInitialize();
	renderer = new CVideo(GX2_TV_SCAN_MODE_720P, GX2_DRC_RENDER_MODE_SINGLE);
	renderer->tvEnable(true);
	renderer->drcEnable(true);
}

void shutdownScreen()
{
	delete renderer;
	libgui_memoryRelease();
}

void blankScreen()
{
	renderer->prepareTvRendering();
	renderer->tvDrawDone();
	
	renderer->prepareDrcRendering();
	renderer->drcDrawDone();
	
	renderer->waitForVSync();
}

void drawKeyboard()
{
	renderer->prepareTvRendering();
	Swkbd_DrawTV();
	renderer->tvDrawDone();
	
	renderer->prepareDrcRendering();
	Swkbd_DrawDRC();
	renderer->drcDrawDone();
	
	renderer->waitForVSync();
}