/****************************************************************
 * This file is part of SWKBD_Fuzzer.                           *
 * (c) 2020 V10lator <v10lator@myway.de>                        *
 *                                                              *
 * Licensed under the MIT license (see LICENSE.txt for details) *
 ****************************************************************/

#include <coreinit/filesystem.h>
#include <whb/log.h>
#include <whb/log_udp.h>

#include "guiWrapper.h"
#include "input.h"

int main()
{
	WHBLogUdpInit();
	WHBLogPrintf("Initialising libraries...");
	
	initScreen();
	blankScreen();
	WHBLogPrintf("Screen initialized!");
	
	FSInit(); // We need to start this before the SWKBD.
	WHBLogPrintf("FS initialized!");
	
	SWKBD_Init();
	
	for(int i = 0; i < 10; i++)
	{
		showKeyboard();
		blankScreen();
	}
	
	WHBLogPrintf("Deinitializing libraries...");
	
	SWKBD_Shutdown();
	WHBLogPrintf("SWKBD closed");
	
	shutdownScreen();
	WHBLogPrintf("OSScreen closed");
	
	FSShutdown();
	WHBLogPrintf("FS closed");
	
	WHBLogUdpDeinit();
	return 0;
}
