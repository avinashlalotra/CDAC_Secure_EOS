#include "processevent.hpp"

void TtyResolver::loadDrivers() {
  driver_map.reserve(16);

  FILE *f = fopen("/proc/tty/drivers", "r");
  if (!f)
    return;

  char line[256];

  while (fgets(line, sizeof(line), f)) {

    char name[64];
    char prefix[64];
    int major;

    int n = sscanf(line, "%63s %63s %d", name, prefix, &major);

    if (n != 3)
      continue;

    driver_map[major] = std::string(prefix);
  }

  fclose(f);
}

std::string TtyResolver::resolve(int major, int minor) {
  auto it = driver_map.find(major);

  if (it == driver_map.end())
    return "Unknown";

  return it->second + "/" + std::to_string(minor);
}

void resolveTtyName(int32_t major, uint32_t index, char *out, size_t out_sz) {
  if (major == -1) {
    snprintf(out, out_sz, "None");
    return;
  }

  FILE *f = fopen("/proc/tty/drivers", "r");
  if (!f) {
    snprintf(out, out_sz, "Unknown");
    return;
  }

  char line[256];

  while (fgets(line, sizeof(line), f)) {

    char name[64], prefix[64];
    int maj;

    if (sscanf(line, "%63s %63s %d", name, prefix, &maj) < 3)
      continue;

    if (maj == major) {
      snprintf(out, out_sz, "%s/%u", prefix, index);
      fclose(f);
      return;
    }
  }

  fclose(f);
  snprintf(out, out_sz, "None");
}