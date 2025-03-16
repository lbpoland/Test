#include <player.h>
#include <mail.h>
#include <clothing.h>
private mapping player_info;
private string password;
private nosave string tmppassword;
string query_name();
private int change_password();
private int change_password2(mixed pass);
private int change_password3(string pass);
private int change_password4(string pass);
int add_command(string command, object ob, mixed format, function func);
void finger_commands() {
   add_command("password", this_object(), "", (: change_password() :));
   add_command("passwd", this_object(), "", (: change_password() :));
}
void set_desc(string str) {
   if (!player_info) {
      player_info = ([ ]);
   }
   if (!str) {
      map_delete(player_info, "desc");
   } else {
      player_info["desc"] = str;
   }
}
string query_desc() {
   if (!player_info  ||  undefinedp(player_info["desc"])) {
      return "";
   }
   return player_info["desc"] + "%^RESET%^";
}
void set_zone_desc(string zone, string desc) {
   if (!player_info["zone desc"]) {
      player_info["zone desc"] = ([ ]);
   }
   if (!desc) {
      map_delete(player_info["zone desc"], zone);
   } else {
      player_info["zone desc"][zone] = desc;
   }
}
string query_zone_desc(string zone) {
   if (!player_info["zone desc"]) {
      return 0;
   }
   return player_info["zone desc"][zone];
}
string* query_zone_desc_names() {
   if (!player_info["zone desc"]) {
      return ({ });
   }
   return keys(player_info["zone desc"]);
}
string query_main_zone_desc(object* wearing) {
   object bing;
   string zone;
   string type;
   string eq_type;
   string str;
   mixed types;
   mapping covered;
   if (!sizeof(player_info["zone desc"])) {
      return "";
   }
   covered = ([ ]);
   foreach (bing in wearing) {
      types = bing->query_type();
      if (!arrayp(types)) {
         types = ({ types });
      }
      foreach (type in types) {
         eq_type = CLOTHING_HANDLER->query_equivilant_type(type);
         if (eq_type) {
            foreach (zone in CLOTHING_HANDLER->query_zone_names(eq_type)) {
               covered[zone] = 1;
            }
         } else {
            foreach (zone in CLOTHING_HANDLER->query_zone_names(type)) {
               covered[zone] = 1;
            }
         }
      }
   }
   str = "";
   foreach (zone in query_zone_desc_names()) {
      if (!covered[zone]) {
         str += " " + replace_string(query_zone_desc(zone), "$NEW_LINE$", "\n");
      }
   }
   return str;
}
void set_password(string pass) {
   if (file_name(previous_object())[0..12] == "/secure/login" ||
       file_name(previous_object())[0..13] == "/secure/nlogin") {
      password = pass;
   }
}
private int change_password() {
   if (password) {
      write("Please enter your old password : ");
      input_to((: change_password2 :),1);
      return 1;
   }
   change_password2(0);
   return 1;
}
private int change_password2(mixed pass) {
   string str;
   if (password) {
      str = crypt(pass,password);
      if (str != password) {
         write("\nIncorrect.\n");
         return 1;
      }
   }
   write("\nEnter new Password : ");
   input_to((: change_password3 :),1);
   return 1;
}
private int change_password3(string pass) {
   tmppassword = pass;
   if(sizeof(pass) < 6) {
     write("\nPassword is too short, must be at least 6 characters.\n");
     write("Enter new Password :");
     input_to((: change_password3 :),1);
     return 1;
   }
   write("\nPlease enter again : ");
   input_to((: change_password4 :),1);
   return 1;
}
private int change_password4(string pass) {
   if (tmppassword != pass) {
      write("\nIncorrect.\n");
      return 1;
   }
   password = crypt(pass,password);
   write("\nOk.\n");
   return 1;
}
string *query_rhosts() {
  if(!player_info)
    return 0;
  return player_info["allowed_ips"];
}
void set_rhosts(string *ips) {
  if(file_name(previous_object())[0..18] != "/cmds/player/access" &&
     file_name(previous_object())[0..19] != "/cmds/lord/authorise")
    return ;
  if(!player_info)
    player_info = ([ ]);
  player_info["allowed_ips"] = ips;
}
string query_real_name() {
   if (!player_info) {
      return 0;
   }
   return player_info["real_name"];
}
void set_real_name(string str) {
   if (!player_info) {
      player_info = ([ ]);
   }
   player_info["real_name"] = str;
}
string query_where() {
   if (!player_info) {
      return "";
   }
   return player_info["location"];
}
void set_where(string str) {
   if (!player_info) {
      player_info = ([ ]);
   }
   player_info["location"] = str;
}
string query_birthday() {
   if (!player_info) {
      return UNKNOWN_BIRTHDAY;
   }
   if (!player_info["birthday"]) {
      return UNKNOWN_BIRTHDAY;
   }
   return player_info["birthday"];
}
void set_birthday(string i) {
   if (!player_info) {
      player_info = ([]);
   }
   player_info["birthday"] = i;
}
int query_is_birthday_today() {
   string cmonth;
   string dummy;
   string bmonth;
   int cdate;
   int bdate;
   if (sscanf(ctime(time()), "%s %s %d %s", dummy, cmonth, cdate, dummy)!=4) {
      return 0;
   }
   if (sscanf(query_birthday(), "%d%s of %s", bdate, dummy, bmonth) !=3) {
      return 0;
   }
   if (cmonth == bmonth[0..2] && cdate == bdate) {
      return 1;
   }
}
string query_email() {
  if(file_name(previous_object())[0..13] != "/secure/finger" &&
     file_name(previous_object())[0..27] != "/obj/handlers/player_handler" &&
     file_name(previous_object())[0..28] != "/obj/handlers/options_handler") {
    return "";
   }
   if (!player_info) {
      return "";
   }
   return player_info["email"];
}
nomask void set_email(string str) {
   if (!player_info) {
      player_info = ([]);
   }
   player_info["email"] = str;
}
string query_homepage() {
   if (!player_info) {
      player_info = ([ ]);
   }
   return player_info["homepage"];
}
nomask void set_homepage(string str) {
   if (!player_info) {
      player_info = ([]);
   }
   player_info["homepage"] = str;
}
int finger_set() {
   if (!player_info ||
      player_info == ([ ]) ||
      sizeof(keys(player_info)) == 1) {
      return 0;
   }
   return 1;
}