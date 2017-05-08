/*
 * Copyright (C) 2017 All rights reserved.
 * file : MiojiVerifyRouter.h
 * author : zldeng@mioji.com
 * date : 2017-05-05
 * description : 
 */

#ifndef _MIOJI_VERIFY_ROUTER_H_
#define _MIOJI_VERIFY_ROUTER_H_

#include "Task.hpp"
#include <cstring>
#include <iostream>

class VerifyRouterTask: public TaskInterface
{
	private:
		long request_beg_time_ms;
		long request_timeout_seconds;
	
	public:
		VerifyRouterTask(const long req_begin_time_ms,const long req_timeout_seconds,const std::string& name)
		{
			is_stop_task = false; //must set the flag to false or the worker will stop the thread and drop the last task

			request_beg_time_ms = req_begin_time_ms;
			request_timeout_seconds = req_timeout_seconds;
			task_name = name;
			
			const long cur_time_ms = getNowTimestampMs();

			priority = request_timeout_seconds - (cur_time_ms - req_begin_time_ms)/1000;

			std::cerr << req_begin_time_ms << "\t" << cur_time_ms << "\t" << priority << std::endl;
		}

		void run();
		void updatePriority();
		bool isDoTheTask();
};

#endif
