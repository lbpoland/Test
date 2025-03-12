#include "virtual.h"
object garbage_handler;
object clone_object(string str, mixed *args ...) {
  object ob;
  if (sizeof(args) == 0)
    ob = efun::clone_object(str);
  else
    ob = efun::clone_object(str, args ...);
  if (!ob && file_size(str) > 0) {
    ob = SERVER->create_virtual_object(str, 1);
  }
  if (ob)  {
    if(!garbage_handler)
      catch(garbage_handler = load_object("/obj/handlers/garbage"));
    if(garbage_handler)
      catch(garbage_handler->cloned(ob));
  }
  return ob;
}