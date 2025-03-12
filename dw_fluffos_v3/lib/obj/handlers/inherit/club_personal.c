inherit "/obj/handlers/inherit/club_basic";
#define __CLUBS_H_NO_CLASSES
#include <clubs.h>
class personal_info {
}
protected void create_extra_data(string name) {
   class personal_info p_info;
   class club_info data;
   data = (class club_info)query_club_info(name);
   if (query_club_type(name) == CLUB_PERSONAL) {
         p_info = new(class personal_info);
      data->extra_data = p_info;
      set_club_changed(name);
   } else {
      ::create_extra_data(name);
   }
}
private class personal_info query_personal_info(string name) {
   class club_info data;
   if (is_personal_club(name)) {
      data = (class club_info)query_club_info(name);
      return data->extra_data;
   }
   return 0;
}