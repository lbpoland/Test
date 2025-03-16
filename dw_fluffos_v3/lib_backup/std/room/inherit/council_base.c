#define NOMIC_SYSTEM_NO_CLASSES
#include <nomic_system.h>
private nosave string _council_area;
string query_council_area() {
   return _council_area;
}
void set_council_area(string area) {
   _council_area = area;
}
void send_council_inform(int magistrate_only, string message) {
   NOMIC_HANDLER->send_council_inform(query_council_area(),
                                       magistrate_only, message);
}