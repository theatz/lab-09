//
// Created by mrbgn on 4/12/21.
//

#include <ThreadPool.hpp>


ThreadPool::ThreadPool(std::size_t workers_count) : _is_stopped(false) {
  for (std::size_t i = 0; i < workers_count; ++i) {
    _worker_threads.emplace_back([=] {
      while (true) {
        std::function<void()> task;
        {
          std::unique_lock<std::mutex> lock(_mutex);
          _available_to_job.wait(
              lock, [=] { return _is_stopped || !_tasks_queue.empty(); });
          if (_is_stopped && _tasks_queue.empty()) return;
          task = std::move(_tasks_queue.front());
          _tasks_queue.pop();
        }
        task();
      }
    });
  }
}

ThreadPool::~ThreadPool() {
  {
    std::unique_lock<std::mutex> lock(_mutex);
    _is_stopped = true;
  }
  _available_to_job.notify_all();
  for (auto &worker : _worker_threads) worker.join();
}
