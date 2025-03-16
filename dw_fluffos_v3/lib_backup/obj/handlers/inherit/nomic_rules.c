#include <nomic_system.h>
private mapping _rules;
void save_me();
int query_can_change_rule(string area, class nomic_rule rule);
class nomic_rule find_nomic_rule(string area, string creator, string text);
void create() {
   _rules = ([ ]);
}
int add_nomic_rule(string area, int type, string creator, string text) {
   int bing;
   class nomic_rule nomic_rule;
   if (!_rules[area]) {
      return NOMIC_ERROR;
   }
   if (type < 0 || type >= sizeof(_rules[area]->new_type_num)) {
      return NOMIC_ERROR;
   }
   if (find_nomic_rule(area, creator, text)) {
      return NOMIC_ERROR;
   }
   nomic_rule = new(class nomic_rule);
   bing = _rules[area]->new_type_num[type];
   nomic_rule->id = bing;
   nomic_rule->creator = creator;
   nomic_rule->type = type;
   nomic_rule->text = text;
   nomic_rule->date_created = time();
   nomic_rule->amendments = ({ });
   _rules[area]->rules += ({ nomic_rule });
   _rules[area]->new_type_num[type] = bing + 1;
   save_me();
   return bing;
}
protected int add_nomic_rule_class(string area,
                                   class nomic_rule new_rule,
                                   int type) {
   int bing;
   if (!_rules[area]) {
      return NOMIC_ERROR;
   }
   if (type < 0 || type >= sizeof(_rules[area]->new_type_num)) {
      return NOMIC_ERROR;
   }
   if (find_nomic_rule(area, new_rule->creator, new_rule->text)) {
      return NOMIC_ERROR;
   }
   bing = _rules[area]->new_type_num[type];
   new_rule->id = bing;
   new_rule->type = type;
   _rules[area]->rules += ({ new_rule });
   _rules[area]->new_type_num[type] = bing + 1;
   save_me();
   return bing;
}
protected int move_nomic_rule(string area, class nomic_rule rule,
                              int type) {
   int bing;
   int i;
   if (!_rules[area]) {
      return NOMIC_ERROR;
   }
   if (type < 0 || type >= sizeof(_rules[area]->new_type_num)) {
      return NOMIC_ERROR;
   }
   bing = _rules[area]->new_type_num[type];
   for (i = 0; i < sizeof(_rules[area]->rules); i++) {
      if (_rules[area]->rules[i]->id == rule->id) {
         if (!query_can_change_rule(area, _rules[area]->rules[i])) {
            return NOMIC_ERROR;
         }
         _rules[area]->rules[i]->id = bing;
         ((class nomic_rule)_rules[area]->rules[i])->type = type;
         _rules[area]->new_type_num[type] = bing + 1;
         save_me();
         return bing;
      }
   }
   return NOMIC_ERROR;
}
int change_nomic_rule(string area, class nomic_rule rule) {
   int i;
   if (!_rules[area]) {
      return 0;
   }
   for (i = 0; i < sizeof(_rules[area]->rules); i++) {
      if (_rules[area]->rules[i]->id == rule->id) {
         if (!query_can_change_rule(area, _rules[area]->rules[i])) {
            return NOMIC_ERROR;
         }
         rule->type = ((class nomic_rule)_rules[area]->rules[i])->type;
         rule->id = ((class nomic_rule)_rules[area]->rules[i])->id;
         _rules[area]->rules[i] = rule;
         save_me();
         return 1;
      }
   }
   return 0;
}
int remove_nomic_rule(string area, int id) {
   class nomic_rule nomic_rule;
   if (!_rules[area]) {
      return NOMIC_ERROR;
   }
   foreach (nomic_rule in _rules[area]->rules) {
      if (nomic_rule->id == id) {
         if (!query_can_change_rule(area, nomic_rule)) {
            return NOMIC_ERROR;
         }
         _rules[area]->rules -= ({ nomic_rule });
         save_me();
         return 1;
      }
   }
   return 0;
}
int int_remove_nomic_rule(string area, int id) {
   class nomic_rule nomic_rule;
   if (!_rules[area]) {
      return NOMIC_ERROR;
   }
   foreach (nomic_rule in _rules[area]->rules) {
      if (nomic_rule->id == id) {
         _rules[area]->rules -= ({ nomic_rule });
         save_me();
         return 1;
      }
   }
   return 0;
}
class nomic_rule query_nomic_rule(string area, int id) {
   class nomic_rule nomic_rule;
   if (!_rules[area]) {
      return 0;
   }
   foreach (nomic_rule in _rules[area]->rules) {
      if (nomic_rule->id == id) {
         return copy(nomic_rule);
      }
   }
   return 0;
}
class nomic_rule* query_all_nomic_rules(string area) {
   if (!_rules[area]) {
      return ({ });
   }
   return copy(_rules[area]->rules);
}
class nomic_rule find_nomic_rule(string area, string creator, string text) {
   class nomic_rule rule;
   if (!_rules[area]) {
      return 0;
   }
   foreach (rule in _rules[area]->rules) {
      if (rule->creator == creator && rule->text == text) {
         return rule;
      }
   }
   return 0;
}
int create_area(string area) {
   class nomic_area new_area;
   if (_rules[area]) {
       return 0;
   }
   new_area = new(class nomic_area);
   new_area->new_type_num = NOMIC_DEFAULT_TYPE_NUMS;
   new_area->rules = ({ });
   _rules[area] = new_area;
   return 1;
}
int query_type_number(string name) {
   switch (lower_case(name)) {
   case "immutable" :
      return NOMIC_TYPE_IMMUTABLE;
   case "general" :
      return NOMIC_TYPE_GENERAL;
   case "citizen" :
      return NOMIC_TYPE_CITIZEN;
   default :
      return NOMIC_ERROR;
   }
}
string query_type_name(int type_no) {
   switch (type_no) {
   case NOMIC_TYPE_IMMUTABLE :
      return "immutable";
   case NOMIC_TYPE_GENERAL :
      return "general";
   case NOMIC_TYPE_CITIZEN :
      return "citizen";
   default :
      return "error";
   }
}
int query_can_change_rule(string area, class nomic_rule rule) {
   return rule->type != NOMIC_TYPE_IMMUTABLE;
}
string rule_as_string(int indent, class nomic_rule rule) {
   string ret;
   class nomic_amendment amend;
   ret = "$I$" + (indent + 5) + "=" + sprintf("%*s", indent, "") +
          (rule->id?rule->id+"":"(" +
          NOMIC_HANDLER->query_type_name(rule->type) + ")") + " by " +
          capitalize(rule->creator) + " (" +
          ctime(rule->date_created) + "):\n" + rule->text +
          "\n";
   foreach (amend in rule->amendments) {
      ret += "$I$" + (indent + 10) + "=" + sprintf("%*s", indent + 3, "") +
             capitalize(amend->amender) + " (" +
             ctime(amend->date_amended) + "):\n" +
             amend->text + "\n";
   }
   return ret;
}