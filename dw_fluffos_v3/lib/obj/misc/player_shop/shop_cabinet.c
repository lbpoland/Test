#include <move_failures.h>
inherit "/std/container";
private mapping _stock = ([]);
private nosave string _save_file = "";
private nosave int _call_save = 0;
private void do_save();
void create()
{
   do_setup++;
   ::create();
   do_setup--;
   if (!do_setup)
   {
      this_object()->setup();
      this_object()->reset();
   }
}
object *add_items(object *items, object player)
{
   object *failed = ({});
   foreach( object item in items )
   {
      if (item->move(this_object()) != MOVE_OK)
      {
         failed += ({ item });
      }
   }
   if (sizeof(failed))
   {
      failed->move(player);
   }
   remove_call_out(_call_save);
   _call_save = call_out((: do_save() :), 1);
   return failed;
}
void dest_me()
{
   if (remove_call_out(_call_save) != -1)
   {
      do_save();
   }
   ::dest_me();
}
private void do_load()
{
   if (_save_file)
   {
      if (file_size(_save_file + ".o") > 0)
      {
         unguarded((: restore_object, _save_file :));
         if (sizeof(_stock))
         {
            init_dynamic_arg(_stock,0);
         }
      }
   }
}
private void do_save()
{
   if (_save_file && _save_file != "")
   {
#ifdef DEBUG
      debug_printf("Saving cabinet data to %s.\n", _save_file);
#endif
      _stock = query_dynamic_auto_load();
      unguarded((: save_object, _save_file :));
   }
}
object *remove_items(object *items, object player)
{
   object *failed = ({});
   foreach(object item in items)
   {
      if (item->move(player) != MOVE_OK)
      {
         failed += ({ item });
      }
   }
   if (sizeof(failed))
   {
      failed->move(environment(player));
   }
   remove_call_out(_call_save);
     _call_save = call_out((: do_save() :), 1);
   return failed;
}
void set_save_file(string filename)
{
   _save_file = filename;
   do_load();
}