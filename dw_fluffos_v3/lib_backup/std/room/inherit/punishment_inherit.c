#define NOMIC_SYSTEM_CASE_CLASSES
#include <nomic_system.h>
#include <nroff.h>
private nosave string _short;
private nosave string _mail_information;
private nosave string _desc_file;
void create() {
   _mail_information = "";
   this_object()->setup();
}
void set_short(string short) {
   _short = short;
}
void set_description_file(string str) {
   _desc_file = str;
}
string query_description_file() {
   return _desc_file;
}
void set_mail_information(string mail) {
   _mail_information = mail;
}
string query_short(string area, class nomic_case the_case, string type, mixed data) {
   return _short;
}
string query_description(string area, string type) {
   string str;
   if (_desc_file) {
      str = unguarded( (: NROFF_HAND->cat_file(_desc_file+"_nroff", 1) :) );
      if (!str) {
         unguarded( (: NROFF_HAND->create_nroff(_desc_file, _desc_file+"_nroff") :) );
         str = unguarded( (: NROFF_HAND->cat_file(_desc_file+"_nroff", 1) :) );
      }
      if (str) {
         return str;
      }
   }
   return "Nothing particularly special.\n";
}
void start_punishment(string area, class nomic_case the_case, string type, function finish) {
   evaluate(finish, the_case, type, 0);
}
void complete_punishement(string area, class nomic_case the_case, string type, mixed data) {
   return ;
}
void suspend_punishment(string area, class nomic_case the_case, string type, mixed data) {
   return ;
}
string query_mail_information(string area, class nomic_case the_case,
                              string type, mixed data) {
   return _mail_information;
}