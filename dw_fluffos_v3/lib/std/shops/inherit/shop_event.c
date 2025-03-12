private nosave object* _events;
void create() {
   _events = ({ });
}
void add_shop_observer(object observer) {
   if (!_events) {
      _events = ({ });
   }
   if (member_array(observer, _events) == -1) {
      _events += ({ observer });
   }
}
void remove_shop_observer(object observer) {
   _events -= ({ observer });
}
int broadcast_shop_event(string type, object player, mixed args ...) {
   debug_printf("Calling %O on %O\n", "event_shop_" + type, _events);
   if (sizeof(filter(call_other(_events, "event_shop_" + type, this_object(),
                                player, args ...),
                    (: $1 :)))) {
      return 1;
   }
   return 0;
}