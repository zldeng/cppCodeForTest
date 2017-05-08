/*
 * Copyright (C) 2017 All rights reserved.
 * file : Condition.h
 * author : zldeng@mioji.com
 * date : 2017-05-04
 * description : 
 */

#ifndef _CONDITION_H_
#define _CONDITION_H_

#include "NonCopyable.hpp"
#include <pthread.h>
#include "MutexLock.hpp"

class Condition : NonCopyable
{
	private:
		mutable MutexLock& cond_mutex;
		pthread_cond_t p_condition;

	public:
		explicit Condition(MutexLock& cand_mutex):cond_mutex(cand_mutex){
			pthread_cond_init(&p_condition,NULL);
		}

		~Condition()
		{
			pthread_cond_destroy(&p_condition);
		}

		void wait()
		{
			pthread_cond_wait(&p_condition,cond_mutex.GetPthreadMutex());
		}

		void notify()
		{
			pthread_cond_signal(&p_condition);
		}

		void notifyAll()
		{
			pthread_cond_broadcast(&p_condition);
		}
};

#endif
