private nosave mapping _respond_cmd;
class respond_data {
   object ob;
   mixed data;
}
void remove_respond_command(string type, object ob);
mapping query_respond_cmd_data() { return _respond_cmd; }
void create() {
   _respond_cmd = ([ ]);
}
void add_respond_command(string type, object ob, mixed data) {
   class respond_data frog;
   remove_respond_command(type, ob);
   frog = new (class respond_data);
   frog->ob = ob;
   frog->data = data;
   if (!_respond_cmd[type]) {
      _respond_cmd[type] = ({ });
   }
   _respond_cmd[type] += ({ frog });
}
mixed query_respond_command(string type, object ob) {
   class respond_data frog;
   if (_respond_cmd[type]) {
      foreach (frog in _respond_cmd[type]) {
         if (frog->ob == ob) {
            return frog->data;
         }
      }
   }
   return 0;
}
void remove_respond_command(string type, object ob) {
   class respond_data frog;
   int i;
   if (_respond_cmd[type]) {
      for (i = 0; i < sizeof(_respond_cmd[type]); i++) {
         frog = _respond_cmd[type][i];
         if (frog->ob == ob) {
            _respond_cmd[type] = _respond_cmd[type][0..i - 1] +
                                 _respond_cmd[type][i+1..];
            i--;
         }
      }
   }
}
void clear_respond_commands() {
   _respond_cmd = ([ ]);
}