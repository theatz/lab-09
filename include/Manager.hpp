//
// Created by mrbgn on 4/6/21.
//
#ifndef PRODUCER_CONSUMER_MANAGER_HPP
#define PRODUCER_CONSUMER_MANAGER_HPP

#include <Downloader.hpp>
#include <Parser.hpp>
#include <atomic>
#include <condition_variable>
//#include <future>
#include <mutex>
#include <queue>
#include <string>

#include "Downloader.hpp"
#include "Parser.hpp"
#include "Structs.hpp"
#include "ThreadPool.hpp"
#include "Callback.hpp"
#include "Task.hpp"

class Manager {
 public:
  Manager(std::size_t threadsMaxDownload, std::size_t threadsMaxParse,
          std::size_t depth);

  void CallbackDownload(const PageToParse& page);
  void CallbackParse(const PageOutput& output);

 private:
  // manage threads count
  std::size_t _threadsMaxDownload;
  std::size_t _threadsMaxParse;
  std::size_t _threadsMaxWrite;

  // manage threads
  //  ThreadPool
  ThreadPool _threadPoolDownload;
  ThreadPool _threadPoolParse;
  ThreadPool _threadPoolWrite;

  std::mutex _mutexDownload;
  std::mutex _mutexParse;

  // manage work
  bool _work;
  std::size_t _depth;
  Downloader _downloader;
  Parser _parser;
};

#endif  // PRODUCER_CONSUMER_MANAGER_HPP
