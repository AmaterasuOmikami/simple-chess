#include "engine.hpp"

STARTUPINFO Engine::startup_info_;
SECURITY_ATTRIBUTES Engine::security_attributes_;
PROCESS_INFORMATION Engine::process_information_;
HANDLE Engine::pipin_w_, Engine::pipin_r_, Engine::pipout_w_, Engine::pipout_r_;
BYTE Engine::buffer_[2048];
DWORD Engine::write_, Engine::read_, Engine::available_;

void Engine::ConnectToEngine(char *path) {
  pipin_w_ = pipin_r_ = pipout_w_ = pipout_r_ = nullptr;
  security_attributes_.nLength = sizeof(security_attributes_);
  security_attributes_.bInheritHandle = TRUE;
  security_attributes_.lpSecurityDescriptor = nullptr;

  CreatePipe(&pipout_r_, &pipout_w_, &security_attributes_, 0);
  CreatePipe(&pipin_r_, &pipin_w_, &security_attributes_, 0);

  startup_info_.dwFlags = STARTF_USESHOWWINDOW | STARTF_USESTDHANDLES;
  startup_info_.wShowWindow = SW_HIDE;
  startup_info_.hStdInput = pipin_r_;
  startup_info_.hStdOutput = pipout_w_;
  startup_info_.hStdError = pipout_w_;

  CreateProcess(nullptr,
                path,
                nullptr,
                nullptr,
                true,
                0,
                nullptr,
                nullptr,
                &startup_info_,
                &process_information_);
}

std::string Engine::GetNextMove(std::string fen_position) {
  std::string str;
  fen_position = "position fen " + fen_position + "\ngo depth 5\n";

  WriteFile(pipin_w_,
            fen_position.c_str(),
            fen_position.length(),
            &write_,
            nullptr);
  Sleep(500);

  PeekNamedPipe(pipout_r_,
                buffer_,
                sizeof(buffer_),
                &read_,
                &available_,
                nullptr);
  do {
    ZeroMemory(buffer_, sizeof(buffer_));
    if (!ReadFile(pipout_r_, buffer_, sizeof(buffer_), &read_, nullptr)
        || !read_)
      break;
    buffer_[read_] = 0;
    str += (char *) buffer_;
  } while (read_ >= sizeof(buffer_));

  int n = static_cast<int>(str.find("bestmove"));
  if (n != -1) return str.substr(n + 9, 5);

  return "error";
}

void Engine::CloseConnection() {
  WriteFile(pipin_w_, "quit\n", 5, &write_, nullptr);
  if (pipin_w_ != nullptr) CloseHandle(pipin_w_);
  if (pipin_r_ != nullptr) CloseHandle(pipin_r_);
  if (pipout_w_ != nullptr) CloseHandle(pipout_w_);
  if (pipout_r_ != nullptr) CloseHandle(pipout_r_);
  if (process_information_.hProcess != nullptr)
    CloseHandle(process_information_.hProcess);
  if (process_information_.hThread != nullptr)
    CloseHandle(process_information_.hThread);
}
