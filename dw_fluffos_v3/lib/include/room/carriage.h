#ifndef __CARRIAGE_H__
#define __CARRIAGE_H__
class stop_details {
   string name;
   string path;
   int delay;
}
class stop_list_details {
   string id;
   int travel_time;
}
class route_details {
   string colour;
   int return_along;
   class stop_list_details* stops;
}
#define CARRIAGE_HANDLER_INHERIT "/std/room/inherit/carriage/handler"
#define CARRIAGE_CARRIAGE_INHERIT "/std/room/inherit/carriage/carriage"
#define CARRIAGE_CARRIAGE_POLE "/std/room/inherit/carriage/carriage_pole"
#endif