/*
 * Copyright (C) 2017 All rights reserved.
 * file : test_task.cpp
 * author : zldeng@mioji.com
 * date : 2017-05-05
 * description : 
 */


#include <iostream>
#include "TaskQueue.hpp"
#include "MiojiVerifyRouter.h"
#include <time.h>

int main()
{
	TaskQueue task_queue(1);
	
	const long beg_time = getNowTimestampMs();

	VerifyRouterTask* task_1 = new VerifyRouterTask(beg_time,15,"1_task");
	VerifyRouterTask* task_2 = new VerifyRouterTask(beg_time,20,"2_task");
	VerifyRouterTask* task_3 = new VerifyRouterTask(beg_time,5,"3_task");
	VerifyRouterTask* task_4 = new VerifyRouterTask(beg_time,10,"4_task");
	
	task_queue.addTask(task_1);
	task_queue.addTask(task_2);
	task_queue.addTask(task_3);
	task_queue.addTask(task_4);

	task_queue.startWorker();
	
	sleep(3);
	VerifyRouterTask* task_5 = new VerifyRouterTask(beg_time,8,"5_task");
	task_queue.addTask(task_5);
	
	std::cerr << "stop_task\n";

	task_queue.StopWorker();

	std::cerr << "hello world!\n";

	return 0;
}
