#include <stdio.h>
#include <iostream>
#include <unistd.h>
#include <string.h>
#include "Stage.hpp"
#include "SSLModule.hpp"

static constexpr char MODULE_NAME[] = "ssl-module";

SSLModule::SSLModule()
{
  SSL_load_error_strings();
  OpenSSL_add_ssl_algorithms();
  _ctx = createContext();
  configureContext(_ctx);
}

SSLModule::~SSLModule()
{
  EVP_cleanup();
}

SSL_CTX *SSLModule::createContext()
{
  const SSL_METHOD *method;
  SSL_CTX *ctx;

  method = SSLv23_server_method();

  ctx = SSL_CTX_new(method);
  if (!ctx) {
    perror("Unable to create SSL context");
    ERR_print_errors_fp(stderr);
    exit(EXIT_FAILURE);
  }

  return ctx;
}

void SSLModule::configureContext(SSL_CTX *ctx)
{
  SSL_CTX_set_ecdh_auto(ctx, 1);

  /* Set the key and cert */
  if (SSL_CTX_use_certificate_file(ctx, "cert.pem", SSL_FILETYPE_PEM) <= 0) {
    ERR_print_errors_fp(stderr);
    exit(EXIT_FAILURE);
  }

  if (SSL_CTX_use_PrivateKey_file(ctx, "key.pem", SSL_FILETYPE_PEM) <= 0) {
    ERR_print_errors_fp(stderr);
    exit(EXIT_FAILURE);
  }
}

void SSLModule::secureClient(dems::Context &ctx)
{
  SSL *ssl;
  int ret = 0;

  ssl = SSL_new(_ctx);
  SSL_set_fd(ssl, ctx.socketFd);
  ret = SSL_accept(ssl);

  if (ret <= 0) {
    int err = SSL_get_error(ssl, ret);
    std::cerr << "SSL_accept return: " << ret << std::endl;
    std::cerr << "ERROR: " << err << std::endl;
    if (err == SSL_ERROR_WANT_READ) {
      std::cout << "wait for data to read" << std::endl;
    }
    else if (err == SSL_ERROR_WANT_WRITE) {
      std::cout << "wait for data to write" << std::endl;
    }
    else if (err == SSL_ERROR_SYSCALL) {
      std::cout << "syscall error" << std::endl;
      exit(84);
    }
    else if (err == SSL_ERROR_SSL) {
      std::cout << "SSL ERROR" << std::endl;
      // exit(84);
    }
    else if (err == SSL_ERROR_ZERO_RETURN) {
      std::cout << "zero return" << std::endl;
      exit(84);
    }
    // exit(84);
  }
  else {
    const int rdSize = 4096;
    int total = 0;
    int rd;

    do {
      std::cout << "reading rawDATA" << std::endl;
      ctx.rawData.resize(ctx.rawData.size() + rdSize);
      rd = SSL_read(ssl, ctx.rawData.data() + total, rdSize);
      if (rd < 0)
        // gestion erreur
        if (rd < rdSize && rd > 0)
          ctx.rawData.resize(ctx.rawData.size() - (rdSize - rd));
      total += rd;
    } while (rd == rdSize);
  }
  for (auto r : ctx.rawData)
    std::cout << "print raw data: " << r << std::endl;
  std::cout << "done reading data\n";
  SSL_free(ssl);
}

void SSLFunc(dems::Context &ctx)
{
  SSLModule sslMod;

  sslMod.secureClient(ctx);
}

extern "C" {

std::string registerHooks(dems::StageManager &manager)
{
  manager.request().hookToFirst(0, MODULE_NAME, [](dems::Context &ctx) {
    std::cout << "Stage: Request FIRST" << std::endl;
    SSLFunc(ctx);
    std::cout << ctx.response.body << std::endl;
    return dems::CodeStatus::OK;
  });

  manager.request().hookToMiddle(0, MODULE_NAME, [](dems::Context &ctx) {
    std::cout << "Stage: Request MIDDLE" << std::endl;
    std::cout << ctx.response.body << std::endl;
    return dems::CodeStatus::OK;
  });

  manager.request().hookToEnd(0, MODULE_NAME, [](dems::Context &ctx) {
    std::cout << "Stage: Request END" << std::endl;
    std::cout << ctx.response.body << std::endl;
    return dems::CodeStatus::OK;
  });
  return MODULE_NAME;
}
};
