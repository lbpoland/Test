#include <situations.h>
inherit "/std/room/basic/situation_changer";
void add_situation( mixed label, class situation sit ) {
  if (!clonep()) ::add_situation( label, sit );
  else write("You can't add situations to a clone of this object.");
}
object set_room(object room_o) {
  if (clonep() ) {
    object base;
    base = find_object(base_name(this_object()));
    if (!base) {
      (base_name(this_object()))->parp();
      base = find_object(base_name(this_object()));
    }
    if (!(base->query_room())) {
      call_out( "dest_me", 2 );
      return room_o->set_situation_changer( base );
    }
    sitdata = base->query_situations();
  }
  return ::set_room( room_o );
}
void dest_me() {
  if (clonep()) ::dest_me();
  else if (sizeof(children(base_name(this_object())))==1) ::dest_me();
  return;
}
void create() {
  if (!clonep()) this_object()->setup_situations();
}