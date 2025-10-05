#ifndef _WDLTYPES_H_
#define _WDLTYPES_H_

#include <stdint.h>

#ifndef _WIN32
  typedef intptr_t INT_PTR;
  typedef unsigned int DWORD;
  typedef unsigned short WORD;
  typedef unsigned char BYTE;
  typedef int BOOL;
  #define TRUE 1
  #define FALSE 0
#endif

#endif // _WDLTYPES_H_