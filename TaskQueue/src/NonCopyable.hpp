/*
 * Copyright (C) 2017 All rights reserved.
 * file : NonCopyable.hpp
 * author : zldeng@mioji.com
 * date : 2017-04-26
 * description : 
 */

#ifndef _NONCOPYABLE_H_
#define _NONCOPYABLE_H_

class NonCopyable {
 protected:
  NonCopyable() {
  }
  ~NonCopyable() {
  }
 private:
  NonCopyable(const NonCopyable& );
  const NonCopyable& operator=(const NonCopyable& );
}; // class NonCopyable

#endif // _NONCOPYABLE_H
