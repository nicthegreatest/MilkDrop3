#ifndef __WASABI_H__
#define __WASABI_H__

#include <string>

// Function to retrieve a localized string from the language pack
const char* wasabiApiLangString(int resource_id, char* buf, int buf_len);

#endif // __WASABI_H__