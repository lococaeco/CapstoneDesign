#ifndef PARSER_H
#define PARSER_H
#pragma once

#include "global/global.h"

void* ImuParserWrapper(void* p_Arg);
void* LidarParserWrapper(void* p_Arg);
void* SlamParserWrapper(void* p_Arg);
void* SerialParserWrapper(void* p_Arg);
void* ObjectParserWrapper(void* p_Arg);

#endif
