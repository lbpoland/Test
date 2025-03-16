#include <clubs.h>
#include <player.h>
class family_information {
   string name;
   string* adjectives;
   string id;
   string* titles;
   string cur_title;
   string* clubs;
   string force_title;
   int force_timeout;
}
#define FAMILY_CLASS_SIZE 8
private class family_information _family_name;
string query_name();
int set_family_name(string name);
int add_player_title(string title);
void remove_player_title(string title);
private class family_information create_family_info() {
   class family_information bing;
   bing = new(class family_information);
   bing->adjectives = ({ });
   bing->titles = ({ "mr", "miss", "mrs", "ms" });
   bing->clubs = ({ });
   return bing;
}
protected void setup_default_titles() {
   if (!_family_name) {
       return;
   }
   _family_name->titles = ({ "mr", "miss", "mrs", "ms" });
}
private void update_adjectives() {
   if (!_family_name) {
      return ;
   }
   _family_name->adjectives = ({ });
   _family_name->id = 0;
   if (_family_name &&
       _family_name->name) {
      _family_name->adjectives = explode(lower_case(_family_name->name), " ")[0..<2];
      _family_name->id = explode(lower_case(_family_name->name), " ")[<1];
   }
   if (_family_name &&
       _family_name->cur_title) {
      _family_name->adjectives += explode(_family_name->cur_title, " ");
   }
}
void check_family_name() {
   class family_information frog;
   string bing;
   if (!classp(_family_name) &&
       _family_name) {
      bing = (string)_family_name;
      _family_name = create_family_info();
      set_family_name(bing);
   }
   if (classp(_family_name) &&
       sizeof(_family_name) == 5) {
      frog = new(class family_information);
      frog->adjectives = _family_name->adjectives;
      frog->id = _family_name->id;
      frog->cur_title = _family_name->cur_title;
      frog->name = _family_name->name;
      frog->titles = _family_name->titles;
      frog->clubs = ({ });
      _family_name = frog;
   }
   if (classp(_family_name) &&
       sizeof(_family_name) == 6) {
      frog = new(class family_information);
      frog->adjectives = _family_name->adjectives;
      frog->id = _family_name->id;
      frog->cur_title = _family_name->cur_title;
      frog->name = _family_name->name;
      frog->titles = _family_name->titles;
      frog->clubs = _family_name->clubs;
      _family_name = frog;
   }
   if (_family_name &&
       _family_name->name) {
      if (!CLUB_HANDLER->is_family(_family_name->name) ||
          !CLUB_HANDLER->is_member_of(_family_name->name, query_name())) {
         _family_name->name = 0;
      }
   }
   if (_family_name &&
       strlen(_family_name->cur_title) > 20) {
      tell_object(this_object(),
                  "%^YELLOW%^Your title is too long!  Resetting.\n%^RESET%^");
      _family_name->cur_title = 0;
   }
   if (_family_name &&
       _family_name->cur_title) {
      if (member_array(lower_case(_family_name->cur_title),
                       _family_name->titles) == -1) {
         tell_object(this_object(),
                  "%^YELLOW%^Your title is invalid!  Resetting.\n%^RESET%^");
         _family_name->cur_title = 0;
      }
   }
   update_adjectives();
   if (_family_name && _family_name->clubs) {
       _family_name->clubs = filter(_family_name->clubs,
           (: CLUB_HANDLER->is_club($1) :));
   }
}
int set_family_name(string name) {
   if (name && (!CLUB_HANDLER->is_family(name) ||
                !CLUB_HANDLER->is_member_of(name, query_name()))) {
      return 0;
   }
   if (!classp(_family_name)) {
      _family_name = create_family_info();
   }
   if (_family_name->name) {
      CLUB_HANDLER->remove_member(_family_name->name, query_name());
   }
   if (name) {
      _family_name->name = CLUB_HANDLER->query_club_name(name);
   } else {
      _family_name = 0;
   }
   update_adjectives();
   return 1;
}
string query_family_name() {
   if (stringp(_family_name)) {
      return (string)_family_name;
   }
   if (_family_name) {
      return _family_name->name;
   }
   return 0;
}
string query_player_title() {
   check_family_name();
   if (_family_name && classp(_family_name) &&
       _family_name->force_title) {
      if (-this_object()->query_time_on() > _family_name->force_timeout) {
         _family_name->force_title = 0;
      } else {
         return capitalize(_family_name->force_title);
      }
   }
   if (_family_name && classp(_family_name) &&
       _family_name->cur_title) {
      return capitalize(_family_name->cur_title);
   }
   return 0;
}
string* query_all_player_titles() {
   if (!_family_name) {
      _family_name = create_family_info();
   }
   return _family_name->titles;
}
int set_player_title(string title) {
   string* bits;
   if (!_family_name) {
      _family_name = create_family_info();
   }
   if (strlen(title) > 20) {
      return 0;
   }
   if (!title ||
       member_array(lower_case(title), _family_name->titles) != -1) {
      if (title) {
         bits = explode(title, " ");
         _family_name->cur_title = implode(map(bits, (: capitalize($1) :)), " ");
      } else {
         _family_name->cur_title = 0;
      }
      update_adjectives();
      return 1;
   }
   return 0;
}
int set_forced_title(string title, int timeout) {
   _family_name->force_title = title;
   _family_name->force_timeout = -this_object()->query_time_on() + timeout;
   tell_object(this_object(), "%^CYAN%^You feel that other peoples perception "
               "of you has changed and you title is being "
               "misinterpreted.%^RESET%^\n");
   return 1;
}
string query_forced_title() {
   return _family_name->force_title;
}
int add_player_title(string title) {
   title = lower_case(title);
   if (!_family_name) {
      _family_name = create_family_info();
   }
   if (member_array(title, _family_name->titles) == -1) {
      _family_name->titles += ({ title });
      return 1;
   }
   return 0;
}
void remove_player_title(string title) {
   title = lower_case(title);
   if (!_family_name) {
      _family_name = create_family_info();
   }
   if (member_array(title, _family_name->titles) != -1) {
      _family_name->titles -= ({ title });
   }
   if (_family_name->cur_title == title) {
      _family_name->cur_title = 0;
   }
}
int add_player_club(string club) {
   class family_information frog;
   if (!club) {
      return 0;
   }
   club = CLUB_HANDLER->normalise_name(club);
   if (!CLUB_HANDLER->is_club(club)) {
      return 0;
   }
   if (!_family_name) {
      _family_name = create_family_info();
   }
   if (classp(_family_name) &&
       sizeof(_family_name) == 5) {
      frog = new(class family_information);
      frog->adjectives = _family_name->adjectives;
      frog->id = _family_name->id;
      frog->cur_title = _family_name->cur_title;
      frog->name = _family_name->name;
      frog->titles = _family_name->titles;
      frog->clubs = ({ });
      _family_name = frog;
   }
   if (member_array(club, _family_name->clubs) == -1) {
      _family_name->clubs += ({ club });
      return 1;
   }
   return 0;
}
void remove_player_club(string club) {
   if (!club) {
      return 0;
   }
   club = CLUB_HANDLER->normalise_name(club);
   if (!_family_name) {
      return ;
   }
   _family_name->clubs -= ({ club });
}
string* query_player_clubs() {
   if (!_family_name) {
      return ({ });
   }
   return _family_name->clubs;
}
string *parse_command_id_list() {
   if (_family_name &&
       _family_name->id) {
      return ({ _family_name->id });
   }
   return ({ });
}
string *parse_command_plural_id_list() {
   if (_family_name &&
       _family_name->id) {
      return ({ pluralize(_family_name->id) });
   }
   return ({ });
}
string *parse_command_adjectiv_id_list() {
   if (_family_name) {
      return _family_name->adjectives;
   }
   return ({ });
}