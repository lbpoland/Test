#define GROUP_ARRAY_SIZE      3
#define GROUP_ARRAY_FUNCTION  0
#define GROUP_ARRAY_MEM_REQ   1
#define GROUP_ARRAY_LDR_REQ   2
mapping _commands;
void create() {
   _commands = ([ ]);
}
int query_group_sub_command_amount() {
   return sizeof( _commands );
}
int add_group_sub_command( string verb, string pattern,
   function cmd_function ) {
   if( !_commands[ verb ] ) {
      _commands += ([ verb : ([ pattern : ({ cmd_function, 0, 0 }) ]) ]);
      return 1;
   }
   if( _commands[ verb ][ pattern ] ) {
      return 0;
   }
   _commands[ verb ] += ([ pattern : ({ cmd_function, 0, 0 }) ]);
   return 1;
}
varargs int remove_group_sub_command( string verb, string pattern ) {
   if( undefinedp( pattern ) ) {
      if( !_commands[ verb ] ) {
         return 0;
      }
      map_delete( _commands, verb );
      return 1;
   }
   if( !_commands[ verb ] || !_commands[ verb ][ pattern ] ) {
      return 0;
   }
   map_delete( _commands[ verb ], pattern );
   return 1;
}
string *query_group_sub_command_verbs() {
   return keys( _commands );
}
string *query_group_sub_command_patterns( string verb ) {
   if( !_commands[ verb ] ) {
      return 0;
   }
   return keys( _commands[ verb ] );
}
varargs function *query_group_sub_command_function( string verb, string
   pattern ) {
   if( !_commands[ verb ] ) {
      return 0;
   }
   if( undefinedp( pattern ) ) {
      return values( _commands[ verb ] );
   }
   if( !_commands[ verb ][ pattern ] ) {
      return 0;
   }
   return _commands[ verb ][ pattern ][ GROUP_ARRAY_FUNCTION ];
}
int set_membership_required( string verb, string pattern, int flag ) {
   mixed *dummy;
   string key;
   if( !_commands[ verb ] ) {
      return 0;
   }
   if( pattern ) {
      if( !_commands[ verb ][ pattern ] ) {
         return 0;
      }
      _commands[ verb ][ pattern ][ GROUP_ARRAY_MEM_REQ ] = flag;
      return 1;
   }
   foreach( key, dummy in _commands[ verb ] ) {
      _commands[ verb ][ key ][ GROUP_ARRAY_MEM_REQ ] = flag;
   }
   return 1;
}
int set_leadership_required( string verb, string pattern, int flag ) {
   mixed *dummy;
   string key;
   if( !_commands[ verb ] ) {
      return 0;
   }
   if( pattern ) {
      if( !_commands[ verb ][ pattern ] ) {
         return 0;
      }
      _commands[ verb ][ pattern ][ GROUP_ARRAY_LDR_REQ ] = flag;
      return 1;
   }
   foreach( key, dummy in _commands[ verb ] ) {
      _commands[ verb ][ key ][ GROUP_ARRAY_LDR_REQ ] = flag;
   }
   return 1;
}
varargs int query_membership_required( string verb, string pattern ) {
   if( !_commands[ verb ] ) {
      return -1;
   }
   if( undefinedp( pattern ) ) {
      return _commands[ verb ][ keys( _commands[ verb ] )[ 0 ] ]
         [ GROUP_ARRAY_MEM_REQ ];
   }
   if( !_commands[ verb ][ pattern ] ) {
      return -1;
   }
   return _commands[ verb ][ pattern ][ GROUP_ARRAY_MEM_REQ ];
}
varargs int query_leadership_required( string verb, string pattern ) {
   if( !_commands[ verb ] ) {
      return -1;
   }
   if( undefinedp( pattern ) ) {
      return _commands[ verb ][ keys( _commands[ verb ] )[ 0 ] ]
         [ GROUP_ARRAY_LDR_REQ ];
   }
   if( !_commands[ verb ][ pattern ] ) {
      return -1;
   }
   return _commands[ verb ][ pattern ][ GROUP_ARRAY_LDR_REQ ];
}