#define CREATOR_DOC "/doc/creator/concepts/creator_doc.txt"
#include <command.h>
#include <mail.h>
inherit "/global/wiz_file_comm";
protected int do_dismiss(string str, string reason);
protected int employ(string str);
protected int new_domain(string dom, string director);
private int do_heart_beat();
protected int do_qsnoop(object *obs);
protected int bulk_delete( string word );
protected int clean_up_files( string word );
protected int do_hexec(string);
void create() {
  ::create();
}
void move_player_to_start(string bong, int bing, string c_name, string ident,
                          int go_invis) {
  ::move_player_to_start(bong, bing, c_name, ident, go_invis);
  cat("doc/CREATORNEWS");
  cat("doc/DIRECTORNEWS");
#ifndef NEW_DRIVER
  enable_wizard();
#endif
   switch ( query_invis() ) {
      case 3 :
         tell_object( this_object(),
               "===> You are currently Trustee invisible! <===\n" );
         break;
      case 2 :
         tell_object( this_object(),
               "===> You are currently Director invisible! <===\n" );
         break;
      case 1:
         tell_object( this_object(),
               "===> You are currently invisible! <===\n" );
         break;
   }
  add_command("qsnoop", this_object(), "<indirect:player>", (: do_qsnoop($1)
                                                             :));
  add_command("qsnoop", this_object(), "", (: do_qsnoop :));
  add_command("employ", this_object(), "<word>", (: employ($4[0]) :));
  add_command("dismiss", this_object(), "<word> <string>", (: do_dismiss($4[0], $4[1]) :));
  add_command("new_domain", this_object(), "<word> <word>",
              (: new_domain($4[0], $4[1]) :) );
  add_command("heart_beat", this_object(), "", (: do_heart_beat() :) );
  add_command("bulk_delete", this_object(),
              "{a|b|c|d|e|f|g|h|i|j|k|l|m|n|o|p|q|r|s|t|u|v|w|x|y|z}",
              (: bulk_delete($4[0]) :) );
  add_command("clean_up_files",  this_object(), "<word>",
              (: clean_up_files($4[0]) :) );
  AddSearchPath(({ DIR_LORD_CMDS, DIR_SECURE_LORD_CMDS }));
}
protected mixed process_input(string input){
  if(input == "end_it_all")
    shutdown(0);
  if(input[0..4] == "hexec")
    return do_hexec(input[5..]);
  return ::process_input(input);
}
protected int end_it_all() {
  shutdown(0);
  return 1;
}
private int do_heart_beat() {
  heart_beat();
  return 1;
}
int query_creator() {
  return 1;
}
nomask int query_director() {
  return 1;
}
nomask int query_lord() {
  return 1;
}
protected int employ(string str) {
  string doc;
  if (GetForced()) {
    return 0;
  }
  switch (master()->employ_creator( lower_case(str) )) {
    case 2 :
      if(file_size(CREATOR_DOC) > 0) {
        doc = read_file(CREATOR_DOC);
        AUTO_MAILER->auto_mail(lower_case(str), this_player()->query_name(),
          "Documents for new creators", "", doc, 0, 0);
      }
      return 1;
    case 1 :
      return 1;
    default :
      return 0;
  }
}
protected int do_dismiss(string str, string reason) {
  if (GetForced()) {
    return 0;
  }
   return (int)master()->dismiss_creator( str + " " + reason);
}
protected int new_domain(string dom, string director) {
  if (GetForced()) {
    return 0;
  }
  return (int)master()->create_domain(dom, director);
}
string query_object_type(object) {
  if (master()->query_trustee(geteuid(this_object())))
    return "T";
  return "D";
}
void event_enter(object me, string s1, object from) {
  if ((!s1 || s1 == "") && interactive(me)) {
    if (environment() == environment(me))
      event_inform(me, me->query_cap_name()+" invisibly enters the room",
                   "enter");
    else
      event_inform(me, me->query_cap_name()+" invisibly enters your inventory",
                   "enter");
  }
  ::event_enter(me, s1, from);
}
void event_exit(object me, string s1, object from) {
  if ((!s1 || s1 == "") && interactive(me)) {
    if (environment() == environment(me))
      event_inform(me, me->query_cap_name()+" invisibly exits the room",
                   "enter");
    else
      event_inform(me, me->query_cap_name()+" invisibly exits your inventory",
                   "enter");
  }
  ::event_exit(me, s1, from);
}
protected int do_hexec(string junk) {
  if (GetForced()) {
    return 0;
  }
  write_file("/w/"+query_name()+"/exec_thing.c", "void create() { "+junk+"; }");
  catch(("/w/"+query_name()+"/exec_thing")->bingle());
  destruct(find_object("/w/"+query_name()+"/exec_thing"));
  rm("/w/"+query_name()+"/exec_thing.c");
  return 1;
}
varargs int adjust_xp(int number, int shared) {
  if (objectp(previous_object())) {
    event_inform(previous_object(),
                 (string)previous_object()->query_name() + " (" +
                 file_name(previous_object()) +") gives you " +
                 number + " xp", "xp");
  }
  return ::adjust_xp(number, shared);
}
protected int bulk_delete( string word ) {
  if (GetForced()) {
    return 0;
  }
  word = lower_case(word);
  return (int)"/secure/bulk_delete"->delete_files(word);
}
protected int clean_up_files( string word ) {
  if (GetForced()) {
    return 0;
  }
  return (int)"/secure/bulk_delete"->clean_up_files(word);
}
protected int do_qsnoop(object *obs) {
  object targ;
  if (GetForced()) {
    return 0;
  }
  if (!obs || !sizeof(obs)) {
    snoop(this_object(), 0);
    write("Ok, qsnoop cancelled.\n");
    return 1;
  }
  targ = obs[0];
  if(!snoop(this_object(), targ)) {
    notify_fail("You fail to qsnoop " + targ->query_cap_name() + ".\n");
    return 0;
  }
  write("Ok, qsnooping "+targ->query_cap_name() + ".\n");
  return 1;
}