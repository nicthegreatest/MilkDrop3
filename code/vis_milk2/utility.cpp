/*
  LICENSE
  -------
Copyright 2005-2013 Nullsoft, Inc.
All rights reserved.

Redistribution and use in source and binary forms, with or without modification,
are permitted provided that the following conditions are met:

  * Redistributions of source code must retain the above copyright notice,
    this list of conditions and the following disclaimer.

  * Redistributions in binary form must reproduce the above copyright notice,
    this list of conditions and the following disclaimer in the documentation
    and/or other materials provided with the distribution.

  * Neither the name of Nullsoft nor the names of its contributors may be used to
    endorse or promote products derived from this software without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR
IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND
FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER
IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT
OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

#include "utility.h"
#include <math.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

intptr_t myOpenURL(void* hwnd, const char *loc)
{
    // Stub implementation. On Linux, one might use `xdg-open`.
    printf("Opening URL (stub): %s\n", loc);
    return 1; // Success
}

float PowCosineInterp(float x, float pow)
{
    // input (x) & output should be in range 0..1.
    // pow > 0: tends to push things toward 0 and 1
    // pow < 0: tends to push things toward 0.5.

    if (x<0)
        return 0;
    if (x>1)
        return 1;

    int bneg = (pow < 0) ? 1 : 0;
    if (bneg)
        pow = -pow;

    if (pow>1000) pow=1000;

    int its = (int)pow;
    for (int i=0; i<its; i++)
    {
        if (bneg)
            x = InvCosineInterp(x);
        else
            x = CosineInterp(x);
    }
    float x2 = (bneg) ? InvCosineInterp(x) : CosineInterp(x);
    float dx = pow - its;
    return ((1-dx)*x + (dx)*x2);
}

float AdjustRateToFPS(float per_frame_decay_rate_at_fps1, float fps1, float actual_fps)
{
    // returns the equivalent per-frame decay rate at actual_fps

    // basically, do all your testing at fps1 and get a good decay rate;
    // then, in the real application, adjust that rate by the actual fps each time you use it.

    float per_second_decay_rate_at_fps1 = powf(per_frame_decay_rate_at_fps1, fps1);
    float per_frame_decay_rate_at_fps2 = powf(per_second_decay_rate_at_fps1, 1.0f/actual_fps);

    return per_frame_decay_rate_at_fps2;
}

// Dummy implementations for INI file functions
float GetPrivateProfileFloat(const char *szSectionName, const char *szKeyName, float fDefault, const char *szIniFile)
{
    // Stub implementation
    return fDefault;
}

bool WritePrivateProfileInt(int d, const char *szKeyName, const char *szIniFile, const char *szSectionName)
{
    // Stub implementation
    return true;
}

bool WritePrivateProfileFloat(float f, const char *szKeyName, const char *szIniFile, const char *szSectionName)
{
    // Stub implementation
    return true;
}


void RemoveExtension(char *str)
{
    char *p = strrchr(str, '.');
    if (p) *p = 0;
}

static void ShiftDown(char *str)
{
	while (*str)
	{
		str[0] = str[1];
		str++;
	}
}

void RemoveSingleAmpersands(char *str)
{
	while (*str)
	{
		if (str[0] == '&')
		{
			if (str[1] == '&') // two in a row: replace with single ampersand, move on
				str++;

			ShiftDown(str);
		}
		else
			str++; // Note: This might not handle multi-byte characters correctly, but we're assuming ASCII/UTF-8 for now.
	}
}

bool CheckForMMX()
{
    // On modern x86/x64, MMX is universally available.
    // For other architectures, this would need a proper check.
#if defined(__i386__) || defined(__x86_64__)
    return true;
#else
    return false;
#endif
}

bool CheckForSSE()
{
    // On modern x86/x64, SSE is universally available.
#if defined(__i386__) || defined(__x86_64__)
    return true;
#else
    return false;
#endif
}

void GetDesktopFolder(char *szDesktopFolder)
{
    // Stub implementation for non-Windows platforms.
    // We can default to the user's home directory.
    const char* home = getenv("HOME");
    if (home) {
        strcpy(szDesktopFolder, home);
    } else {
        szDesktopFolder[0] = '\0';
    }
}