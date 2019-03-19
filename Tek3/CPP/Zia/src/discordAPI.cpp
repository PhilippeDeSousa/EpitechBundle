#include <cstring>

#include "discordAPI.hpp"
#include "trace.hpp"

#define DISCORD_NAME "[" BOLDBLUE "Discord" RESET "] "

static void DrpEvtReady(const DiscordUser *request) noexcept
{
  trace(true, DISCORD_NAME "Connected to user %s#%s - %s\n", request->username,
        request->discriminator, request->userId);
}

static void DrpEvtDisconnect(int errcode, const char *message) noexcept
{
  trace(true, DISCORD_NAME "Disconnected (%d: %s)\n", errcode, message);
}

static void DrpEvtErrored(int errcode, const char *message) noexcept
{
  trace(true, DISCORD_NAME "Error (%d: %s)\n", errcode, message);
}

static void DrpEvtJoinGame(const char *joinSecret) noexcept
{
  (void)joinSecret;
}

static void DrpEvtSpectateGame(const char *spectateSecret) noexcept
{
  (void)spectateSecret;
}

static void DrpEvtJoinRequest(const DiscordUser *request) noexcept
{
  (void)request;
}

DiscordAPI::DiscordAPI(const std::string &AppId) noexcept
        : _app(AppId)
{
  Discord_Initialize(_app.c_str(), &_handlers, 1, nullptr);
  _handlers.disconnected = DrpEvtDisconnect;
  _handlers.errored = DrpEvtErrored;
  _handlers.joinGame = DrpEvtJoinGame;
  _handlers.joinRequest = DrpEvtJoinRequest;
  _handlers.ready = DrpEvtReady;
  _handlers.spectateGame = DrpEvtSpectateGame;
  std::memset(&_drp, 0, sizeof(_drp));
  update();
}

DiscordAPI::~DiscordAPI() noexcept
{
  Discord_Shutdown();
}

void DiscordAPI::setState(const std::string &state) noexcept
{
  _map["state"] = state;
  _drp.state = _map["state"].c_str();
}

void DiscordAPI::setDetails(const std::string &details) noexcept
{
  _map["details"] = details;
  _drp.details = _map["details"].c_str();
}

void DiscordAPI::setLargeImageKey(const std::string &key) noexcept
{
  _map["largeImageKey"] = key;
  _drp.largeImageKey = _map["largeImageKey"].c_str();
}

void DiscordAPI::setLargeImageText(const std::string &text) noexcept
{
  _map["largeImageText"] = text;
  _drp.largeImageText = _map["largeImageText"].c_str();
}

void DiscordAPI::setSmallImageKey(const std::string &key) noexcept
{
  _map["smallImageKey"] = key;
  _drp.smallImageKey = _map["smallImageKey"].c_str();
}

void DiscordAPI::setSmallImageText(const std::string &text) noexcept
{
  _map["smallImageText"] = text;
  _drp.smallImageText = _map["smallImageText"].c_str();
}

void DiscordAPI::setPartyId(const std::string &id) noexcept
{
  _map["partyId"] = id;
  _drp.partyId = _map["partyId"].c_str();
}

void DiscordAPI::setPartySize(int size) noexcept
{
  _drp.partySize = size;
}

void DiscordAPI::setPartyMax(int size) noexcept
{
  _drp.partyMax = size;
}

void DiscordAPI::startTimer() noexcept
{
  _drp.startTimestamp = time(NULL);
}

void DiscordAPI::durationTimer(int seconds) noexcept
{
  _drp.endTimestamp = _drp.startTimestamp + seconds;
}

void DiscordAPI::resetTimer() noexcept
{
  _drp.startTimestamp = time(NULL);
  _drp.endTimestamp = 0;
}

void DiscordAPI::update() noexcept
{
  Discord_UpdatePresence(&_drp);
  Discord_UpdateHandlers(&_handlers);
  trace(true, DISCORD_NAME "updating rich presence...\n");
}