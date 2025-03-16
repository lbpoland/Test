inherit "/std/basic/setup";
class region {
   string description;
   string start_location;
   string accent_ob;
}
private string _name;
private string _information;
private string _same_nat_description;
private string _different_nat_description;
private string _start_loc;
private string _language;
private string _accent;
private string _currency;
private mapping _regions;
void create() {
   _regions = ([ ]);
   do_setup();
}
void add_region(string name, string description, string start, string accent) {
   class region bing;
   bing = new(class region,
              description : description,
              start_location : start,
              accent_ob : accent);
   _regions[name] = bing;
}
void set_name(string name) {
   _name = name;
}
string query_name() {
   return _name;
}
void set_same_nationality_description(string description) {
   _same_nat_description = description;
}
string query_same_nationality_description() {
   return _same_nat_description;
}
void set_different_nationality_description(string description) {
   _different_nat_description = description;
}
string query_different_nationality_description() {
   return _different_nat_description;
}
string query_look_description(object person, object looker) {
   return "";
   if (person->query_nationality() == looker->query_nationality()) {
      return capitalize(person->query_pronoun()) + " " +
             _same_nat_description;
   } else {
      return capitalize(person->query_pronoun()) + " " +
             _different_nat_description;
   }
}
void set_default_start_location(string start_loc) {
   _start_loc = start_loc;
}
string query_default_start_location() {
   return _start_loc;
}
void set_language(string language) {
   _language = language;
}
string query_language() {
   return _language;
}
void set_information(string info) {
   _information = info;
}
string query_information() {
	if (!_information) {
      _information = "The $C$" + query_name() + " nationality is yet to "
                     "be described.\n";
   }
   return _information;
}
string* query_regions() {
   return keys(_regions);
}
string query_region_description(string region) {
   return _regions[region]->description;
}
string query_region_start_location(string region) {
   return _regions[region]->start_location;
}
string query_start_location(string region) {
   if (_regions[region] && _regions[region]->start_location) {
      return _regions[region]->start_location;
   }
   return _start_loc;
}
string query_region_accent_ob(string region) {
   if (_regions[region]) {
      return _regions[region]->accent_ob;
   }
   return 0;
}
void set_currency_area(string area) {
   _currency = area;
}
string query_currency_area() {
   return _currency;
}