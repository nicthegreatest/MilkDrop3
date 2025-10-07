#include "support.h"
#include "utility.h"
#include <wchar.h>
#include <glm/gtc/matrix_transform.hpp>

bool g_bDebugOutput = false;
bool g_bDumpFileCleared = false;

void MakeWorldMatrix( glm::mat4* pOut,
                      float xpos, float ypos, float zpos,
                      float sx,   float sy,   float sz,
                      float pitch, float yaw, float roll)
{
    *pOut = glm::mat4(1.0f);
    *pOut = glm::translate(*pOut, glm::vec3(xpos, ypos, zpos));
    *pOut = glm::rotate(*pOut, roll, glm::vec3(0.0f, 0.0f, 1.0f));
    *pOut = glm::rotate(*pOut, pitch, glm::vec3(1.0f, 0.0f, 0.0f));
    *pOut = glm::rotate(*pOut, yaw, glm::vec3(0.0f, 1.0f, 0.0f));
    *pOut = glm::scale(*pOut, glm::vec3(sx, sy, sz));
}

void MakeProjectionMatrix( glm::mat4* pOut,
                           const float near_plane, // Distance to near clipping plane
                           const float far_plane,  // Distance to far clipping plane
                           const float fov_horiz,  // Horizontal field of view angle, in radians
                           const float fov_vert)   // Vertical field of view angle, in radians
{
    float aspect = tanf(fov_horiz*0.5f) / tanf(fov_vert*0.5f);
    *pOut = glm::perspective(fov_vert, aspect, near_plane, far_plane);
}


void FormatSongTime(double seconds, char *dst)
{
    int millis = (int) seconds * 1000;
    // note: size(szSongLen[]) must be at least 64.
    dst[0] = 0;
    if (millis >= 0)
    {
		int len_s = millis/1000;
		int minutes = len_s/60;
		int seconds_rem = len_s - minutes*60;
		sprintf(dst, "%d:%02d", minutes, seconds_rem);
    }
}