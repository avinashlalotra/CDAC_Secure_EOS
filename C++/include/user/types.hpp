#ifndef TYPES_HPP
#define TYPES_HPP

#include <stdint.h>
#include <string>
#include <unordered_map>
#include <vector>

struct user_space_filter {
  std::unordered_map<std::string, uint8_t> exclude_extension;
  std::vector<std::string> exclude_suffix;
  std::vector<std::string> exclude_prefix;
  std::vector<std::string> exclude_pattern;
};

struct Packet {

  std::string full_path;
  std::string ip_address;
  std::string tty;
  std::string before_size;
  std::string file_size;
  std::string event_type;
  std::string timestamp;
  std::string username;
};

#endif
