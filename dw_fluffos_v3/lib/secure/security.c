#include <security.h>
varargs nomask mixed call_unguarded(string func, mixed a1,
                                           mixed a2, mixed a3, mixed a4) {
  return call_other(previous_object(), func, a1, a2, a3, a4);
}