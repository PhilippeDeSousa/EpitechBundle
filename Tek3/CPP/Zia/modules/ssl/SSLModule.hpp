#pragma once

#include <openssl/ssl.h>
#include <openssl/err.h>

class SSLModule {
public:
  SSLModule();
  ~SSLModule();
  SSL_CTX *createContext();
  void configureContext(SSL_CTX *ctx);
  void secureClient(dems::Context &ctx);

private:
  SSL_CTX *_ctx;
};
