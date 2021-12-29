#pragma once

#include <stdio.h>
#include <windows.h>
#include <tlhelp32.h> // Alternative for tlhelp32?

#include <fstream> 

#define errorf(fmt, ...) fprintf(stderr, "\n[error at %s:%d] " fmt, __FILE__, __LINE__, ##__VA_ARGS__)
#define StrToWStr(s) (std::wstring(s, &s[strlen(s)]).c_str())

#include "utils.h"
#include "map.h"
#include "hijack.h"