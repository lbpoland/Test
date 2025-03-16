#include <group_handler.h>
#include <function.h>
#include <player.h>
#undef IN_TESTING
#undef IN_STRICT_TESTING
mixed *_patterns;
mapping _sub_commands;
class sub_command {
   string file_name;
   mixed *data;
}
#if defined( IN_TESTING ) || defined( IN_STRICT_TESTING )
int allowed_to_use( object user );
#endif
void rehash_group_sub_commands();
void make_patterns_array();
mixed *query_patterns();
int group_command_control( string verb, mixed *indirect_obs,
   string dir_match, string indir_match, mixed *args, string pattern );
int do_help( string on_what );
void create() {
   rehash_group_sub_commands();
   make_patterns_array();
}
void rehash_group_sub_commands() {
   mixed *files;
   object cmd_object;
   string dir, verb, file, pattern;
   _sub_commands = ([ ]);
   dir = GROUP_SUB_CMDS_DIR;
   dir += GROUP_SUB_CMDS_FILE_WILDCARD;
   files = get_dir( dir );
   if( !sizeof( files ) ) {
      return;
   }
   foreach( file in files ) {
      sscanf( file, "%s.%*s", file );
      cmd_object = load_object( ( GROUP_SUB_CMDS_DIR + file ) );
      if( !cmd_object ) {
         continue;
      }
      if( !cmd_object->query_group_sub_command_amount() ) {
         continue;
      }
      foreach( verb in cmd_object->query_group_sub_command_verbs() ) {
         if( !_sub_commands[ verb ] ) {
            _sub_commands += ([ verb : new( class sub_command ) ]);
         }
         _sub_commands[ verb ]->data = ( mixed * )({ });
         _sub_commands[ verb ]->file_name = ( string )file_name( cmd_object );
         foreach( pattern in
            cmd_object->query_group_sub_command_patterns( verb ) ) {
            _sub_commands[ verb ]->data +=
               ({
               pattern,
               cmd_object->query_group_sub_command_function( verb, pattern )
               });
         }
      }
   }
}
int group_command_control( string verb, mixed *indirect_obs,
   string dir_match, string indir_match, mixed *args, string pattern ) {
   int count, size;
   string cmd_pattern, mangled_pattern, group;
   function cmd_fun;
   object cmd_object;
   class sub_command info;
#if defined( IN_TESTING ) || defined( IN_STRICT_TESTING )
   if( !allowed_to_use( this_player() ) ) {
      return 0;
   }
#endif
   info = _sub_commands[ verb ];
   if( !info ) {
      printf( "ERROR: Command information for \"" + verb + "\""
         " not found.\n" );
      return 0;
   }
   if( pattern != verb ) {
      sscanf( pattern, verb + " %s", mangled_pattern );
   }
   else {
      mangled_pattern = "";
   }
   size = sizeof( info->data );
   for( count = 0; count < size; count += 2 ) {
      if( mangled_pattern == info->data[ count ] ) {
         cmd_pattern = info->data[ count ];
         cmd_fun     = info->data[ count + 1 ];
         break;
      }
   }
   if( !cmd_pattern || !cmd_fun ) {
      printf( "ERROR: Correct version of \"" + verb + "\" not found.\n" );
      tell_creator( this_player(), "DEBUG: Verb: %s, pattern: %s\n",
         verb, pattern );
      return 0;
   }
   if( !cmd_object = load_object( info->file_name ) ) {
      printf( "ERROR: Cannot load command \"" + verb + "\"!\n" );
      tell_creator( this_player(), "DEBUG: File name: %s\n", info->file_name );
      return 0;
   }
   if( functionp( cmd_fun ) & FP_OWNER_DESTED ) {
      info->data[ count + 1 ] = cmd_fun =
         cmd_object->query_group_sub_command_function( verb, cmd_pattern );
   }
   if( !cmd_fun || !functionp( cmd_fun ) ) {
      printf( "ERROR: Could not find command function for verb " +
         "\"" + verb + "\".\n" );
      return 0;
   }
   group = this_player()->query_group();
   if( cmd_object->query_membership_required( verb, cmd_pattern ) > 0 ) {
      if( !group ) {
         return notify_fail( "You must be a member of a group in order "
            "to use this command.\n" );
      }
   }
   if( cmd_object->query_leadership_required( verb, cmd_pattern ) > 0 ) {
      if( GROUP->leader_of( group ) != this_player() ) {
         return notify_fail( "Only the leader of a group can use this "
            "command.\n" );
      }
   }
   return evaluate( cmd_fun, indirect_obs, dir_match, indir_match,
      args, pattern, group );
}
int do_help( string on_what ) {
   int top_left;
   string help, message;
   object command;
   on_what = lower_case( on_what );
#if defined( IN_TESTING ) || defined( IN_STRICT_TESTING )
   if( !allowed_to_use( this_player() ) ) {
      return 0;
   }
#endif
   if( on_what == "help" ) {
      return notify_fail( "To get help on a command, use \"group help <sub-"
         "command>\".  That is, if you wanted to get help on the command "
         "\"group create <name>\", you would type \"group help create\".\n" );
   }
   if( !_sub_commands[ on_what ] ) {
      return notify_fail( "There is no sub-command called \"" + on_what +
         "\".\n" );
   }
   command = load_object( _sub_commands[ on_what ]->file_name );
   if( !command ) {
      tell_creator( this_player(), "Alleged file name: %s\n",
         _sub_commands[ on_what ]->file_name );
      return notify_fail( "ERROR: Cannot find or load sub-command "
         "\"" + on_what + "\".\n" );
   }
   help = command->query_help_string_for( on_what );
   if( !help ) {
      return notify_fail( "No help found for sub-command \"" + on_what +
         "\".\n" );
   }
   top_left = this_player()->query_cols();
   message = sprintf(
      "\n%' '|*s\n"
      "%' '-=*s\n",
      top_left, "Help on sub-command \"" + on_what + "\":\n",
      top_left, help );
   this_player()->more_string( message );
   return 1;
}
void make_patterns_array() {
   int count, size;
   string verb, pattern;
   class sub_command command;
   _patterns = ({ });
   _patterns += ({
      "help <word'sub-command'>", (: do_help( $4[ 0 ] ) :) });
   foreach( verb, command in _sub_commands ) {
      size = sizeof( command->data );
      for( count = 0; count < size; count += 2 ) {
         if( sizeof( command->data[ count ] ) ) {
            pattern = verb + " " + command->data[ count  ];
         }
         else {
            pattern = verb;
         }
         _patterns += ({
            pattern, (: group_command_control( $( verb ), $1, $2, $3, $4,
               $5 ) :) });
      }
   }
}
mixed *query_patterns() {
   return _patterns;
}
#if defined( IN_TESTING ) || defined( IN_STRICT_TESTING )
int allowed_to_use( object user ) {
#endif
#ifdef IN_STICT_TESTING
   if( !user->query_creator() ) {
      tell_object( user, "You are not allowed to use this feature at this "
         "time.\n" );
      return 0;
   }
#endif
#ifdef IN_TESTING
   if( !PLAYTESTER_HAND->query_tester( user ) ) {
      tell_object( user, "You are not allowed to use this feature at this "
         "time.\n" );
      return 0;
   }
#endif
#if defined( IN_TESTING ) || defined( IN_STRICT_TESTING )
   return 1;
}
#endif
mapping dump_info() { return _sub_commands; }
mixed *dump_patterns() { return _patterns; }