#include "virtual.h"
void add_method(string suffix, object ob, string fun, int type);
mapping methods;
#define OB   0
#define FUN  1
#define TYPE 2
#define LOAD   1
#define CLONE  2
void create() {
  seteuid(getuid());
  methods = ([ ]);
  add_method("C", "/global/virtual/c_compiler.c", "compile_c",
                        CLONE|LOAD);
}
object create_virtual_object(string name, int clone);
void add_method(string suffix, object ob, string fun, int type) {
  if (!type)
    type = CLONE;
  if (!methods[suffix]) {
    methods[suffix] = ({ ob, fun, type });
  }
}
#define Error(s) write(s); log_file("VO_HANDLER", s); return 0;
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
      ob->add_property("virtual name", name);
      return ob;
    }
    return 0;
  }
  Error("create_virtual_object() : unknown suffix to " + name + "\n");
}