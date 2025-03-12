#include "/include/virtual.h"
object compile_object(string path) {
   string* bits;
   if (file_size(path) > 0) {
      return (object)SERVER->create_virtual_object(path);
   }
   bits = explode(path, ":");
   if (sizeof(bits) > 1) {
      if (file_size(bits[0]) > 0 ||
          file_size(bits[0] + ".c") > 0) {
         return bits[0]->create_virtual_object(bits[1..] ...);
      }
   }
}