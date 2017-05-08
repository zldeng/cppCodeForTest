/*
 * Copyright (C) 2017 All rights reserved.
 * file : MiojiVerifyRouter.cpp
 * author : zldeng@mioji.com
 * date : 2017-05-05
 * description : 
 */

#include "MiojiVerifyRouter.h"
#include <iostream>

using namespace std;

void VerifyRouterTask::run()
{
	const long cur = getNowTimestampMs(); 
	std::cout << "run the task " << task_name << "beg: " << request_beg_time_ms
		<< " time_o: " << request_timeout_seconds << " cur: " << cur 	<< " pro: " << priority << endl;
}

void VerifyRouterTask::updatePriority()
{
	const long cur_time_ms = getNowTimestampMs();
	priority = request_timeout_seconds - (cur_time_ms - request_beg_time_ms)/1000;
}

//detect where the task can be done right now
bool VerifyRouterTask::isDoTheTask()
{
	const long cur_time_ms = getNowTimestampMs();

	const int cost_seconds = (cur_time_ms - request_beg_time_ms)/1000;

	const int remain_seconds = request_timeout_seconds - cost_seconds;
	
	//std::cerr << "isDon: " << cost_seconds << "\t" << remain_seconds << endl;

	if (remain_seconds <= 3)
	{
		//std::cerr << "remian " << remain_seconds << " do it\n";
		return true;
	}
	else
	{
		//std::cerr << "remian " << remain_seconds << " wait\n";
		return false;
	}
}
