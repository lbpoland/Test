inherit "/std/object";
private nosave int _amount;
private nosave string *_shorts;
private nosave string *_longs;
string fuel_short();
string fuel_long();
void create(){
   ::create();
   if(!_amount){
     _amount = 100;
   }
   set_short( (: fuel_short :) );
   set_long( (: fuel_long :) );
   add_property("no recycling", 1);
   add_property("fuel", 1);
}
void set_amount_left(int i){  _amount = i;  }
void adjust_amount_left(int i){  _amount += i;  }
int query_amount_left(){  return _amount;  }
void set_shorts(string *desc){  _shorts = desc;  }
void set_longs(string *desc){  _longs = desc;  }
string fuel_short(){
   int i;
   int x;
   x = sizeof(_shorts);
   for(i = 1; i <= x; i++){
      if( (_amount + 1) > 100 - ( i * 100 / x ) ){
         return _shorts[(i-1)];
      }
   }
   return "fuel";
}
string fuel_long(){
   int i;
   int x;
   x = sizeof(_longs);
   for(i = 1; i <= x; i++){
      if( ( _amount + 1 ) > ( 100 - ( i * 100 / x )) ){
         return _longs[(i-1)];
      }
   }
   return "fuel";
}
mixed query_dynamic_auto_load() {
   return ([ "::" : ::query_dynamic_auto_load(),
             "amount" : _amount
          ]);
}
void init_dynamic_arg(mapping arg) {
   _amount = arg[ "amount" ];
   ::init_dynamic_arg(arg["::"]);
}