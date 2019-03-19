#define CATCH_CONFIG_MAIN
#include <single_include/catch2/catch.hpp>

#include "CBuffer.hpp"
#include "SharedModules.hpp"
#include "SharedObject.hpp"

TEST_CASE("constructor", "[CBuffer]")
{
  CBuffer buffer(512);

  REQUIRE(buffer.size() == 0);
  REQUIRE(buffer.sizeLeft() == 512);
}

TEST_CASE("write 1", "[CBuffer]")
{
  CBuffer buffer(1);

  REQUIRE(buffer.write("toto", 4) == 1);
  REQUIRE(buffer.write("salut", 5) == 0);
  REQUIRE(buffer.write("", 0) == 0);
  REQUIRE(buffer.write("LAHO", 1) == 0);
}

TEST_CASE("write 10", "[CBuffer]")
{
  CBuffer buffer(10);

  REQUIRE(buffer.write("toto", 4) == 4);
  REQUIRE(buffer.write("salut", 5) == 5);
  REQUIRE(buffer.write("", 0) == 0);
  REQUIRE(buffer.write("LAHO", 1) == 1);
  REQUIRE(buffer.write("jambon", 6) == 0);
  REQUIRE(buffer.write("LAHO", 2) == 0);
}

TEST_CASE("read write", "[CBuffer]")
{
  CBuffer buffer(10);
  char s[10];

  REQUIRE(buffer.write("jambe", 5) == 5);
  REQUIRE(buffer.write("poto", 4) == 4);
  REQUIRE(buffer.read(s, 3) == 3);
  REQUIRE(strncmp(s, "jam", 3) == 0);
  REQUIRE(buffer.read(s, 5) == 5);
  REQUIRE(strncmp(s, "bepot", 5) == 0);
  REQUIRE(buffer.read(s, 10) == 1);
  REQUIRE(strncmp(s, "o", 1) == 0);
}

TEST_CASE("", "[CBuffer]")
{
  CBuffer buffer(10);
  char s[10];

  REQUIRE(buffer.write("banane", 6) == 6);
  REQUIRE(buffer.read(s, 10) == 6);
  REQUIRE(strncmp(s, "banane", 6) == 0);
}

TEST_CASE("write too long", "[CBuffer]")
{
  CBuffer buffer(10);
  char s[10];

  REQUIRE(buffer.write("potatoes la magnifique", 22) == 10);
  REQUIRE(buffer.read(s, 10) == 10);
  REQUIRE(strncmp(s, "potatoes l", 10) == 0);
}

TEST_CASE("write full", "[CBuffer]")
{
  CBuffer buffer(10);
  char s[10];

  REQUIRE(buffer.write("salut les potes", 10) == 10);
  REQUIRE(buffer.write("peau de banane", 7) == 0);
  REQUIRE(buffer.read(s, 10) == 10);
  REQUIRE(strncmp(s, "salut les ", 10) == 0);
}

TEST_CASE("read empty", "[CBuffer]")
{
  CBuffer buffer(10);
  char s[10];

  REQUIRE(buffer.read(s, 10) == 0);
  REQUIRE(buffer.write("yolo", 4) == 4);
  REQUIRE(buffer.read(s, 4) == 4);
  REQUIRE(strncmp(s, "yolo", 4) == 0);
  REQUIRE(buffer.read(s, 4) == 0);
  REQUIRE(strncmp(s, "yolo", 4) == 0);
  REQUIRE(buffer.read(s, 10) == 0);
  REQUIRE(strncmp(s, "yolo", 4) == 0);
  REQUIRE(buffer.read(s, 345645) == 0);
  REQUIRE(strncmp(s, "yolo", 4) == 0);
}

TEST_CASE("Size left", "[CBuffer]")
{
  CBuffer buffer(10);
  char s[10];

  REQUIRE(buffer.sizeLeft() == 10);
  REQUIRE(buffer.write("salut", 5) == 5);
  REQUIRE(buffer.sizeLeft() == 5);
  REQUIRE(buffer.write("toto", 4) == 4);
  REQUIRE(buffer.sizeLeft() == 1);
  REQUIRE(buffer.read(s, 3) == 3);
  REQUIRE(buffer.sizeLeft() == 4);
  REQUIRE(buffer.write("titi", 4) == 4);
  REQUIRE(buffer.sizeLeft() == 0);
  REQUIRE(buffer.read(s, 6) == 6);
  REQUIRE(buffer.sizeLeft() == 6);
}

TEST_CASE("read write not ASCII character", "[CBuffer]")
{
  CBuffer buffer(4096);
  int a = 34;
  long b = 21;
  double c = 3.14;

  REQUIRE(buffer.write(a) == sizeof(a));
  REQUIRE(buffer.write(b) == sizeof(b));
  REQUIRE(buffer.write(c) == sizeof(c));

  REQUIRE(buffer.read(a) == sizeof(a));
  REQUIRE(buffer.read(b) == sizeof(b));
  REQUIRE(buffer.read(c) == sizeof(c));

  REQUIRE(a == 34);
  REQUIRE(b == 21);
  REQUIRE(c == 3.14);
}

TEST_CASE("open a .so file and get the module's name", "[SharedModules]")
{
	zia::SharedModules modules;

	if (modules.addModule("../modules/php/phpmodule.so") == true) {
		auto v = modules.getModules();
		REQUIRE(v[0].getPath() == "../modules/php/phpmodule.so");
	}
}

TEST_CASE("open a .so file and fail", "[SharedModules]")
{
	zia::SharedModules modules;

	REQUIRE(modules.addModule("lol") == false);
}
