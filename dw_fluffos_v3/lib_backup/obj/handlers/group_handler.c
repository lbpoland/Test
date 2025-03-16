#include <group_handler.h>
#include <broadcaster.h>
#include <login_handler.h>
int _loaded;
int _groups_formed;
mapping _groups;
class group
{
   int start_time;
   string short;
   string leader_name;
   object leader;
   object *members;
   object *invited;
}
int is_group( string group );
int is_member( string name, object person );
int is_invited( string name, object person );
object *invitations_to( string name );
string query_group_short( string name );
object *members_of( string name );
object leader_of( string name );
string short_to_name( string short );
int create_group( string name );
int remove_group( string name );
int add_invite( string name, object person, int flag );
int remove_invite( string name, object person );
int add_member( string name, object person );
int remove_member( string name, object person );
varargs int set_leader( string name, object person, object appointer );
void notify_group( string name, object broadcaster, mixed message );
varargs void disband_group( string name, mixed message );
varargs object shuffle_new_leader( string group, int way, object *exclude );
void leader_goes_linkdead( string player, string event_type );
void handle_group_follow( string group, object who, object *what,
   int unfollow, int silent );
void broadcast_to_groups( string *name, string message );
string *query_groups();
int set_group_short( string, string);
void create()
{
   _groups = ([ ]);
   _loaded = time();
   _groups_formed = 0;
}
void dest_me() {
   string name;
   broadcast_to_groups( 0, "%^BOLD%^WARNING%^RESET%^: The group handler is being destructed."
      "  All active groups will be disbanded.  It should be possible to "
      "recreate the group almost immediately afterwards.  If not, please "
      "file a bug report for the \"group\" command." );
   foreach( name in query_groups() ) {
      disband_group( name, 0 );
   }
}
void stats_please() {
   printf( "The handler was loaded on %s.  Since then, "
      "%i groups have been formed.\n", ctime( _loaded ),
      _groups_formed );
}
string *query_groups() {
   return keys( _groups );
}
int is_group( string group ) {
   return !undefinedp( _groups[ group ] );
}
int is_member( string name, object person ) {
   if( !is_group( name ) ) {
      return 0;
   }
   if( member_array( person, _groups[ name ]->members ) == -1 ) {
      return 0;
   }
   return 1;
}
int is_invited( string name, object person )
{
   if( member_array( person, _groups[ name ]->invited ) != -1 )
   {
      return 1;
   }
   return 0;
}
object *invitations_to( string name )
{
   if( !is_group( name ) )
   {
      return 0;
   }
   return _groups[ name ]->invited;
}
string query_group_short( string name )
{
   if( !is_group( name ) )
   {
      return 0;
   }
   return _groups[ name ]->short;
}
object *members_of( string name )
{
   if( !is_group( name ) )
   {
      return 0;
   }
   return _groups[ name ]->members;
}
object leader_of( string name )
{
   if( !is_group( name ) )
   {
      return 0;
   }
   return _groups[ name ]->leader;
}
int query_start_time( string name )
{
   if( !is_group( name ) )
   {
      return 0;
   }
   return _groups[ name ]->start_time;
}
string short_to_name( string short )
{
   string *words;
   short = lower_case( short );
   words = explode( short, " " );
   words -= INVALID_WORDS;
   if( !sizeof( words ) ) {
      return "";
   }
   short = implode( words, " " );
   if( BROADCASTER->query_channel_members( "group_" + short ) ) {
      return "";
   }
   return short;
}
int create_group( string name )
{
   if( is_group( name ) ) {
      return 0;
   }
   _groups += ([ name : new( class group ) ]);
   _groups[ name ]->members = ({ });
   _groups[ name ]->invited = ({ });
   _groups[ name ]->start_time = time();
   _groups_formed++;
   return 1;
}
int rename_group(string group, string new_group) {
   object member;
   if (is_group(new_group) || new_group == group) {
      return 0;
   }
   _groups[new_group] = _groups[group];
   map_delete(_groups, group);
   set_group_short(new_group, new_group);
   foreach (member in _groups[new_group]->members) {
      if (!member) {
         continue;
      }
      BROADCASTER->remove_object_from_channel( "group_" + group, member );
      member->group_membership_removed();
      member->add_effect( EFFECT, new_group);
      BROADCASTER->add_object_to_channel( "group_" + new_group, member );
      member->set_title( GROUP_TITLE, "a member of " +
      query_group_short( new_group ) );
   }
   notify_group( new_group, this_object(), ({ "", "The group has been renamed to " +
      new_group + "." }) );
   return 1;
}
int set_group_short( string name, string short_desc )
{
   if( !is_group( name ) ) {
      return 0;
   }
   _groups[ name ]->short = short_desc;
   return 1;
}
int remove_group( string name )
{
   if( !is_group( name ) ) {
      return 0;
   }
   if( _groups[ name ]->leader_name ) {
      LOGIN_HANDLER->remove_login_call(
         _groups[ name ]->leader_name, "leader_goes_linkdead",
         this_object() );
   }
   map_delete( _groups, name );
   return 1;
}
int add_invite( string name, object person, int flag )
{
   if( !is_group( name ) )
   {
      return 0;
   }
   if( is_member( name, person ) )
   {
      return 0;
   }
   if( member_array( person, _groups[ name ]->invited ) != -1 )
   {
      return 0;
   }
   _groups[ name ]->invited += ({ person });
   if( !flag )
   {
      call_out( (: remove_invite, name, person :), INVITE_TIMEOUT );
   }
   return 1;
}
int remove_invite( string name, object person )
{
   if( !is_group( name ) )
   {
      return 0;
   }
   if( !is_invited( name, person ) )
   {
      return 0;
   }
   _groups[ name ]->invited -= ({ person, 0 });
   return 1;
}
int add_member( string name, object person )
{
   if( !is_group( name ) )
   {
      return 0;
   }
   if( is_member( name, person ) )
   {
      return 0;
   }
   _groups[ name ]->members += ({ person });
   _groups[ name ]->invited -= ({ person });
   person->add_effect( EFFECT, name );
   BROADCASTER->add_object_to_channel( "group_" + name, person );
   notify_group( name, person, ({ "You have joined the group.",
      person->query_cap_name() + " has joined the group." }) );
   if( sizeof( _groups[ name ]->members ) > 1 )
   {
      handle_group_follow( name, person, ({ _groups[ name ]->leader }), 0, 0 );
   }
   person->set_title( GROUP_TITLE, "a member of " +
      query_group_short( name ) );
   return 1;
}
int remove_member( string name, object person )
{
   object member;
   if( !is_group( name ) )
   {
      return 0;
   }
   if( !is_member( name, person ) )
   {
      return 0;
   }
   if( person )
   {
      notify_group( name, person, ({
         "You have left the group.",
      person->query_cap_name() + " has left the group." }) );
      foreach( member in person->query_assisting() )
      {
         if( !member )
         {
            continue;
         }
         member->remove_assister( person );
      }
      foreach( member in person->query_assisters() )
      {
         if( !member )
         {
            continue;
         }
         member->remove_assisting( person );
      }
   }
   _groups[ name ]->members -= ({ person });
   BROADCASTER->remove_object_from_channel( "group_" + name, person );
   if( person )
   {
      person->group_membership_removed();
   }
   if( person == leader_of( name ) && sizeof( members_of( name ) ) )
   {
      if (sizeof(members_of(name)) == 1) {
         notify_group( name, this_object(), "The current leader has left "
            "the group, you are now all alone.  Better start recruiting.");
      } else {
         notify_group( name, this_object(), "The current leader has left "
            "the group.  A new leader will be chosen randomly." );
      }
      if( !shuffle_new_leader( name, 0 ) )
      {
         notify_group( name, this_object(), "The choosing of a new "
            "leader has failed (oh dear).  The group is hereby "
            "disbanded.\n" );
         call_out( "disband_group", 0, name );
         return 1;
      }
   }
   handle_group_follow( name, person, _groups[ name ]->members, 1, 1 );
   foreach( member in _groups[ name ]->members ) {
      handle_group_follow( name, member, ({ person }), 1, 1 );
   }
   if (person && objectp(person)) {
      person->remove_title( GROUP_TITLE );
   }
   if( !sizeof( members_of( name ) ) ) {
      remove_group( name );
   }
   return 1;
}
varargs int set_leader( string name, object person, object appointer )
{
   object *followers, old_leader, member;
   if( !is_group( name ) )
   {
      return 0;
   }
   if( !is_member( name, person ) )
   {
      return 0;
   }
   if( !person )
   {
      return 0;
   }
   if( _groups[ name ]->leader_name )
   {
      LOGIN_HANDLER->remove_dynamic_login_call(
         _groups[ name ]->leader_name, "leader_goes_linkdead",
         base_name( this_object() ) );
   }
   old_leader = _groups[ name ]->leader;
   if( old_leader )
   {
      followers = ( old_leader->query_followers() & _groups[ name ]->members );
      followers -= ({ 0 });
      followers += ({ old_leader });
      foreach( member in followers )
      {
         handle_group_follow( name, member, ({ old_leader }), 1, 1 );
         handle_group_follow( name, member, ({ person }), 0, 1 );
      }
      old_leader->set_title( GROUP_TITLE, "a member of " +
         query_group_short( name ) );
   }
   _groups[ name ]->leader = person;
   if( userp( person ) ) {
      _groups[ name ]->leader_name = person->query_name();
      LOGIN_HANDLER->add_dynamic_login_call( person->query_name(),
         "leader_goes_linkdead", base_name( this_object() ) );
   }
   else
   {
      _groups[ name ]->leader_name = 0;
   }
   if( !appointer )
   {
      notify_group( name, person, ({ "You are now the leader of "
         "the group.", person->query_cap_name() + " is now the leader "
         "of the group." }) );
   }
   else
   {
      notify_group( name, appointer, "By the power vested in " +
         appointer->query_cap_name() + ", " + person->query_cap_name() +
         " has been appointed as the new leader of the group." );
   }
   person->set_title( GROUP_TITLE, "the leader of " +
      GROUP->query_group_short( name ) );
   return 1;
}
void notify_group( string name, object broadcaster, mixed message ) {
   BROADCASTER->broadcast_to_channel( broadcaster, "group_" + name,
      ({ message, time() }) );
}
varargs void disband_group( string name, mixed message ) {
   object bugger, leader, *members;
   if( !is_group( name ) ) {
      return;
   }
   if( message ) {
      notify_group( name, this_object(), message );
   }
   members = members_of( name );
   leader = leader_of( name );
   if( leader ) {
      members -= ({ leader });
   }
   foreach( bugger in members ) {
      remove_member( name, bugger );
   }
   remove_member( name, leader );
   remove_group( name );
}
varargs object shuffle_new_leader( string group, int way, object *exclude ) {
   object leader;
   object *members;
   if( !is_group( group ) ) {
      return 0;
   }
   members = members_of( group );
   if( !sizeof( members ) ) {
      return 0;
   }
   if( exclude ) {
      members -= exclude;
   }
   members = filter( members, (: $1 && interactive( $1 ) :) );
   if( !sizeof( members ) ) {
      return 0;
   }
   switch( way ) {
      case 0:
         leader = members[ random( sizeof( members ) ) ];
         if( set_leader( group, leader ) ) {
            return leader;
         }
         return 0;
      default:
         return 0;
   }
}
void leader_goes_linkdead( string player, string event_type ) {
   string group;
   object player_ob, *members;
   if( event_type != NETDEATH && event_type != RECONNECT ) {
      LOGIN_HANDLER->remove_dynamic_login_call( player,
         "leader_goes_linkdead", base_name( this_object() ) );
      return;
   }
   if( !player_ob = find_player( player ) ) {
      LOGIN_HANDLER->remove_dynamic_login_call( player,
         "leader_goes_linkdead", base_name( this_object() ) );
      return;
   }
   group = player_ob->query_group();
   if( !group ) {
      LOGIN_HANDLER->remove_dynamic_login_call( player,
         "leader_goes_linkdead", base_name( this_object() ) );
      return;
   }
   if( _groups[ group ]->leader_name != player ) {
      LOGIN_HANDLER->remove_dynamic_login_call( player,
         "leader_goes_linkdead", base_name( this_object() ) );
      return;
   }
   members = members_of( group );
   members -= ({ player_ob });
   if( !sizeof( members ) ) {
      return;
   }
   LOGIN_HANDLER->remove_dynamic_login_call( player,
      "leader_goes_linkdead", base_name( this_object() ) );
   notify_group( group, this_object(), "The current leader "
      "has gone netdead.  A new leader will be selected at random." );
   if( !shuffle_new_leader( group, 0, 0 ) ) {
      notify_group( group, this_object(), "No eligible leaders "
         "found.  The group is disbanded." );
      disband_group( group );
   }
}
void handle_group_follow( string group, object who, object *what,
   int unfollow, int silent ) {
   string short, mess_to_me, mess_to_others;
   switch( unfollow ) {
      case 0:
         what = filter( what, (: $1->add_follower( $( who ) ) :) );
         if( !sizeof( what ) ) {
            mess_to_me = "You begin following noone.";
            break;
         }
         short = query_multiple_short( what );
         mess_to_me = "You begin following " + short + ".";
         mess_to_others = who->query_cap_name() + " begins following " +
            short + ".";
         break;
      case 1:
         what = filter( what, (: $1->remove_follower( $( who ) ) :) );
         if( !sizeof( what ) ) {
            mess_to_me = "You stop following noone.";
            mess_to_others = 0;
            break;
         }
         short = query_multiple_short( what );
         mess_to_me = "You stop following " + short + ".";
         mess_to_others = who->query_cap_name() + " stops following " +
            short + ".";
         break;
      default:
         printf( "Barf.\n" );
         return;
   }
   if( !silent ) {
      notify_group( group, who, ({ mess_to_me, mess_to_others }) );
   }
}
void broadcast_to_groups( string *name, string message ) {
   string group;
   string *groups;
   if( name && sizeof( name ) ) {
      groups = name;
   }
   else {
      groups = keys( _groups );
   }
   foreach( group in groups ) {
      notify_group( group, this_player(), message );
   }
}
mapping query_dynamic_auto_load() {
   return ([ "groups" : _groups,
             "groups formed" : _groups_formed ]);
}
void init_dynamic_arg(mapping map) {
   _groups = map["groups"];
   _groups_formed = map["groups formed"];
}