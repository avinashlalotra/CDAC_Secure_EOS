#ifndef PROCESS_EVENT_HPP
#define PROCESS_EVENT_HPP

#include <bpf/libbpf.h>
#include <cstdio>
#include <cstring>
#include <string>
#include <unordered_map>

class TtyResolver {

private:
  std::unordered_map<int, std::string> driver_map;

public:
  void loadDrivers();
  std::string resolve(int major, int minor);
};

#endif