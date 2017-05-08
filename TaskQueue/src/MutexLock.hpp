/*
 * Copyright (C) 2017 All rights reserved.
 * file : MutexLock.hpp
 * author : zldeng@mioji.com
 * date : 2017-04-26
 * description : 
 */

#ifndef _MUTEX_LOCK_HPP_
#define _MUTEX_LOCK_HPP_

#include <pthread.h>
#include <cassert>
#include "NonCopyable.hpp"

class MutexLock: NonCopyable {
 public:
  MutexLock() {
    assert(!pthread_mutex_init(&mutex_, NULL));
  }
  ~MutexLock() {
    assert(!pthread_mutex_destroy(&mutex_));
  }
  pthread_mutex_t* GetPthreadMutex() {
    return &mutex_;
  }

 private:
  void Lock() {
    assert(!pthread_mutex_lock(&mutex_));
  }
  void Unlock() {
    assert(!pthread_mutex_unlock(&mutex_));
  }
  friend class MutexLockGuard;

  pthread_mutex_t mutex_;
}; // class MutexLock

class MutexLockGuard: NonCopyable {
 public:
  explicit MutexLockGuard(MutexLock & mutex)
    : mutex_(mutex) {
    mutex_.Lock();
  }
  ~MutexLockGuard() {
    mutex_.Unlock();
  }
 private:
  MutexLock & mutex_;
}; // class MutexLockGuard

#endif // _MUTEX_LOCK_HPP_
