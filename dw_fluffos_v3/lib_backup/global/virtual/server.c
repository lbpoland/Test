#include "virtual.h"
void add_method(string suffix, mixed ob, string fun, int type);
mapping methods;
#define OB   0
#define FUN  1
#define TYPE 2
nosave mapping cache;
void create() {
  seteuid(getuid());
  methods = ([ ]);
  add_method("c", "/global/virtual/c_compiler.c", "compile_c",
                        CLONE|LOAD);
  add_method("C", "/global/virtual/c_compiler.c", "compile_c",
                        CLONE|LOAD);
  cache = ([ ]);
}
object create_virtual_object(string name, int clone);
void add_method(string suffix, mixed ob, string fun, int type) {
  if (!type)
    type = CLONE;
  if (!methods[suffix]) {
    methods[suffix] = ({ ob, fun, type });
  }
}
#define Error(s) write(s); log_file("VO_HANDLER", s); return 0;
string get_mod_time(string name) {
  if(cache[name])
    return cache[name];
  if(file_size(name) <= 0)
    cache[name] = "";
  else
    cache[name] = stat(name)[1];
  return cache[name];
}
object create_virtual_object(string name, int clone) {
  string *split;
  mixed  *method;
  object ob;
  split = explode(name, ".");
  method = methods[split[sizeof(split) - 1]];
  if (method) {
    if (clone ||
        (method[TYPE]&LOAD)) {
      ob =  (object) call_other(method[OB], method[FUN], name, clone);
      if (ob)  {
      ob->add_property(VIRTUAL_NAME_PROP, name);
        if (get_mod_time(name) != "")
          ob->add_property("virtual time", get_mod_time(name));
      }
      return ob;
    }
    return 0;
  }
  Error("create_virtual_object() : unknown suffix to " + name + "\n");
}
void reset() {
  cache = ([ ]);
}