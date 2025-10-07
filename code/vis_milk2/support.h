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

#ifndef __NULLSOFT_DX9_EXAMPLE_PLUGIN_SUPPORT_H__
#define __NULLSOFT_DX9_EXAMPLE_PLUGIN_SUPPORT_H__ 1

#include "shell_defines.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>


void MakeWorldMatrix( glm::mat4* pOut,
                      float xpos, float ypos, float zpos,
                      float sx,   float sy,   float sz,
                      float pitch, float yaw, float roll);
void MakeProjectionMatrix( glm::mat4* pOut,
                           const float near_plane, // Distance to near clipping plane
                           const float far_plane,  // Distance to far clipping plane
                           const float fov_horiz,  // Horizontal field of view angle, in radians
                           const float fov_vert);   // Vertical field of view angle, in radians


// Define vertex formats you'll be using here:
typedef struct _MYVERTEX
{
    float x, y, z;     // screen position + Z-buffer depth
    DWORD Diffuse;     // diffuse color
    float tu, tv;           // DYNAMIC
     float tu_orig, tv_orig; // STATIC
    float rad, ang;         // STATIC
} MYVERTEX, *LPMYVERTEX;


typedef struct _WFVERTEX
{
    float x, y, z;
    DWORD Diffuse;   // diffuse color. also acts as filler; aligns struct to 16 bytes (good for random access/indexed prims)
} WFVERTEX, *LPWFVERTEX;


typedef struct _SPRITEVERTEX
{
    float x, y;      // screen position
    float z;         // Z-buffer depth
    DWORD Diffuse;   // diffuse color. also acts as filler; aligns struct to 16 bytes (good for random access/indexed prims)
    float tu, tv;    // texture coordinates for texture #0
} SPRITEVERTEX, *LPSPRITEVERTEX;

#define PROFILE_BEGIN
#define PROFILE_END(s)

#endif // __NULLSOFT_DX9_EXAMPLE_PLUGIN_SUPPORT_H__