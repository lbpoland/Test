#include <command.h>
#define READ ( DIR_LIVING_CMDS "/r_ead" )
inherit "/cmds/base";
int do_show_object( object shower, object item, object owner, object target, int no_mess );
#ifdef DEBUG
int notify_fail(string str) {
  tell_object(find_player("tape"), "%^YELLOW%^"+
              this_player()->query_short()+" "+str+"%^RESET%^\n");
  return efun::notify_fail(str);
}
#endif
int cmd( object item, object target )
{
   return do_show_object( this_player(), item, this_player(), target, 0 );
}
int do_show_object( object shower, object item, object owner, object target, int nomess )
{
   tell_creator( shower, "%O\n%O\n", item, target );
   if( target == shower ) {
      add_failed_mess( "Why not just look at it?\n");
      return 0;
   }
   if( !shower->query_visible( target ) ) {
      add_failed_mess( "It appears that " + target->the_short() +
         " can't see you or your item.\n" );
      return 0;
   }
   if( target->query_property( "ignoring" ) ) {
      if( member_array( shower->query_name(),
         target->query_property( "ignoring" ) ) != -1 ) {
         add_failed_mess( target->the_short() + " ignores you.\n" );
         return 0;
      }
   }
   if( item->query_worn_by() ) {
      add_failed_mess( item->the_short() + " must be removed before it can be "
         "shown.\n" );
      return 0;
   }
   target->add_respond_command( "show offer", this_object(),
      ({ item, owner, shower }) );
   if( !nomess )
   {
      tell_room( environment( shower ), shower->the_short() +
         " offers to show " + item->a_short() + " to " +
         target->a_short() + ".\n",
         ({ target, shower }) );
      tell_object( shower, "You offer " + item->the_short() +
         " to " + target->the_short() + " for inspection.\n" );
      tell_object( target, shower->the_short() + " offers you " +
         item->a_short() + " for inspection.  Use \"show accept offer "
         "from " + shower->query_name() + "\" to view it.\n" );
   }
   return 1;
}
int accept_show( object target, int read ) {
   mixed *stuff;
   object from;
   object owner;
   object item;
   string message;
   if( target == this_player() ) {
      add_failed_mess( "You cannot show stuff to yourself.\n");
      return 0;
   }
   stuff = this_player()->query_respond_command(
      "show offer", this_object() );
   if( !sizeof( stuff ) ) {
      add_failed_mess( "No one has offered to show you anything.\n");
      return 0;
   }
   item     = stuff[ 0 ];
   owner    = stuff[ 1 ];
   from     = stuff[ 2 ];
   if( !from || target != from ) {
      add_failed_mess( target->the_short() + " hasn't offered "
         "to show you anything.\n" );
      return 0;
   }
   if( !item || ( owner && environment( item ) != owner ) )
   {
      add_failed_mess( "It appears that " + target->the_short() +
         " has misplaced " + target->query_possessive() + " item.\n");
      return 0;
   }
   this_player()->remove_respond_command( "show offer", this_object() );
   tell_room( environment( this_player() ), this_player()->the_short() +
      " accepts the offer from " +
      target->the_short() +
      " to see " + item->the_short() + ".\n", ({ this_player(), target }) );
   message = "You accept " + target->the_short() + "'s offer.\n";
   tell_object( target, "You show " + item->the_short() + " to " +
      this_player()->the_short() + ".\n" );
   message += "\n";
   if( this_player()->query_creator() ) {
      message += "%^CYAN%^" + file_name( item ) + ":%^RESET%^\n";
   }
   message += item->long();
   if( sizeof( item->query_read_mess() ) ) {
      message += item->the_short() + " also contains some writing.\n";
      message += item->query_readable_message(this_player());
   }
   write("$P$Show$P$" + message);
   return 1;
}
mixed *query_patterns() {
   return ({
      "<indirect:object:me'item'> to <indirect:living'living'>",
         (: cmd( $1[ 0 ][ 0 ], $1[ 1 ][ 0 ] ) :),
      "accept [offer] [from] <indirect:living'living'>",
         (: accept_show( $1[ 0 ], 0 ) :) });
}