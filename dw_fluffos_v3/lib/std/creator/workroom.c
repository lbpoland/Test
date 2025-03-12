#include <config.h>
inherit "/std/room/basic_room";
object button, bookcase, board;
void setup() {
  set_short("workroom of "+ CREATOR);
  add_property( "determinate", "the ");
  set_light(100);
  set_long("This is the workroom of "+CREATOR+".  You can see a small "
     "wooden desk sulking in the corner of the room, it has a "
     "beautifully carved wooden rolly chair in front of it.  It "
     "looks like this was just newly created, there is a smell "
     "of paint and leather in the air.\n");
  add_item("chair",
        ({ "long", "The teak rolly chair has amazing carvings of dragons "
                   "and ... other things on it.  They almost seem alive, "
                   "you especially don't note the way the dragon "
                   "blinks at you.",
                   "position",
                   "the teak rolly chair" }) );
  add_item("desk", "The desk is made of mahogany with a touch of "
     "mountain ash.  The top has two little basket things "
     "on it labelled \"in\" and \"out\".  The in basket "
     "is rather small." );
  add_item( "dragon", "I told you, you don't notice it winking at you." );
  add_item("in basket", "The in basket is full of small yellow forms "
     "with large red letters on them saying "
     "\"Important read me first\" and then not "
     "appearing to actually have any thing else on "
     "them." );
  add_item( "out basket", "The out basket is completely empty." );
  add_item("basket", "There are two baskets sitting on top of the desk.  "
     "They have the words \"in\" and \"out\" written "
     "on them." );
  add_item("paint", "You look around to see the source of the paint "
     "smell and you can't find it.  The walls? of the room "
     "ummm seem to be well shall we just twisting in a "
     "confused mish mash of shapes, you are sure they are "
     "not threatening." );
  add_item("wall", "The walls are made up of a cloudy substance, white "
     "in nature that is roiling around the place where "
     "you are standing.  Great magic must be holding it "
     "back, every now and then you see a demonic head "
     "push its way out of the cloud roll its eyes and fade "
     "back into the cloud." );
  add_item("cloud", "The cloud is white coloured with a few flashes "
     "of light bursting in it." );
  add_item("demon", "The demonic heads that pop out are pretty nasty "
     "looking, they disapear with a snarl of strain." );
  add_exit("common", "/w/common", "door");
  add_exit("drum", CONFIG_START_LOCATION, "path");
  add_exit("learning", "/d/learning/main", "path");
  modify_exit( ({ "common", "drum", "learning" }),
      ({ "function", "check_player" }) );
  add_alias("north", "drum");
  add_alias("south", "common");
  "/w/common"->add_exit(CREATOR, "/w/"+CREATOR+"/workroom", "door");
}
void reset() {
  if (!button) {
    button = clone_object("/obj/misc/button");
    button->move(this_object());
  }
  if (!board) {
    board = clone_object("/obj/misc/board_mas");
    board->move(this_object() );
  }
  if (!bookcase) {
    bookcase = clone_object("/obj/cont_save");
    bookcase->set_name( "bookcase" );
    bookcase->set_short( "oaken bookcase" );
    bookcase->add_adjective( "wooden" );
    bookcase->add_adjective( "oak" );
    bookcase->add_adjective( "oaken" );
    bookcase->add_property( "there", "standing against the wall" );
    bookcase->set_long( "This bookcase is made from oak and "
      "varnished to bring out the glow.  It has 2 "
      "shelves, upon which you can see some books, and "
      "other objects.\n" );
    bookcase->set_weight( 2000 );
    bookcase->set_max_weight( 4000 );
    bookcase->reset_get();
    bookcase->check_euid();
    bookcase->set_save_file( "/w/"+CREATOR+"/creator_kit" );
    bookcase->move( this_object() );
  }
}
object *query_non_destable()  {
  return ({ bookcase, board });
}
int check_player( string verb, object player, string special ) {
    if ( interactive( player ) ) {
        return 1;
    }
    notify_fail( "" );
    return 0;
}