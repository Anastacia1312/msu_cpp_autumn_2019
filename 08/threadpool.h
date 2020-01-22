#include <iostream>
#include <vector>
#include <cstddef>
#include <functional>
#include <future>
#include <queue>
#include <thread>

class ThreadPool
{
private:
    std::vector<std::thread> threads;
    std::queue<std::function<void()>> tasks;
    std::mutex mut;
    std::condition_variable cond;
    bool flag;
    
public:
    explicit ThreadPool(size_t poolSize)
    {
        flag = true;
        for (size_t i = 0; i < poolSize; ++i)
        {
            threads.emplace_back([this]()
                {
                        while (flag)
                        {
                            std::unique_lock<std::mutex> lock(mut);
                            if (!tasks.empty())
                            {
                                auto task = tasks.front();
                                tasks.pop();
                                lock.unlock();
                                task();
                            } else {
                                cond.wait(lock);
                            }
                        }
                });
        }
    }
    
    ~ThreadPool()
    {
        flag = false;
        cond.notify_all();
        for (auto& thread : threads)
        {
            thread.join();
        }
    }
    
    template <class Func, class... Args>
    auto exec(Func func, Args... args) -> std::future<decltype(func(args...))>
    {
        using typeReturn = decltype(func(args...));
        using typeP = std::packaged_task<typeReturn ()>;
        auto task = std::make_shared<typeP>([func, args...]()
        {
            return func(args...);
        });
        {
            std::lock_guard<std::mutex> lock(mut);
            tasks.emplace(
                    [task]()
                    {
                        (*task)();
                    });
        }
        cond.notify_one();
        return task -> get_future();
    }

};