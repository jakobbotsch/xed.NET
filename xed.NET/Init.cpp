#include "Stdafx.h"

struct __declspec(dllexport) Init
{
    Init() { xed_tables_init(); }
};

Init init;