#include <expressions.h>
#include <player_handler.h>
#include <clubs.h>
#include <nomic_system.h>
void add_allowed_function(string name, int type, int* args, function value);
void add_allowed_variable(string name, int type, function value);
private int variable_player_level(string seller) {
   return PLAYER_HANDLER->test_level(seller);
}
private string variable_player_guild(string seller) {
   string guild;
   guild = PLAYER_HANDLER->test_guild(seller);
   if (guild) {
      return guild->query_name();
   }
   return "";
}
private string variable_player_order(string seller) {
   string guild;
   guild = PLAYER_HANDLER->test_guild(seller);
   if (guild) {
      guild = guild->query_wizard_order();
      if (guild) {
         return replace_string(lower_case(guild), "_", " ");
      }
   }
   return "";
}
private string variable_player_name(string seller) {
   return lower_case(seller);
}
private string variable_player_deity(string seller) {
   string deity;
   deity = PLAYER_HANDLER->test_deity(seller);
   if (deity) {
      return deity;
   }
   return "";
}
private string variable_player_family(string seller) {
   string family;
   family = PLAYER_HANDLER->test_family(seller);
   if (family) {
      return family;
   }
   return "";
}
private int function_club_member(string club, string seller) {
   return CLUB_HANDLER->is_member_of(club, seller);
}
private int function_citizen_of(string region, string seller) {
   return NOMIC_HANDLER->is_citizen_of(region, seller);
}
void create() {
   if (!function_exists("add_allowed_variable", this_object())) {
      return ;
   }
   add_allowed_variable("level", EXPRESSION_TYPE_INTEGER,
                        (: variable_player_level :) );
   add_allowed_variable("guild", EXPRESSION_TYPE_STRING,
                        (: variable_player_guild :) );
   add_allowed_variable("deity", EXPRESSION_TYPE_STRING,
                        (: variable_player_deity :) );
   add_allowed_variable("family", EXPRESSION_TYPE_STRING,
                        (: variable_player_family :) );
   add_allowed_variable("order", EXPRESSION_TYPE_STRING,
                        (: variable_player_order :) );
   add_allowed_variable("playername", EXPRESSION_TYPE_STRING,
                        (: variable_player_name :) );
   add_allowed_function("clubmember", EXPRESSION_TYPE_BOOLEAN,
                        ({ EXPRESSION_TYPE_STRING }),
                        (: function_club_member :) );
   add_allowed_function("citizenof", EXPRESSION_TYPE_BOOLEAN,
                        ({ EXPRESSION_TYPE_STRING }),
                        (: function_club_member :) );
}