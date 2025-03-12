inherit "/std/room/basic_room";
object	button;
void	after_reset();
void	dest_me();
void	reset();
void	setup();
void
after_reset()
{
     if ( !button )
     {
	button = clone_object( "/obj/misc/button" );
	button->move( this_object() );
     }
}
void
dest_me()
{
    if ( button )  button->dest_me();
    ::dest_me();
}
void
reset()
{
    call_out( "after_reset" , 1 );
}
void setup() {
     set_light(100);
     set_short("Graveyard");
  set_long( "This room is full of broken bits and pieces of objects which "+
      "decided not to work or behave properly.\n" );
}
void init() {
  ::init();
  co_ord = 0;
}
int *query_co_ord() { return 0; }