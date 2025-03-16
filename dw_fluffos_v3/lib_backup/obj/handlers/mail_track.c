inherit "std/object";
#include <mail.h>
#include <mail_track.h>
#include <player_handler.h>
#define SECURITY if (!master()->query_leader(previous_object(-1))) return 0;
int add_member(string list, string mem);
private void load_me();
private void save_me();
int query_list(string list);
int create_list(string list, string creator);
nosave mixed *our_mailers;
mapping mailing_lists;
void setup() {
   set_name("tracker");
   set_short("mail tracker");
   add_property("determinate", "the ");
   add_property("there", "mounted on one wall");
   add_adjective("mail");
   set_long("This thing tracks mail.   Clever, innit?\n");
   reset_get();
   reset_drop();
   our_mailers = ({ });
   mailing_lists = ([ ]);
   seteuid("Root");
   load_me();
   if (!query_list("postmaster")) {
      create_list("postmaster", "pinkfish");
   }
   move(MAIL_ROOM);
}
int add_mailer(object ob, string str) {
   int i;
   if (!stringp(str) || !objectp(ob)) {
      return 0;
   }
   i = member_array(str, our_mailers);
   if (i == -1) {
      our_mailers += ({ ob, str });
   } else {
      write(i);
      if (our_mailers[i-1]) {
         our_mailers[i-1]->dest_me();
      }
      our_mailers += ({ ob, str });
   }
   return 1;
}
object find_mailer(string str) {
   int i;
   if (!stringp(str)) {
      return 0;
   }
   i = member_array(str, our_mailers);
   if (i == -1) {
      return 0;
   }
   return our_mailers[i-1];
}
int delete_mailer(object ob) {
   int i;
   if (!objectp(ob)) {
      return 0;
   }
   i = member_array(ob, our_mailers);
   if (i == -1) {
      return 0;
   }
   our_mailers = delete(our_mailers, i, 2);
}
void we_are_done(object me) {
   if (objectp(me)) {
      me->dest_me();
   }
}
int mail(string str, string sub) {
   object mailer;
   mailer = clone_object(MAILER);
   mailer->set_do_this_last(({ this_object(), "we_are_done", mailer }));
   mailer->read_mail(str, sub);
   return 2;
}
private void save_me() {
   unguarded((: save_object, "/save/mail_track" :));
}
private void load_me() {
   string *list_names, name;
   mixed *list;
   unguarded((: restore_object, "/save/mail_track" :));
   list_names = keys(mailing_lists);
   if (sizeof(list_names) && !classp(mailing_lists[list_names[0]])) {
      foreach (name, list in mailing_lists) {
         mailing_lists[name] = new(class mailing_list, members : list[0],
                                                controllers : list[1], creator : list[2]);
      }
      save_me();
   }
}
string *query_mailing_lists() {
   return keys(mailing_lists) +
     "/secure/master"->query_domains() +
      ({ "seniors", "lords", "hlords" });
}
int query_list(string list) {
   return member_array(list, query_mailing_lists()) != -1;
}
string *query_members(string list) {
  string *tmp;
  switch (list) {
  case "playtesters" :
    tmp = (string *)"/obj/handlers/playtesters"->query_playtesters();
    return ({ "/d/playtesters/master"->query_lord() }) + sort_array(tmp, 1);
  case "seniors" :
    tmp = (string *)master()->query_all_seniors();
    return tmp;
  case "lords" :
    tmp = (string *)master()->query_all_leaders();
    return tmp;
  case "hlords" :
    tmp = ((string *)master()->query_administrators() -
           ({ "Admin", "Root", "offler" }));
    return tmp;
  default :
  }
  if (file_size("/d/"+ list) == -2) {
    tmp = (string *)("/d/"+ list +"/master")->query_members() +
      ({ (string)("/d/"+ list +"/master")->query_lord() });
  }
  else if (mailing_lists[list]) {
    tmp = copy(mailing_lists[list]->members);
  }
  if(tmp)
    return filter_array(tmp, (: PLAYER_HANDLER->test_active($1, 1) :));
  return ({ });
}
int query_member(string list_name, string name) {
   class mailing_list list;
   list = mailing_lists[list_name];
   if (list) {
      return member_array(name, list->members) != -1;
   }
   if (file_size("/d/" + list_name) == -2) {
      return (int)("/d/" + list_name + "/master")->query_member(name);
   }
   if (list_name == "seniors") {
      return (int)master()->query_senior(name);
   }
   if (list_name == "lords") {
      return (int)master()->query_leader(name);
   }
   if (list_name == "hlords") {
      return (int)master()->query_administrator(name);
   }
}
string *query_controllers(string list) {
   if (file_size("/d/"+ list) == -2) {
      return ({ (string)("/d/"+ list +"/master")->query_lord() });
   }
   if (mailing_lists[list]) {
      return copy(mailing_lists[list]->controllers);
   }
   return ({ });
}
int query_controller(string list_name, string name) {
   class mailing_list list = mailing_lists[list_name];
   if (!list) {
      return 0;
   }
   return member_array(name, list->controllers) != -1;
}
string query_creator(string list_name) {
   class mailing_list list = mailing_lists[list_name];
   if (!classp(list)) {
      return 0;
   }
   return list->creator;
}
int create_list(string list, string creator) {
   SECURITY
   if (mailing_lists[list]) {
      return 0;
   }
   if (file_size("/d/" + list) == -2) {
      return 0;
   }
   if (PLAYER_HANDLER->test_user(list)) {
      return 0;
   }
   mailing_lists[list] = new(class mailing_list, members : ({ creator }),
                                          controllers : ({ creator }), creator : creator);
   save_me();
   return 1;
}
protected int delete_list(string list) {
   if (!mailing_lists[list]) {
      return 0;
   }
   map_delete(mailing_lists, list);
   save_me();
   return 1;
}
int add_controller(string list_name, string mem) {
   class mailing_list list = mailing_lists[list_name];
   SECURITY
   if (!classp(list)) {
      return 0;
   }
   if (member_array(mem, list->controllers) != -1) {
      return 0;
   }
   list->controllers += ({ mem });
   add_member(list_name, mem);
   save_me();
   return 1;
}
int remove_controller(string list_name, string name) {
   int i;
   class mailing_list list = mailing_lists[list_name];
   SECURITY
   if (!classp(list)) {
      return 0;
   }
   if ((i = member_array(name, list->controllers)) == -1) {
      return 0;
   }
   list->controllers = delete(list->controllers, i, 1);
   save_me();
   return 1;
}
int add_member(string list_name, string mem) {
   class mailing_list list = mailing_lists[list_name];
   if (file_name(previous_object()) != MAIL_ROOM) {
      return 0;
   }
   if (!classp(list)) {
      return 0;
   }
   if (member_array(mem, list->members) != -1) {
      return 0;
   }
   list->members += ({ mem });
   save_me();
   return 1;
}
int remove_member(string list_name, string mem) {
   int i;
   class mailing_list list = mailing_lists[list_name];
   if (file_name(previous_object()) != MAIL_ROOM) {
      return 0;
   }
   if (!classp(list)) {
      return 0;
   }
   if ((i = member_array(mem, list->members)) == -1) {
      return 0;
   }
   list->members = delete(list->members, i, 1);
   if (!sizeof(list->members)) {
      delete_list(list_name);
   }
   save_me();
   return 1;
}
int delete_member(string list_name, string mem) {
   class mailing_list list = mailing_lists[list_name];
   SECURITY
   if (!remove_member(list_name, mem)) {
      return 0;
   }
   remove_controller(list_name, mem);
   if (!sizeof(list->members)) {
      delete_list(list_name);
   }
   save_me();
   return 1;
}