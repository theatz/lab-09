//
// Created by mrbgn on 4/12/21.
//

#ifndef PRODUCER_CONSUMER_THREADPOOL_HPP
#define PRODUCER_CONSUMER_THREADPOOL_HPP

#include <condition_variable>
#include <functional>
#include <future>
#include <memory>
#include <mutex>
#include <queue>
#include <thread>
#include <vector>


class ThreadPool {
 public:
  explicit ThreadPool(
      std::size_t workers_count = std::thread::hardware_concurrency());
  ~ThreadPool();

  template <typename task_t, typename callback_t>
  void execute(task_t&& task, callback_t&& callback) {
    auto workers_task = std::make_shared<std::packaged_task<void()>>(std::bind(
        std::forward<callback_t>(callback), std::forward<task_t>(task)));

    {
      std::unique_lock<std::mutex> lock(_mutex);
      _tasks_queue.emplace([workers_task] { (*workers_task)(); });
    }
    _available_to_job.notify_one();
  }

 private:
  std::vector<std::thread> _worker_threads;
  std::queue<std::function<void()>> _tasks_queue;
  std::mutex _mutex;
  std::condition_variable _available_to_job;
  bool _is_stopped;
};

#endif  // PRODUCER_CONSUMER_THREADPOOL_HPP
