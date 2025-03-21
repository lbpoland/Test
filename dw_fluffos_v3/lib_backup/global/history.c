#define COLS (int)this_object()->query_cols()
nosave string *history;
nosave int hoffset, numoff;
nosave int in_alias_command;
nosave string ignore_history;
void history_commands() {}
string substitute_history(string arg) {
  string s1, s2;
  if (sscanf(arg, "%s^%s", s1, s2) != 2)
    return arg;
  sscanf(s2, "%s^", s2);
  if (hoffset)
    return replace(history[hoffset-1], s1, s2);
  else
    return replace(history[sizeof(history)-1], s1, s2);
}
protected string expand_history( string arg ) {
   int num, i;
   if (arg[0] == '.' || strlen(arg) == 0) {
      if (hoffset) {
         return history[hoffset-1]+arg[1..strlen(arg)];
      } else {
         return history[sizeof(history)-1]+arg[1..strlen(arg)];
      }
   }
   if (sscanf(arg,"%d",num)==1) {
      num = num % sizeof(history);
      if (num<0) {
         num += hoffset;
         if (num<0) {
            num += sizeof(history);
         }
      }
      return history[num];
   }
   for (i=hoffset-1;i>=0;i--) {
      if (stringp(history[i])) {
         if (strsrch(history[i],arg)==0) {
            return history[i];
         }
      }
   }
   for (i=sizeof(history)-1;i>hoffset;i--) {
      if (stringp(history[i])) {
         if (strsrch(history[i],arg)==0) {
            return history[i];
         }
      }
   }
   return arg;
}
void ignore_from_history(string str) {
  ignore_history = str;
}
void add_history( string arg ) {
   if (ignore_history) {
      if (ignore_history == arg) {
         ignore_history = 0;
         return ;
      }
      ignore_history = 0;
   }
   if (arg == "" || arg[0] == '.' || arg[0] == '^')
      return;
   if (in_alias_command)
      return;
   if (!history) {
      history = allocate(40);
      numoff = -40;
   }
   history[hoffset++] = arg;
   if (hoffset>=sizeof(history)) {
      numoff += sizeof(history);
      hoffset = 0;
   }
}
nomask int print_history( string arg ) {
   int i, from, to, num;
   if(this_player()!=this_object()) {
      if(!interactive(this_player())) {
         return 0;
      }
      if(!(master()->query_lord(geteuid(this_player()))) &&
         !master()->is_liaison_deputy(geteuid(this_player()))) {
         return 0;
      }
   }
  if(this_object()!=this_player(1)) {
   user_event( this_object(), "inform",
               "Print history called on " + this_object()->query_name() +
               " by " + this_player()->query_name(),
               "calls", this_player());
  }
   from = hoffset;
   num = sizeof(history);
   if (!arg) {
      arg = "";
   }
   if (sscanf(arg,"%d,%d",from,to)==2) {
      num = to-from;
      if (num<0) {
         from = from+num;
         num = -num;
      }
   } else if (sscanf(arg,",%d",to)==1) {
      from = hoffset+1+num;
      num = from - (to%sizeof(history))+sizeof(history);
   } else if (sscanf(arg,"%d,",from)==1) {
      from = from % sizeof(history);
      num = from - hoffset;
      if (num<0) {
         num += sizeof(history);
      }
   } else if (sscanf(arg,"%d",num)!=1) {
         num = sizeof(history);
   }
   if(sizeof(history)) {
     from = from % sizeof(history);
   } else {
     from = 0;
   }
   if (num>sizeof(history)) {
     num = sizeof(history);
   }
   if (num <= 0) {
     add_failed_mess("Range out of bounds.\n");
     return 0;
   }
   for (i=from;i<sizeof(history);i++,num--) {
     if (history[i]) {
       printf( "%s%-=*s\n", sprintf( "% 4d", i + numoff ) +": ", COLS - 6,
               history[ i ] );
     }
     if (!num) {
       return 1;
     }
   }
   for (i=0;i<from;i++,num--) {
     if (history[i]) {
       printf( "%s%-=*s\n", sprintf( "% 4d", i + numoff + sizeof( history ) ) +
               ": ", COLS - 6, history[ i ] );
     }
     if (!num) {
       return 1;
     }
   }
   return 1;
}
nomask protected string *get_history() {
  return history;
}