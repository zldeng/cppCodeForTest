/*
 * Copyright (C) 2017 All rights reserved.
 * file : TaskQueue.hpp
 * author : zldeng@mioji.com
 * date : 2017-05-04
 * description : 
 */

#ifndef _TASK_QUEUE_HPP_
#define _TASK_QUEUE_HPP_

#include "NonCopyable.hpp"
#include "Condition.hpp"
#include <queue>
#include "Task.hpp"
#include <vector>
#include <iostream>
#include <time.h>

class TaskQueue:NonCopyable
{
	public:
		class StopTask : public TaskInterface{
			public:
				StopTask()
				{
					priority = INT_MAX;
					is_stop_task = true;
					task_name = "stop_worker";
				}

				void run()
				{

				}

				void updatePriority()
				{
					priority = INT_MAX;
				}

				bool isDoTheTask()
				{
					return true;
				}
		};

		class Worker
		{
			private:
				TaskQueue* task_queue;
				pthread_t thread_;
				bool is_started;
				bool is_joined;

				static void* ThreadFunc(void* worker_data)
				{
					Worker* cand_worker = (Worker*)worker_data;

					cand_worker->run();
				}

			public:
				Worker(TaskQueue* cand_queue):task_queue(cand_queue){
					assert(task_queue);
					is_started = false;
					is_joined = false;
				}

				void JoinWorker()
				{
					if (!is_joined)
					{
						pthread_join(thread_,NULL);
						is_joined = true;
					}
				}

				void startWorker()
				{
					if (!is_started)
					{
						pthread_create(&thread_,NULL,ThreadFunc,this);
						is_started = true;
					}
				}

				virtual ~Worker()
				{
					if (is_started && !is_joined)
					{
						pthread_detach(thread_);
					}
				}

				virtual void run()
				{
					std::cerr << "worker_run begin:\n";
					while(true)
					{
						TaskInterface* cand_task = task_queue->getTask();
						
						//std::cerr << "beg run: " << static_cast<void*>(cand_task) << " name: "<< cand_task->task_name << std::endl;
						
						//the task queue is topped
						if (cand_task->is_stop_task)
						{
							//std::cerr << "stop_worker\n";
							delete cand_task;
							break;
						}

						try{
							if (cand_task->isDoTheTask())
							{
								//std::cerr << "run the worker\n";
								cand_task->run();
							}
							else
							{
								//std::cerr << "wait for next\n";
								sleep(1);
								cand_task->updatePriority();

								task_queue->addTask(cand_task);

								continue;
							}
						}catch (std::exception& e){
							std::cerr << "task_worker: " << e.what() << std::endl;
						}
						catch(...){
							std::cerr << "task worker unknoen exception.";
						}

						delete cand_task;
					}
				}

		};//end worker class

	private:
		mutable MutexLock task_mutex;
		Condition queue_condition;

		int worker_cnt;

		std::priority_queue<TaskInterface*,std::vector<TaskInterface*>,TaskCmp> task_priority_queue;

		friend class Worker;
		std::vector<Worker*> thread_worker_vec;

	public:
		TaskQueue(const int task_worker_cnt = 1):task_mutex(),queue_condition(task_mutex),
		worker_cnt(task_worker_cnt){
			assert(worker_cnt>0);
			for(size_t k = 0;k < task_worker_cnt;k++)
			{
				thread_worker_vec.push_back(new Worker(this));
			}
		}

		int getTaskCnt()
		{
			MutexLockGuard lock(task_mutex); 
			return task_priority_queue.size();
		}

		void addTask(TaskInterface* cand_task)
		{
			MutexLockGuard lock(task_mutex);
			task_priority_queue.push(cand_task);
			queue_condition.notifyAll();

			//std::cerr << "addTask: " << cand_task->task_name 
			//	<< " " << cand_task->priority << " " 
			//	<< task_priority_queue.size() << std::endl;
		}

		TaskInterface* getTask()
		{
			MutexLockGuard lock(task_mutex);
			while(task_priority_queue.empty())
			{
				queue_condition.wait();
			}

			TaskInterface* cand_task = task_priority_queue.top();
			task_priority_queue.pop();
		
			//std::cerr << "get a task:" << cand_task->task_name << "$$$" << std::endl;
			return cand_task;
		}

		void startWorker()
		{
			for(size_t k = 0;k < thread_worker_vec.size();k++)
			{
				thread_worker_vec[k]->startWorker();
			}
		}

		void StopWorker()
		{
			for(size_t k = 0 ;k < thread_worker_vec.size();k++)
			{
				StopTask* stop_task = new StopTask();
				addTask(stop_task);
			}

			for(size_t k = 0;k < thread_worker_vec.size();k++)
			{
				//wait for the worker finish current task
				thread_worker_vec[k]->JoinWorker();
				delete thread_worker_vec[k];
			}

			thread_worker_vec.clear();
		}
};


#endif
