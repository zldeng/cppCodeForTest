/*
 * Copyright (C) 2017 All rights reserved.
 * file : Task.hpp
 * author : zldeng@mioji.com
 * date : 2017-05-04
 * description : 
 */

#ifndef _TASK_H_
#define _TASK_H_

#include <climits>
#include <string>
#include "tool.h"

class TaskInterface
{
	public:
		virtual ~TaskInterface(){}

		virtual void run() = 0;
		virtual void updatePriority() = 0;

		//detect whether the task is available for doing
		//if not, call updatePriority to update priority and push the task to takQueue
		virtual bool isDoTheTask() = 0;

		int priority;
		bool is_stop_task;
		std::string task_name;
};


class TaskCmp
{
	public:
		bool operator()(const TaskInterface* task_1,const TaskInterface* task_2) const
		{
			return task_1->priority > task_2->priority;
		}
};



#endif
