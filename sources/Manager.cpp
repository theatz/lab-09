//
// Created by mrbgn on 4/6/21.
//
#include <Manager.hpp>

Manager::Manager(uint32_t& threadsMaxDownload, uint32_t& threadsMaxParse,
                 uint32_t& depth)
    : _threadsMaxDownload(threadsMaxDownload),
      _threadsMaxParse(threadsMaxParse),
      _threadsMaxWrite(threadsMaxDownload),
      _threadPoolDownload(threadsMaxDownload),
      _threadPoolParse(threadsMaxParse),
      _threadPoolWrite(4),
      _work(true),
      _depth(depth),
      _downloader(_depth),
      _parser(_depth) {
  //  _work = true;

  //  Downloader Download(4);
  //  Parser Parse(4);

  //  ThreadPool DownloadPool(4);
  //  ThreadPool ParsePool(4);
  //  template <typename callback_t>

  //  DownloadPool.Execute()
//  _threadPoolDownload.execute(TASK(&Downloader::Download, _downloader,
//                                   UrlToDownload{"http://kremlin.ru", 1}),
//                              CALLBACK(&Manager::CallbackDownload, this);
}
template <typename callback_t>
void Manager::CallbackDownload(const PageToParse& page) {
  std::unique_lock<std::mutex> lock(_mutexDownload);
  _threadPoolParse.execute(TASK(&Parser::Parse, _parser, page),
                           CALLBACK(this->CallbackParse<callback_t>()));
  //  _threadPoolParse.Execute(TASK(&Parser::Parse, _parser, page));
}
template <typename callback_t>
void Manager::CallbackParse(const PageOutput& output) {
  std::unique_lock<std::mutex> lock(_mutexParse);
  for (auto& url : output.url) {
    _threadPoolDownload.execute(TASK(&Downloader::Download, _downloader, url),
                                CALLBACK(this->CallbackDownload<callback_t>()));
  }
}
template <typename callback_t>
void Manager::Start() {
  _threadPoolDownload.execute(TASK(&Downloader::Download, _downloader,
                                   UrlToDownload{"http://kremlin.ru", 1}),
                              CALLBACK(this->CallbackDownload<callback_t>()));
}
