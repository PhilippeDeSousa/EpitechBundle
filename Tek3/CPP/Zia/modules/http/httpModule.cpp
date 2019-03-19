#include "httpModule.hpp"
#include <iostream>
#include <sstream>
#include <fstream>
#include <time.h>
#include <cstring>
#include <filesystem>

static constexpr char MODULE_NAME[] = "http-module";

httpModule::httpModule()
{
	_reqTypes.insert(_reqTypes.end(), { "GET", "HEAD", "POST", "PUT",
		"DELETE", "CONNECT", "OPTIONS", "TRACE"});
}

dems::Context& httpModule::getContextRequest(dems::Context &ctx)
{
	std::string reqStr(ctx.rawData.begin(), ctx.rawData.end());

	//test printing
	//printRequest(reqStr);

	//build http request from string
	std::vector<std::string> reqParts = getRequestParts(reqStr);
	if (reqParts.size() < 5)
		return ctx;
	dems::header::Request req;
	req.method = reqParts[0];
	req.path = reqParts[2];
	req.httpVersion = reqParts[4];
	ctx.request.firstLine = req;
	getResponse(ctx);
	return ctx;
}

void httpModule::getResponse(dems::Context &ctx)
{
	time_t tnow = time(nullptr);
	char buffer[128] = {0};
	struct tm *localt = localtime(&tnow);
	std::ifstream file("index.html");
	std::string s((char *)ctx.rawData.data(), (size_t)ctx.rawData.size());
	std::stringstream ss(s);
	strftime(buffer, sizeof(buffer), "%a, %d %b %Y %T", localt);
	size_t filesize = std::filesystem::file_size("index.html");

	if (!file.is_open()) {
		std::cout << "failed to open index.html";
		return ;
	}
	ctx.rawData.clear();
	ss << "HTTP/1.1 200 OK\n" << "Date: " << buffer << " GMT\n";
	ss << "Server: lserver zia\n" << "Last-Modified: " << buffer << "GMT\n";
	ss << "Content-Length: " << filesize << "\n";
	ss << "Content-Type: text/html; charset=UTF8\n";
	ss << "Connection: Closed\n\n";
	ss << file.rdbuf();
	ctx.rawData.resize(ss.str().size());
	::memcpy(ctx.rawData.data(), ss.str().c_str(), ss.str().size());
	file.close();
}

std::vector<std::string> httpModule::getRequestParts(std::string &req)
{
	std::vector<std::string > reqParts;
	std::string delim = " ";
	size_t pos = 0;
	std::string token;

	while ((pos = req.find(delim)) != std::string::npos) {
		reqParts.push_back(req.substr(0, pos));
		req.erase(0, pos + delim.length());
	}
	reqParts.push_back(req);
	if (checkRequestSyntax(reqParts) == false)
		reqParts.clear();
	return reqParts;
}

bool httpModule::checkRequestSyntax(std::vector<std::string> &reqParts)
{
	auto i = _reqTypes.begin();

	if (reqParts.size() < 5){
		std::cerr << "ERROR: invalid http request size" << std::endl;
		return false;
	}
	while (i != _reqTypes.end() && reqParts[0] != *i)
		i++;
	if (i == _reqTypes.end()) {
		std::cerr << "ERROR: invalid http request method" << std::endl;
		return false;
	}
	return true;
}

void httpModule::printRequest(std::string &req)
{
	std::cout << req << std::endl;
}

void httpModule::printRequest(std::vector<std::string> &req)
{
	auto i = req.begin();
	while (i != req.end()) {
		std::cout << *i << std::endl;
		i++;
	}
}

extern "C" {

std::string registerHooks(dems::StageManager &manager)
{
  manager.request().hookToFirst(0, MODULE_NAME, [](dems::Context &ctx) {
	httpModule http;
	http.getContextRequest(ctx);
	return dems::CodeStatus::OK;
  });

  manager.request().hookToMiddle(0, MODULE_NAME, [](dems::Context &ctx) {
    return dems::CodeStatus::OK;
  });

  manager.request().hookToEnd(0, MODULE_NAME, [](dems::Context &ctx) {
    return dems::CodeStatus::OK;
  });
  return MODULE_NAME;
}
};
