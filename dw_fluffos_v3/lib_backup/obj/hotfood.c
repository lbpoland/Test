#include <bits_controller.h>
#include <weather.h>
inherit "/obj/food";
#define WARM 10
#define WARM_TIME 60
#define COOL_RATE_DEFAULT 10
private int _cool_level;
private int _cool_rate;
private int _purchase_time;
private mixed _hot_eat_message;
private mixed _cold_eat_message;
private mixed _hot_eat_piece_message;
private mixed _hot_eat_amt_message;
private mixed _hot_eat_last_message;
private mixed _cold_eat_piece_message;
private mixed _cold_eat_amt_message;
private mixed _cold_eat_last_message;
void create();
void set_cool_rate( int rate );
void set_cool_level(int level);
int query_cool_rate();
int query_cool_level();
protected void do_cool();
void set_hot_eat_mess(mixed messages);
void set_cold_eat_mess(mixed messages);
mixed query_hot_eat_mess();
mixed query_cold_eat_mess();
void setup_cold_eat_piece_messages(mixed piece, mixed amt, mixed last);
void setup_hot_eat_piece_messages(mixed piece, mixed amt, mixed last);
mixed query_hot_eat_amt_message;
mixed query_hot_eat_piece_message;
mixed query_hot_last_message;
mixed query_cold_eat_amt_message;
mixed query_cold_eat_piece_message;
mixed query_cold_last_message;
void create() {
   do_setup++;
   ::create();
   do_setup--;
   _cool_rate = COOL_RATE_DEFAULT;
   set_decay_speed( 1 );
   if ( !do_setup ) this_object()->setup();
   _cool_level = ( this_object()->query_weight() ) * 20;
   _purchase_time = time();
}
void set_cool_rate( int rate ) {
   _cool_rate = rate;
}
int query_cool_rate() {
   return _cool_rate;
}
int query_cool_level() {
   return _cool_level;
}
string query_short_rotten_adjective() {
   string ret;
   if (this_object()->query_cool_level() == 7){
       return ("cold " + ::query_short_rotten_adjective());
   }
   _cool_level = (time() - _purchase_time)/_cool_rate;
   ret = "";
   switch ( _cool_level ) {
     case 0..1:
        ret="piping hot " + ret;
        break;
     case 2:
        ret = "slightly cooled " + ret;
        break;
     case 3:
        ret = "partially cooled " + ret;
        break;
     case 4:
        ret = "half cooled " + ret;
        break;
     case 5:
        ret = "mostly cooled " + ret;
        break;
     case 6:
        ret = "almost completely cooled " + ret;
        break;
     default:
        ret ="stone cold " + ret;
        break;
        }
   return ret;
}
string query_long_decay_level() {
   string ret;
   int flag;
   if(query_collective() && query_amount() > 1 ) flag = 1;
   if (this_object()->query_cool_level() == 7){
       return ("It is stone cold. " + ::query_long_decay_level());
   }
   ret = "";
  _cool_level = (time() - _purchase_time)/_cool_rate;
   switch ( _cool_level) {
     case 0..1:
          ret += (flag?
          "They have not yet begun to cool.\n":
          "It has not yet begun to cool.\n");
        break;
     case 2:
           ret += (flag?
           "They have cooled slightly.\n":
           "It has cooled slightly.\n");
        break;
     case 3:
           ret += (flag?
           "They have partially cooled.\n":
           "It has partially cooled.\n");
        break;
     case 4:
           ret += (flag?
           "They are half cooled.\n":
           "It is half cooled.\n");
        break;
     case 5:
           ret += (flag?
           "They have mostly cooled.\n":
           "It has mostly cooled.\n");
        break;
     case 6:
           ret += (flag?
           "They are almost completely cold.\n":
           "It is almost completely cold.\n");
        break;
     default:
           ret += (flag?
           "They are stone cold.\n":
           "It is stone cold.\n");
        break;
        }
    return ret;
}
varargs int do_eat( int no_mess ) {
  int current_warmth;
  int remaining_time;
  int new_warmth;
  int new_time;
  if(this_object()->query_cool_level() >= 7 ){
    if (this_object()->query_weight_per_bite()){
      setup_eat_piece_messages(this_object()->query_cold_eat_piece_message(),
                               this_object()->query_cold_eat_amt_message(),
                               this_object()->query_cold_eat_last_message());
      }
    else {
      set_eat_mess( this_object()->query_cold_eat_message() );
      }
     return( ::do_eat( no_mess ));
  }
  if(this_player()->query_property("warmth")){
    current_warmth = this_player() -> query_property("warmth");
    remaining_time = this_player() -> query_property_time_left("warmth");
    new_warmth = current_warmth+WARM;
    new_time = (remaining_time + WARM_TIME)*0.75;
    this_player()->add_property( "warmth",new_warmth,new_time);
    }
  else{
     this_player()->add_property("warmth",WARM,WARM_TIME);
     }
  if(this_object()->query_weight_per_bite()){
    setup_eat_piece_messages(this_object()->query_hot_eat_piece_message(),
                                 this_object()->query_hot_eat_amt_message(),
                                 this_object()->query_hot_eat_last_message());
      }
  else{
    set_eat_mess( this_object()->query_hot_eat_message() );
    }
  return( ::do_eat( no_mess ) );
}
void set_hot_eat_message(mixed messages){
   _hot_eat_message = messages;
}
void set_cold_eat_message(mixed messages){
   _cold_eat_message = messages;
}
mixed query_hot_eat_message(){
  return _hot_eat_message;
}
mixed query_cold_eat_message(){
  return _cold_eat_message;
}
void setup_hot_eat_piece_messages(mixed piece, mixed amt, mixed last) {
   _hot_eat_piece_message = piece;
   _hot_eat_amt_message = amt;
   _hot_eat_last_message = last;
}
void setup_cold_eat_piece_messages(mixed piece, mixed amt, mixed last) {
   _cold_eat_piece_message = piece;
   _cold_eat_amt_message = amt;
   _cold_eat_last_message = last;
}
mixed query_cold_eat_piece_message(){
  return _cold_eat_piece_message;
}
mixed query_cold_eat_amt_message(){
  return _cold_eat_amt_message;
}
mixed query_cold_eat_last_message(){
  return _cold_eat_last_message;
}
mixed query_hot_eat_piece_message(){
  return _hot_eat_piece_message;
}
mixed query_hot_eat_amt_message(){
  return _hot_eat_amt_message;
}
mixed query_hot_eat_last_message(){
  return _hot_eat_last_message;
}
mixed *stats(){
   mixed *args;
   args =::stats() + ({ ({ "cool level", _cool_level }),
                        ({ "cool rate", _cool_rate }),
                        ({ "purchase time", _purchase_time }) });
   return args;
}
mapping int_query_static_auto_load(){
   return ([ "::" : ::int_query_static_auto_load(),
             "cool_level" : _cool_level,
             "cool rate" : _cool_rate,
             "purchase time" : _purchase_time ]);
}
mapping query_static_auto_load(){
   if ( ( base_name( this_object() ) != "/obj/food" )
       && !query_continuous() ) {
      return 0;
   }
   return int_query_static_auto_load();
}
void init_static_arg( mapping map ){
   if ( !mapp( map ) ) return;
   if ( map[ "::" ] ) ::init_static_arg( map[ "::" ] );
   _cool_level = map[ "cool_level" ];
   _cool_rate = map[ "cool rate" ];
   _purchase_time = map [ "purchase time" ];
}
mapping query_dynamic_auto_load(){
   return ([ "::" : ::query_dynamic_auto_load(),
             "cool_level" : _cool_level,
             "cool rate" : _cool_rate,
             "purchase time" : _purchase_time ]);
}
void init_dynamic_arg( mapping map, object ){
   if ( !mapp( map ) ) return;
   if ( map[ "::" ] ) ::init_dynamic_arg( map[ "::" ] );
   _cool_level = map[ "cool_level" ];
   _cool_rate = map[ "cool rate" ];
   _purchase_time = map [ "purchase time" ];
}
void do_decay() {
   if (this_object()->query_cool_level()>1) return;
   ::do_decay();
}
int query_decays() {
   if (this_object()->query_cool_level()>1) return 0;
   return 1;
}
int query_decay_speed() {
   if (this_object()->query_cool_level()>1) return 0;
   return (::query_decay_speed());
}
int query_decay_level() {
   if (this_object()->query_cool_level()>1) return 0;
   return (::query_decay_level());
}
void set_decay_speed( int decay ) {
  if (this_object()->query_cool_level()>1) return( ::set_decay_speed( 0 ) );
  return( ::set_decay_speed( 7200 ) );
}
void set_main_plural(mixed str) {
   return;
}