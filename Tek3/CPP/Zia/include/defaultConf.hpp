#pragma once

#include <cstdint>

namespace zia {
constexpr const uint16_t DEFAULT_PORT = 80;
constexpr const std::size_t DEFAULT_MAX_CLIENTS = 1 << 13;
constexpr const char *DEFAULT_MODULE_PATH = "./modules";
constexpr const uint64_t DEFAULT_WATCHER_DELAY = 5000;
constexpr const char *DEFAULT_CONFIG_FILEPATH = "./zia.conf";
constexpr const int DEFAULT_POLL_TIMEOUT = 100;
} // namespace zia