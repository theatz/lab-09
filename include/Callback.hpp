//
// Created by mrbgn on 4/12/21.
//

#ifndef PRODUCER_CONSUMER_CALLBACK_HPP
#define PRODUCER_CONSUMER_CALLBACK_HPP

#include <functional>
#include <utility>

template <typename task_t, typename... args_t>
inline auto CALLBACK(task_t&& task, args_t&&... args) {
  return std::bind(std::forward<task_t>(task), std::placeholders::_1,
                   std::forward<args_t>(args)...);
}

#endif  // PRODUCER_CONSUMER_CALLBACK_HPP
