inherit "/std/effect_shadow";
#include <move_failures.h>
private int _keep;
private string _identifier;
private string* _adjs;
private object _owner;
int query_keep() { return _keep; }
void set_keep_value(int keep) { _keep = keep; }
void set_keep() { _keep = 1; }
void reset_keep() {
   _keep = 0;
   if (!_identifier)
      remove_this_effect();
}
string query_identifier() { return _identifier; }
string query_full_identifier() {
    string tmp;
    tmp = "";
    if ( sizeof( _adjs ) ) {
        tmp += implode( _adjs, " " ) + " ";
    }
    if ( _identifier ) {
       tmp += _identifier;
    }
    if ( strlen( tmp ) > 0 ) {
       return tmp;
    }
    return 0;
}
void set_identifier( string word ) {
   string* bits;
   if (word) {
      bits = explode(word, " ");
      _identifier = bits[<1];
      _adjs = bits[0..<2];
   } else {
      _identifier = 0;
      _adjs = ({ });
      if (!_keep)
         remove_this_effect();
   }
}
void set_identity_hold_owner(object ob) {
   _owner = ob;
}
object query_identity_hold_owner() {
   return _owner;
}
string *parse_command_id_list() {
   string *words;
   words = (string *)player->parse_command_id_list();
   if ( ( this_player() == _owner ) && stringp( _identifier ) &&
         !sizeof( filter_array( previous_object( -1 ),
         (: $1 && $1->ignore_identifier() :) ) ) ) {
      words += ({ _identifier });
   }
   return words;
}
string *parse_command_adjectiv_id_list() {
   string *words;
   words = (string *)player->parse_command_adjectiv_id_list();
   if ( ( this_player() == _owner ) && pointerp( _adjs ) &&
         !sizeof( filter_array( previous_object( -1 ),
         (: $1->ignore_identifier() :) ) ) ) {
      words += _adjs;
   }
   return words;
}
private void check_move_stuff() {
   object ob;
   ob = environment(player);
   while (ob &&
          ob != _owner) {
      ob = environment(ob);
   }
   if (ob != _owner) {
      remove_this_effect();
   }
}
varargs int move( mixed dest, string messin, string messout ) {
   int flag;
   flag = player->move( dest, messin, messout );
   if ( flag == MOVE_OK &&
        objectp( dest ) ) {
      call_out((: check_move_stuff :), 2);
   }
   return flag;
}