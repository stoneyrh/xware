/*
* ****************************************************************************
* *                                                                          *
* * Copyright 2008, xWorkshop Inc.                                           *
* * All rights reserved.                                                     *
* * Redistribution and use in source and binary forms, with or without       *
* * modification, are permitted provided that the following conditions are   *
* * met:                                                                     *
* *    * Redistributions of source code must retain the above copyright     *
* * notice, this list of conditions and the following disclaimer.            *
* *    * Redistributions in binary form must reproduce the above             *
* * copyright notice, this list of conditions and the following disclaimer   *
* * in the documentation and/or other materials provided with the            *
* * distribution.                                                            *
* *    * Neither the name of xWorkshop Inc. nor the names of its             *
* * contributors may be used to endorse or promote products derived from     *
* * this software without specific prior written permission.                 *
* * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS     *
* * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT        *
* * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR    *
* * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT     *
* * OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,    *
* * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT         *
* * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,    *
* * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY    *
* * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT      *
* * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE    *
* * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.     *
* *                                                                          *
* * Author: stoneyrh@163.com                                                 *
* *                                                                          *
* ****************************************************************************
*/

#ifndef _X_SAFE_QUEUE_H_
#define _X_SAFE_QUEUE_H_

#include <queue>
#include "xmutex.h"
#include "xcondition_variable.h"

namespace xws
{

template <class T>
class xsafe_queue
{
    public:
        xsafe_queue() {}
        ~xsafe_queue() {}

        // Get object with wait
        T get()
        {
            xscoped_lock lock(mutex_);
            // Wait until there is an object
            // Need a loop here because the condition variable can be subject to supurious wake-up
            while (queue_.empty())
            {
                condition_.wait(lock);
            }
            // Make a copy
            T obj(queue_.front());
            // Delete the original one
            queue_.pop();
            // Returning the object doesn't need the lock, so release it here
            lock.unlock();
            return obj;
        }

        // Get the object without wait
        bool get(T& obj)
        {
            xscoped_lock lock(mutex_);
            if (queue_.empty())
            {
                return false;
            }
            obj = queue_.front();
            // Delete the original one
            queue_.pop();
            // Returning the object doesn't need the lock, so release it here
            lock.unlock();
            return true;
        }

        // Put object into the queue
        void put(const T& obj)
        {
            xscoped_lock lock(mutex_);
            bool was_empty = queue_.empty();
            queue_.push(obj);
            // Unlock the lock, because when the waiting thread being notified
            // It may wake up immediately, if the lock is still locked, it has
            // to wait on requiring the lock when exiting the wait function
            lock.unlock();
            // Only notify the thread when the list was empty
            if (was_empty)
            {
                condition_.notify_one();
            }
        }

        size_t size()
        {
            xscoped_lock lock(mutex_);
            return queue_.size();
        }

        bool empty()
        {
            xscoped_lock lock(mutex_);
            return queue_.empty();
        }

        void clear()
        {
            xscoped_lock lock(mutex_);
            while (!queue_.empty())
            {
                queue_.pop();
            }
        }
    private:
        std::queue<T> queue_;
        xmutex mutex_;
        xcondition_variable condition_;
};

} // namespace xws

#endif
