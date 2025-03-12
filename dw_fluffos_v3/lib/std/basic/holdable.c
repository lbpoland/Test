#include <move_failures.h>
private int _my_limb;
private nosave int _no_limbs;
private object _holder;
int held_this_item(int held, object holder, mixed arg);
void set_no_limbs(int num);
void create() {
   _no_limbs = 1;
}
mixed query_static_auto_load() {
  return ([ "no limbs" : _no_limbs
          ]);
}
void init_static_arg( mapping arg ) {
   if (!arg) {
      return ;
   }
   if (arg["no limbs"]) {
      set_no_limbs(arg["no limbs"]);
   }
}
mixed query_dynamic_auto_load() {
  return ([ "limb"       : (_holder ? _my_limb : -1),
            "limbs used" : (_holder ?
              sizeof(find_member(this_object(),
                                 _holder->query_holding())) : 0)
          ]);
}
void init_dynamic_arg( mapping arg, mixed new_arg ) {
   if (!arg) {
      return ;
   }
   if (arg["limb"] != -1) {
      call_out( function( int pos, mapping arg, mixed new_arg ) {
         if ( environment() ) {
            environment()->set_hold(this_object(), pos,
                                    arg["limbs used"]);
         }
         held_this_item(2, environment(), new_arg);
      }, 0, arg["limb"], arg, new_arg);
   }
}
int held_this_item(int held, object holder, mixed arg) {
   return 1;
}
int set_holder(object ob, int limb) {
   if (ob && environment() != ob) {
      return 0;
   }
   this_object()->remove_hide_invis( "concealed" );
   if ( !ob ||
        ob != _holder) {
      if (!held_this_item(0, _holder, 0)) {
         return 0;
      }
   }
   if (ob) {
      if (!held_this_item(1, ob, 0)) {
         return 0;
      }
   }
   _holder = ob;
   _my_limb = limb;
   return 1;
}
int query_my_limb() { return _my_limb; }
int query_no_limbs() { return _no_limbs; }
void set_no_limbs(int num) {
   if (num < 0) {
      return ;
   }
   _no_limbs = num;
}
int move( mixed ob) {
   if ( ob != _holder && _holder ) {
      if ( !sizeof( _holder->set_unhold( this_object() ) ) ) {
         return MOVE_NO_UNHOLD;
      }
   }
   return MOVE_OK;
}
object query_wielded() { return _holder; }
object query_holder() { return _holder; }
void dest_me() {
   if (_holder) {
      _holder->set_unhold(this_object());
   }
}
varargs int *hold_item( object who, int pos ) {
   object ob;
   object *held_things;
   object *dropped_things = ({ });
   int num_limbs;
  if( !undefinedp( pos ) && pos != -1 ) {
    if( pos < 0 || pos >= sizeof( who->query_holding() ) )
      return ({});
    ob = who->query_holding()[ pos ];
    if( ob ) {
      if( !sizeof( who->set_unhold( ob ) ) )
        return ({});
      else dropped_things += ({ ob });
    }
    held_things = who->query_holding()[pos..] +
                  who->query_holding()[0..pos-1];
  }
  else {
    held_things = who->query_holding();
    pos = -1;
  }
  if (pos == -1)  num_limbs = this_object()->query_no_limbs();
  else num_limbs = 1;
  tell_creator( who, "FL: %d, NL: %d, ob: %O\n", who->query_free_limbs(),
      num_limbs, this_object() );
  tell_creator( who, "Dropped things: %O\n", dropped_things );
  for( int i = 0; who->query_free_limbs() <
      num_limbs && i < sizeof( held_things ); i++ ) {
    tell_creator( who, "freeing limbs\n" );
    ob = held_things[i];
    if( ob && sizeof( who->set_unhold( ob ) ) )
      dropped_things += ({ ob });
  }
  if ( sizeof( dropped_things ) )
    tell_object( who, "You put down " + query_multiple_short(
        dropped_things ) + ".\n" );
  if( who->query_free_limbs() >= num_limbs ) {
     return who->set_hold( this_object(), pos, num_limbs );
  }
   tell_object( who, "You can't free up enough limbs to use "+
       this_object()->a_short() + ".\n" );
   return ({ });
}