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

#include "Callback.hpp"
#include "Downloader.hpp"
#include "Parser.hpp"
#include "Structs.hpp"
#include "Task.hpp"
#include "Writer.hpp"
#include "ThreadPool.hpp"


class Manager {
 public:
  Manager(uint32_t& threadsMaxDownload, uint32_t& threadsMaxParse, uint32_t& depth);

  template <typename callback_t>
  void Start();
  template <typename callback_t>
  void CallbackDownload(const PageToParse& page);
  template <typename callback_t>
  void CallbackParse(const PageOutput& output);

 private:
  // manage threads count
  uint32_t _threadsMaxDownload;
  uint32_t _threadsMaxParse;
  uint32_t _threadsMaxWrite;

  // manage threads
  //  ThreadPool
  ThreadPool _threadPoolDownload;
  ThreadPool _threadPoolParse;
  ThreadPool _threadPoolWrite;


  // manage work
  bool _work;
  uint32_t _depth;
  Downloader _downloader;
  Parser _parser;

  std::mutex _mutexDownload;
  std::mutex _mutexParse;
};

#endif  // PRODUCER_CONSUMER_MANAGER_HPP
