private nosave function _open_func;
void set_open_function(function func) {
   _open_func = func;
}
function query_open_function() {
   return _open_func;
}
int is_open(object player, int type) {
   if (_open_func) {
      return evaluate(_open_func, player, type);
   }
   return 1;
}
int test_open() {
    return is_open( this_player(), 0 );
}