#include <living.h>
#include <config.h>
private class living_nationality _nationality_data;
string query_nationality() {
   if (_nationality_data && _nationality_data->nationality) {
      return _nationality_data->nationality;
   }
   return 0;
}
string query_nationality_region() {
   if (_nationality_data && _nationality_data->region) {
      return _nationality_data->region;
   }
   return 0;
}
mixed query_nationality_data() {
   if (_nationality_data && _nationality_data->data) {
      return _nationality_data->data;
   }
   return 0;
}
void set_nationality(string nationality) {
   if (!_nationality_data) {
      _nationality_data = new(class living_nationality);
   }
   _nationality_data->nationality = nationality;
}
void set_nationality_region(string region) {
   if (!_nationality_data) {
      _nationality_data = new(class living_nationality);
   }
   _nationality_data->region = region;
}
void set_nationality_data(mixed data) {
   if (!_nationality_data) {
      _nationality_data = new(class living_nationality);
   }
   _nationality_data->data = data;
}
string query_nationality_name() {
   if (_nationality_data && _nationality_data->nationality) {
      return _nationality_data->nationality->query_name();
   }
   return 0;
}
string query_nationality_description(object looker) {
   if (_nationality_data && _nationality_data->nationality) {
      return _nationality_data->nationality->query_look_description(this_object(), looker);
   }
   return 0;
}
string query_nationality_accent_ob() {
   if (_nationality_data && _nationality_data->nationality) {
      return _nationality_data->nationality->query_region_accent_ob(_nationality_data->region);
   }
}
string query_nationality_start_location() {
   if (_nationality_data && _nationality_data->nationality) {
      return _nationality_data->nationality->query_start_location(_nationality_data->region);
   }
   return CONFIG_START_LOCATION;
}