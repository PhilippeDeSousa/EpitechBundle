#include <string.h>
#include <cstdio>
#include <errno.h>
#include <iostream>
#include "trace.hpp"
#include "Stage.hpp"

static constexpr char MODULE_NAME[] = "php-module";

static size_t readFromStream(std::string &dest, FILE *src)
{
  size_t rd;
  size_t total = 0;
  char buffer[4096];

  do {
    rd = fread(buffer, sizeof(*buffer), sizeof(buffer), src);
    dest.append(buffer, rd);
    total += rd;
  } while (rd == sizeof(buffer));
  return total;
}

static bool phpModule(dems::Context &ctx)
{
  std::string command("php-cgi " + ctx.request.body); // parser le body
  std::string output;
#ifdef __linux__
  FILE *stream = popen(command.c_str(), "r");
#else
  FILE *stream = _popen(command.c_str(), "r");
#endif
  if (stream == NULL)
    return false;
  if (readFromStream(output, stream) > 0) {
    ctx.response.body += output; // pour qu'il y est tout dedans
  }
  fclose(stream);
  return true;
}

extern "C" {

std::string registerHooks(dems::StageManager &manager)
{
  manager.request().hookToFirst(0, MODULE_NAME, [](dems::Context &ctx) {
    return dems::CodeStatus::OK;
  });

  manager.request().hookToMiddle(0, MODULE_NAME, [](dems::Context &ctx) {
    phpModule(ctx);
    return dems::CodeStatus::OK;
  });

  manager.request().hookToEnd(0, MODULE_NAME, [](dems::Context &ctx) {
    return dems::CodeStatus::OK;
  });
  return MODULE_NAME;
}
};
