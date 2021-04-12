//
// Created by mrbgn on 4/6/21.
//
#include <Manager.hpp>

Manager::Manager(std::size_t threadsMaxDownload, std::size_t threadsMaxParse,
                 std::size_t depth)
    : _threadsMaxDownload(threadsMaxDownload),
      _threadsMaxParse(threadsMaxParse),
      _threadPoolDownload(threadsMaxDownload),
      _threadPoolParse(threadsMaxParse),
      _threadPoolWrite(4),
      _depth(depth),
      _downloader(_depth),
      _parser(_depth),
      _work(true){
  //  _work = true;

  //  Downloader Download(4);
  //  Parser Parse(4);

  //  ThreadPool DownloadPool(4);
  //  ThreadPool ParsePool(4);
  _threadPoolDownload.Execute(TASK(&Downloader::Download, _downloader, UrlToDownload{"http://kremlin.ru", 1}),
                              CALLBACK(&Manager::CallbackDownload, this));
  //  DownloadPool.Execute()
}

void Manager::CallbackDownload(const PageToParse& page) {
  std::unique_lock<std::mutex> lock(_mutexDownload);
  _threadPoolParse.Execute(TASK(&Parser::Parse, _parser, page),
                           CALLBACK(&Manager::CallbackParse, this));
  //  _threadPoolParse.Execute(TASK(&Parser::Parse, _parser, page));
}
void Manager::CallbackParse(const PageOutput& output) {
  std::unique_lock<std::mutex> lock(_mutexParse);
  for (auto& url : output.url) {
    _threadPoolDownload.Execute(TASK(&Downloader::Download, _downloader, url),
                                CALLBACK(&Manager::CallbackDownload, this));
  }
}
