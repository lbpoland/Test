inherit "/std/room/furniture/fireplace";
void setup(){
  set_allowed_positions(({"sitting"}));
  set_allowed_room_verbs((["sitting" : "sits" ]));
  set_weight(700);
  set_max_weight(100);
  set_short("finely crafted fireplace");
  set_long("This fireplace is surrounded by an ornately carved mahogany "
     "framework and has a beautifully finished brass hearth.\n");
  set_value(900000);
}