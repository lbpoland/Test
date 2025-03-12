#include <language.h>
#include <player.h>
#include <drinks.h>
inherit "cmds/base";
inherit "cmds/speech";
mixed cmd(string arg) {
  class message mess;
  mess = build_message(arg, 0, "say");
  return say_it(mess);
}