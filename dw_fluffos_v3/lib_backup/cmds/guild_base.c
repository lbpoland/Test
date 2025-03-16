inherit "/cmds/base";
#include <nroff.h>
#include <cmds/guild_base.h>
#define NROFF_SOURCE "/doc/known_command/"
nosave string _nroff_fname;
nosave class teach_skill *_teach_skills;
nosave string _command_name;
nosave string _teach_guild;
void create() {
   _teach_skills = ({ });
}
void set_nroff_file(string str) {
   _nroff_fname = str;
}
string query_nroff_file() {
  return _nroff_fname;
}
private string nroff_file(string name, int html) {
   string nroff_fn;
   string str;
   if (name[0] != '/') {
      name = NROFF_SOURCE + name;
   }
   nroff_fn = NROFF_DIR + replace(name, "/", ".");
   if (html) {
      str = NROFF_HAND->html_file(nroff_fn, 1);
   } else {
      str = NROFF_HAND->cat_file(nroff_fn, 1);
   }
   if (!str) {
      NROFF_HAND->create_nroff(name, nroff_fn);
      if (html) {
         str = NROFF_HAND->html_file(nroff_fn, 0);
      } else {
         str = NROFF_HAND->cat_file(nroff_fn, 0);
      }
   }
   return str;
}
function help_function() {
   if (_nroff_fname) {
      return (: nroff_file(_nroff_fname, 0) :);
   }
   return 0;
}
string help() {
   if (_nroff_fname) {
      return nroff_file(_nroff_fname, 0);
   }
   return 0;
}
string query_www_help() {
   if (_nroff_fname) {
      return nroff_file(_nroff_fname, 1);
   }
   return 0;
}
void add_teach_skill(string skill, int teach, int learn) {
   class teach_skill bing;
   bing = new(class teach_skill);
   bing->skill = skill;
   bing->teach = teach;
   bing->learn = learn;
   _teach_skills += ({ bing });
}
class teach_skill *query_teach_skills() {
   return _teach_skills;
}
void set_command_name(string name) {
   _command_name = name;
}
string query_command_name() {
   return _command_name;
}
void set_teach_guild(string guild) {
   _teach_guild = guild;
}
string query_teach_guild() {
   return _teach_guild;
}
int can_teach_command(object teacher, object student) {
   class teach_skill bing;
   if (!sizeof(_teach_skills) ||
       !_command_name) {
     return 0;
   }
   foreach (bing in _teach_skills) {
      if (teacher->query_skill(bing->skill) < bing->teach) {
         return -1;
      }
      if (student->query_skill(bing->skill) < bing->learn) {
         return -2;
      }
   }
   if (_teach_guild &&
       student->query_guild_ob() != _teach_guild) {
      return -3;
   }
   return 1;
}
int teach_command(object teacher, object student) {
   int ret;
   ret = can_teach_command(teacher, student);
   if (ret == 1) {
      student->add_known_command(_command_name);
   }
   return ret;
}