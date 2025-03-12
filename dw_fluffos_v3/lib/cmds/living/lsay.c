#include <language.h>
#include <player.h>
#include <drinks.h>
#include <broadcaster.h>
inherit "/cmds/speech";
#define TP this_player()
mixed cmd(string arg) {
  int *co_ords;
  int status;
  class message mess;
  if (!arg)  arg = "";
  mess = build_message("@loudly " + arg, 0, "say");
  status = say_it(mess);
  if(status && TP && environment(TP))  {
    co_ords = environment(TP)->query_co_ord();
    BROADCASTER->npc_shout_event(TP, mess->notify_mess, mess->text,
                                 mess->language, co_ords, 20);
  }
  return status;
}
mixed *query_pattern() {
   return ({ "<string'message'>", (: cmd($4[0]) :) });
}