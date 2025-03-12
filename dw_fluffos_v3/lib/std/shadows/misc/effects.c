#define EFF_OB_NAME 0
#define EFF_ARG 1
#define EEQ_INCTIME 0
#define EEQ_FUNC 1
#define EEQ_EFF_OB 2
#define EEQ_INTERVAL 3
#define EEQ_FLAGS 4
#define EFF_SIZE 2
#define EEQ_SIZE 5
inherit "/std/basic/effects";
private object shadowed;
void setup_shadow( object thing ) {
   shadow( thing, 1 );
   shadowed = thing;
}
void destruct_shadow( object thing ) {
   if ( thing == this_object() ) {
      destruct( this_object() );
   } else {
      thing->destruct_shadow( thing );
   }
}
void set_effs( mixed *args ) {
  ::set_effs(args);
}
void set_eeq( mixed *args ) {
  ::set_eeq(args);
}
mixed *stats() {
  mixed *tmp = (mixed *)shadowed->stats();
  if(!arrayp(tmp)) {
    tmp = ({});
  }
  return ::stats() + tmp;
}