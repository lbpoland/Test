void debug_printf(string fmt, mixed args ...) {
  object env;
  env = previous_object();
  if(env)
    while(environment(env))
      env = environment(env);
  if((!env || !env->query_is_room() || base_name(env) == "/room/rubbish") &&
     this_player()) {
    env = environment(this_player());
  }
  if(env) {
#if efun_defined(event)
    event(env, "inform", sprintf("%O:\n " + fmt, previous_object(), args ...),
          "debug");
#else
    this_object()->event(env, "inform", sprintf("%O:\n " + fmt,
                                                previous_object(), args ...),
                         "debug");
#endif
  }
}
varargs void tell_creator(mixed cres, string fmt, mixed args ...)  {
  mixed cre;
  if(!arrayp(cres))
    cres = ({ cres });
  foreach(cre in cres) {
    if (stringp(cre)) {
#if efun_defined(find_player)
      cre = efun::find_player(cre);
#else
      cre = "/obj/handlers/livings"->find_player(cre);
#endif
    }
    if (objectp(cre) && cre->query_creator()) {
      if (sizeof(args)) {
        tell_object(cre, sprintf("%O:\n" + fmt, previous_object(), args ...));
      } else {
        tell_object(cre, sprintf("%O:\n"+fmt, previous_object()));
      }
    }
  }
}