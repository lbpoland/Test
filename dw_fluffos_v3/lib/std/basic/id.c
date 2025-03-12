#include <parse_command.h>
inherit "/std/basic/id_match";
class Id {
  string name;
  string *alias;
  string *faux_alias;
  string *unique_faux_alias;
  string *adjectives;
  string *faux_adjectives;
  string *unique_faux_adjectives;
  string *plural_adjectives;
  string *plurals;
}
private nosave class Id _id;
int id_adjective(string);
int id_plural(string str);
int faux_id_allowed();
private void setup_id_class() {
   if (_id) {
      return ;
   }
   _id = new( class Id );
   _id->alias = ({ });
   _id->faux_alias = ({ });
   _id->unique_faux_alias = ({ });
   _id->plurals = ({ });
   _id->adjectives = ({ });
   _id->faux_adjectives = ({ });
   _id->unique_faux_adjectives = ({ });
   _id->plural_adjectives = ({ });
   _id->name = "object";
}
void set_name(string str) {
   _id->name = str;
}
string query_name() {
   if (!_id) {
      return 0;
   }
   return _id->name;
}
string query_cap_name() {
   if (!_id->name) {
      return "Someone";
   }
   return capitalize(_id->name);
}
void create() {
   setup_id_class();
}
void set_aliases(string *str) {
   _id->alias = str;
}
void add_alias(mixed str) {
   if (pointerp(str)) {
      _id->alias += str;
      return;
   }
   if (member_array(str, _id->alias) == -1) {
      _id->alias += ({ str });
   }
}
int remove_alias(string str) {
   int i;
   i = member_array(str, _id->alias);
   if (i == -1) {
      return 0;
   }
   _id->alias = _id->alias[0..i - 1] + _id->alias[i + 1..];
   return 1;
}
varargs string *query_alias( int no_faux ) {
  if( no_faux ||
      !sizeof( _id->unique_faux_alias ) ||
      !faux_id_allowed() )
    return _id->alias;
  else
    return _id->alias + _id->unique_faux_alias;
}
void add_faux_alias(mixed str) {
   if (pointerp(str)) {
      foreach( string aka in str )
        add_faux_alias( aka );
      return;
   }
   if( member_array( str, _id->alias ) != -1 )
     return;
   _id->faux_alias += ({ str });
   _id->unique_faux_alias = _id->unique_faux_alias | ({ str });
}
int remove_faux_alias(string str) {
   int i;
   i = member_array(str, _id->faux_alias);
   if (i == -1) {
      return 0;
   }
   _id->faux_alias = _id->faux_alias[0..i - 1] +
                      _id->faux_alias[i + 1..];
   if( member_array(str, _id->faux_alias) == -1 ) {
      _id->unique_faux_alias -= ({ str });
   }
   return 1;
}
string *query_faux_alias() {
  return _id->faux_alias;
}
string *query_unique_faux_alias() {
  return _id->unique_faux_alias;
}
int faux_id_allowed() {
  foreach( object ob in previous_object(-1) ) {
    if( objectp(ob) && ob->ignore_identifier() )
      return 0;
  }
  return 1;
}
int id(string str) {
   return (str == _id->name ||
          (member_array(str, query_alias()) != -1) );
}
int full_id(string str) {
   string *words;
   string name;
   string adjective;
   words = explode(str, " ") - ({ "" });
   name = words[<1];
   words = words[0.. < 2];
   if (!id(name)) {
      if (!id_plural(name)) {
         return 0;
      }
   }
   foreach(adjective in words) {
      if (!id_adjective(adjective)) {
         return 0;
      }
   }
   return 1;
}
void set_plurals(string *str) {
   _id->plurals = str;
}
void add_plural(mixed str) {
   if (pointerp(str)) {
      _id->plurals += str;
   } else if (_id->plurals) {
      if (member_array(str, _id->plurals) == -1) {
         _id->plurals += ({ str });
      }
   } else {
      _id->plurals = ({ str });
   }
}
void remove_plural(string str) {
   int i;
   i = member_array(str, _id->plurals);
   if (i != -1) {
      _id->plurals = _id->plurals[0..i - 1] + _id->plurals[i + 1..];
   }
}
void add_plurals(string *str) {
   _id->plurals += str;
}
string *query_plurals() {
   return _id->plurals;
}
int id_plural(string str) {
   return (member_array(str, _id->plurals) != -1);
}
void set_adjectives(string *str) {
   _id->adjectives = str;
}
void add_adjective(mixed str) {
   int i;
   if (pointerp(str)) {
      for (i = 0; i < sizeof(str); i++) {
         add_adjective(str[i]);
      }
      return;
   }
   if (stringp(str)) {
      str = explode(str, " ");
   }
   for (i = 0; i < sizeof(str); i++) {
      if (member_array(str[i], _id->adjectives) == -1) {
         _id->adjectives += ({ str[i] });
      }
   }
}
void remove_adjective(mixed str) {
   int i;
   if (pointerp(str)) {
      for (i = 0; i < sizeof(str); i++) {
         remove_adjective(str[i]);
      }
   } else {
      if ((i = member_array(str, _id->adjectives)) != -1) {
         _id->adjectives = delete(_id->adjectives, i, 1);
      }
   }
}
void add_faux_adjective(mixed str) {
   if (pointerp(str)) {
      foreach( string adj in str )
         add_faux_adjective( adj );
      return;
   }
   if( stringp( str ) ) {
      str = explode(str, " ");
   }
   str -= _id->adjectives;
   foreach( string adj in str ) {
      _id->faux_adjectives += ({ adj });
      _id->unique_faux_adjectives = _id->unique_faux_adjectives |
                                    ({ adj });
   }
}
void remove_faux_adjective(mixed str) {
   int i;
   if (pointerp(str)) {
      foreach( string adj in str )
         remove_faux_adjective( adj );
      return;
   }
   i = member_array(str, _id->faux_adjectives);
   if( i == -1 )
     return;
   _id->faux_adjectives = _id->faux_adjectives[0..i-1] +
                          _id->faux_adjectives[i+1..];
   if( ( i = member_array( str, _id->faux_adjectives ) ) == -1 )
     _id->unique_faux_adjectives -= ({ str });
}
string *query_faux_adjectives() {
  return _id->faux_adjectives;
}
string *query_unique_faux_adjectives() {
  return _id->unique_faux_adjectives;
}
varargs string *query_adjectives( int no_faux ) {
  if( no_faux ||
      !sizeof( _id->unique_faux_adjectives ) ||
      !faux_id_allowed() )
    return _id->adjectives;
  else
    return _id->adjectives + _id->unique_faux_adjectives;
}
int id_adjective(string word) {
   return (member_array(word, query_adjectives()) != -1);
}
void set_plural_adjectives(string *str) {
   _id->plural_adjectives = str;
}
void add_plural_adjective(mixed str) {
   int i;
   if (pointerp(str)) {
      for (i = 0; i < sizeof(str); i++) {
         add_plural_adjective(str[i]);
      }
      return;
   }
   if (stringp(str)) {
      str = explode(str, " ");
   }
   for (i = 0; i < sizeof(str); i++) {
      if (member_array(str[i], _id->plural_adjectives) == -1) {
         _id->plural_adjectives += ({ str[i] });
      }
   }
}
void remove_plural_adjective(mixed str) {
   int i;
   if (pointerp(str)) {
      for (i = 0; i < sizeof(str); i++) {
         remove_plural_adjective(str[i]);
      }
   } else {
      if ((i = member_array(str, _id->plural_adjectives)) != -1) {
         _id->plural_adjectives = delete(_id->plural_adjectives, i, 1);
      }
   }
}
string *query_plural_adjectives() {
   return _id->plural_adjectives;
}
int id_plural_adjective(string word) {
   return (member_array(word, _id->plural_adjectives) != -1);
}
string *parse_command_id_list() {
   return ({ _id->name, file_name(this_object()) }) + query_alias();
}
string *parse_command_plural_id_list() {
   return query_plurals();
}
string *parse_command_adjectiv_id_list() {
   return query_adjectives();
}
string *parse_command_plural_adjectiv_id_list() {
   return query_plural_adjectives();
}
object query_parse_id(mixed *arr) {
   if (arr[P_THING] == 0) {
      return this_object();
   }
   if (arr[P_THING] < 0) {
      arr[P_THING]++;
      if (arr[P_THING] != 0) {
         return 0;
      }
      arr[P_THING] = -10321;
      return this_object();
   }
   arr[P_THING]--;
   if (arr[P_THING] != 0) {
      return this_object();
   }
   arr[P_THING] = -10101;
   return this_object();
}
object query_frac_parse_id(mixed *arr) {
   if (arr[P_THING] < 0) {
      arr[P_THING]++;
      if (arr[P_THING] != 0) {
         return 0;
      }
      arr[P_THING] = -10235;
      return 0;
   }
   if (arr[P_THING] == 0) {
      if ((arr[P_MAX_NUM] * arr[P_TOP]) / arr[P_BOT] > arr[P_CUR_NUM]++) {
         return this_object();
      } else {
         return 0;
      }
   }
   if ((arr[P_THING] * arr[P_TOP]) / arr[P_BOT] > arr[P_CUR_NUM]++) {
      return this_object();
   }
   return 0;
}