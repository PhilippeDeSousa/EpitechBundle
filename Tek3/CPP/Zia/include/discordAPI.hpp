#pragma once

#include <string>
#include <unordered_map>

#include "discord_register.h"
#include "discord_rpc.h"

class DiscordAPI {
public:
  DiscordAPI(const std::string &AppId) noexcept;
  ~DiscordAPI() noexcept;
  void setState(const std::string &state) noexcept;
  void setDetails(const std::string &details) noexcept;
  void setLargeImageKey(const std::string &key) noexcept;
  void setLargeImageText(const std::string &text) noexcept;
  void setSmallImageKey(const std::string &key) noexcept;
  void setSmallImageText(const std::string &text) noexcept;
  void setPartyId(const std::string &id) noexcept;
  void setPartySize(int size) noexcept;
  void setPartyMax(int size) noexcept;
  void startTimer() noexcept;
  void durationTimer(int seconds) noexcept;
  void resetTimer() noexcept;
  void update() noexcept;

private:
  std::unordered_map<std::string, std::string> _map;
  DiscordRichPresence _drp;
  DiscordEventHandlers _handlers;
  std::string _app;
  std::string _cmd;
};