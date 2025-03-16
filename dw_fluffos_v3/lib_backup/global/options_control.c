#define PLAYER_OPTIONS_CLASS
#include <player.h>
mixed query_property(string);
varargs void add_property(string,mixed,int);
private class player_options_control query_player_options() {
   class player_options_control options;
   options = query_property(PLAYER_OPTIONS_CONTROL_PROP);
   if (!options) {
      return new(class player_options_control);
   }
   if (sizeof(options) == 4) {
      class player_options_control newbit;
      newbit = new(class player_options_control);
      newbit->follow_everyone = options->follow_everyone;
      newbit->follow_groups = options->follow_groups;
      newbit->follow_friends = options->follow_friends;
      newbit->lead_behind = options->lead_behind;
      options = newbit;
   }
   return options;
}
int query_auto_follow_group() {
   class player_options_control options;
   options = query_property(PLAYER_OPTIONS_CONTROL_PROP);
   if (!options) {
      return 0;
   }
   return options->follow_groups;
}
int query_auto_follow_friends() {
   class player_options_control options;
   options = query_property(PLAYER_OPTIONS_CONTROL_PROP);
   if (!options) {
      return 0;
   }
   return options->follow_friends;
}
int query_auto_follow_everyone() {
   class player_options_control options;
   options = query_property(PLAYER_OPTIONS_CONTROL_PROP);
   if (!options) {
      return 0;
   }
   return options->follow_everyone;
}
int query_lead_from_behind() {
   class player_options_control options;
   options = query_property(PLAYER_OPTIONS_CONTROL_PROP);
   if (!options) {
      return 0;
   }
   return options->lead_behind;
}
void set_auto_follow_group(int flag) {
   class player_options_control options;
   options = query_property(PLAYER_OPTIONS_CONTROL_PROP);
   if (!options) {
      options = new(class player_options_control);
   }
   options->follow_groups = flag;
   add_property(PLAYER_OPTIONS_CONTROL_PROP, options);
}
void set_auto_follow_friends(int flag) {
   class player_options_control options;
   options = query_property(PLAYER_OPTIONS_CONTROL_PROP);
   if (!options) {
      options = new(class player_options_control);
   }
   options->follow_friends = flag;
   add_property(PLAYER_OPTIONS_CONTROL_PROP, options);
}
void set_auto_follow_everyone(int flag) {
   class player_options_control options;
   options = query_property(PLAYER_OPTIONS_CONTROL_PROP);
   if (!options) {
      options = new(class player_options_control);
   }
   options->follow_everyone = flag;
   add_property(PLAYER_OPTIONS_CONTROL_PROP, options);
}
void set_lead_from_behind(int flag) {
   class player_options_control options;
   options = query_property(PLAYER_OPTIONS_CONTROL_PROP);
   if (!options) {
      options = new(class player_options_control);
   }
   options->lead_behind = flag;
   add_property(PLAYER_OPTIONS_CONTROL_PROP, options);
}
void set_mxp_disable(int flag) {
   class player_options_control options;
   options = query_player_options();
   options->mxp_disable = 1;
   add_property(PLAYER_OPTIONS_CONTROL_PROP, options);
}
int query_mxp_disable() {
   class player_options_control options;
   options = query_player_options();
   return options->mxp_disable;
}
int is_mxp_enabled() {
#if efun_defined(has_mxp)
   if (has_mxp(this_object())) {
      return !query_mxp_disable();
   }
#endif
   return 0;
}