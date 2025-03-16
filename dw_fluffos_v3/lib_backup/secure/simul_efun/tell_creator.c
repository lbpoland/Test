varargs void tell_creator(mixed cre, string fmt, mixed args ...) {
  if (stringp(cre)) {
#if efun_defined(find_player)
    cre = efun::find_player(cre);
#else
    cre = "/obj/handlers/livings"->find_player(cre);
#endif
  }
  if (objectp(cre) && cre->query_creator()) {
    if (sizeof(args)) {
      tell_object(cre, sprintf(fmt, args ...));
    } else {
      tell_object(cre, fmt);
    }
  }
}