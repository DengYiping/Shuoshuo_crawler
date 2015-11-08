//
//  threadtool.h
//
//
//  Created by Scott Deng on 8/14/15.
//  Copyright (c) 2015 Scott. All rights reserved.
//

#ifndef slave_threadtool_h
#define slave_threadtool_h
#include <thread>
#include <mutex>
#include <queue>
#include <stack>
#include <condition_variable>

namespace threadtool{
  template <typename T>
  class Threadsafe_queue{
  private:
    std::queue<T> raw_queue;
    mutable std::mutex mtx; //all mutex should be mutable
    std::condition_variable queue_cond;
  public:
    
    Threadsafe_queue(){}
    explicit Threadsafe_queue(const Threadsafe_queue& other){
      std::lock_guard<std::mutex> guardian1(other.mtx);
      raw_queue = other.raw_queue;
    }
    Threadsafe_queue(const std::queue<T>& other){
      raw_queue = other;
    }
    Threadsafe_queue operator=(const Threadsafe_queue&) = delete;
    
    void push(T data){
      std::lock_guard<std::mutex> locker(mtx);
      raw_queue.push(data);
      queue_cond.notify_one();
      return;
    }
    
    bool try_pop(T& data){
      std::lock_guard<std::mutex> locker(mtx);
      if(raw_queue.empty()) return false;
      
      data = raw_queue.front();
      return true;
    }
    std::shared_ptr<T> try_pop(){
      std::lock_guard<std::mutex> locker(mtx);
      if(raw_queue.empty()) return std::shared_ptr<T>();
      
      std::shared_ptr<T> res = std::make_shared<T>(raw_queue.front());
      raw_queue.pop();
      return res;
    }
    
    void wait_pop(T& data){
      std::unique_lock<std::mutex> locker(mtx);
      queue_cond.wait(locker,[this]{return !raw_queue.empty();});
      
      data = raw_queue.front();
      raw_queue.pop();
      return;
    }
    std::shared_ptr<T> wait_pop(){
      std::unique_lock<std::mutex> locker(mtx);
      queue_cond.wait(locker,[this]{return !raw_queue.empty();});
      
      std::shared_ptr<T> res = std::make_shared<T>(raw_queue.front());
      raw_queue.pop();
      return res;
    }
    
    bool empty() const{
      std::lock_guard<std::mutex> locker(mtx);
      return raw_queue.empty();
    }
    
  };
  
  class Thread_guard{
  private:
    std::thread& t;
  public:
    explicit Thread_guard(std::thread& t_): t(t_) {} //init thread guard
    
    ~Thread_guard(){
      if(t.joinable()) t.join();
    } //thread guard main function
    
    Thread_guard(Thread_guard const&) = delete; //copy control
    Thread_guard operator=(Thread_guard const&) = delete; //copy control
    
  };
  template<typename T>
  class Threadsafe_stack{
  private:
    std::stack<T> raw_stack;
    mutable std::mutex mtx;
    std::condition_variable stack_cond;
  public:
    Threadsafe_stack(){}
    explicit Threadsafe_stack(const Threadsafe_stack& other){
      std::lock_guard<std::mutex> guardian1(other.mtx);
      raw_stack = other.raw_queue;
    }
    explicit Threadsafe_stack(const std::stack<T>& other){
      raw_stack = other;
    }
    Threadsafe_stack operator=(const Threadsafe_stack& other) = delete;
    
    void push(T data){
      std::lock_guard<std::mutex> guardian(mtx);
      raw_stack.push(data);
      stack_cond.notify_one();
    }
    
    bool empty() const{
      std::lock_guard<std::mutex> guardian(mtx);
      return raw_stack.empty;
    }
    
    void wait_pop(T& data){
      std::unique_lock<std::mutex> locker(mtx);
      stack_cond.wait(locker,[this]{return !raw_stack.empty();});
      
      data = raw_stack.end();
      raw_stack.pop();
      return;
    }
    std::shared_ptr<T> wait_pop(){
      std::unique_lock<std::mutex> locker(mtx);
      stack_cond.wait(locker,[this]{return !raw_stack.empty();});
      
      std::shared_ptr<T> res = std::make_shared<T>(raw_stack.end());
      raw_stack.pop();
      return res;
    }
    
    bool try_pop(T& data){
      std::lock_guard<std::mutex> locker(mtx);
      if(raw_stack.empty()) return false;
      
      data = raw_stack.end();
      return true;
    }
    std::shared_ptr<T> try_pop(){
      std::lock_guard<std::mutex> locker(mtx);
      if(raw_stack.empty()) return std::shared_ptr<T>();
      
      std::shared_ptr<T> res = std::make_shared<T>(raw_stack.end());
      raw_stack.pop();
      return res;
    }
  };
}

#endif
