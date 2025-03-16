private nosave object _repeater;
void set_repeater_owner(object owner) {
   _repeater = owner;
}
object query_repeater_owner() {
   return _repeater;
}
void repeat_event_person_say(object caller,
                             object ob,
                             string start,
                             string mess,
                             string lang) {
}
void event_person_say(object ob, string start, string mess, string lang) {
   if (_repeater) {
      _repeater->repeat_event_person_say(this_object(),
                                         ob,
                                         start,
                                         mess,
                                         lang);
   }
}
void repeat_event_emote(object caller,
                        object ob,
                        string mess) {
}
void event_emote( object ob, string mess ) {
   if (_repeater) {
   _repeater->repeat_event_emote(this_object(),
                                 ob,
                                 mess);
   }
}
void repeat_event_say(object caller,
                      object ob,
                      string mess,
                      object *avoid) {
}
void event_say(object ob, string str, mixed avoid) {
   if (_repeater) {
      _repeater->repeat_event_say(this_object(),
                                  ob,
                                  str,
                                  avoid);
   }
}
void repeat_event_soul(object caller,
                       object ob,
                       string mess,
                       object *avoid) {
}
void event_soul(object ob, string str, mixed avoid) {
   if (_repeater) {
      _repeater->repeat_event_soul(this_object(),
                                  ob,
                                  str,
                                  avoid);
   }
}
void repeat_event_enter(object caller,
                        object ob,
                        string mess,
                        object prev) {
}
void event_enter( object thing,
                  string mess,
                  object prev ) {
   if (_repeater) {
      _repeater->repeat_event_enter(this_object(),
                                    thing,
                                    mess,
                                    prev);
   }
}
void repeat_event_exit(object caller,
                       object ob,
                       string mess,
                       object dest) {
}
void event_exit( object thing,
                 string mess,
                 object dest ) {
   if (_repeater) {
      _repeater->repeat_event_enter(this_object(),
                                    thing,
                                    mess,
                                    dest);
   }
}