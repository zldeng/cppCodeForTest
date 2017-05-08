/*
 * Copyright (C) 2017 All rights reserved.
 * file : tool.cpp
 * author : zldeng@mioji.com
 * date : 2017-05-08
 * description : 
 */

#include "tool.h"
#include <stdlib.h>
#include <sys/time.h>

long getNowTimestampMs()
{
	timeval t;
	gettimeofday(&t,NULL);
	return t.tv_sec*1000 + t.tv_usec/1000;

}

