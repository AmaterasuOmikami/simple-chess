#pragma once

#include <windows.h>
#include <string>

class Engine {
 public:
  static void ConnectToEngine(char *path);

  static std::string GetNextMove(std::string fen_position);

  static void CloseConnection();

 private:
  static STARTUPINFO startup_info_;
  static SECURITY_ATTRIBUTES security_attributes_;
  static PROCESS_INFORMATION process_information_;
  static HANDLE pipin_w_, pipin_r_, pipout_w_, pipout_r_;
  static BYTE buffer_[2048];
  static DWORD write_, read_, available_;
};