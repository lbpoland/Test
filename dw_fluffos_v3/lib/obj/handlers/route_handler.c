int use_count;
varargs void get_route(string end, string start, function call_back, int count) {
  string *result;
  if(start == "/room/virtual"){
    call_out((: evaluate($(call_back), ({ })) :), 1);
    return;
  }
  if(!(stringp(start) && stringp(end)))
    error("illegal argument 1 or 2 to get_route");
  if(!function_owner(call_back))
    return;
  if ((end == start) || (count > 3)){
    call_out((: evaluate($(call_back), ({ })) :), 1);
    if(end != start)
      log_file("ROUTEHANDLER","route for %s from %s to %s failed\n",
               file_name(function_owner(call_back)), start, end);
    return;
  }
  result = "/obj/handlers/clusters"->get_route(start, end);
  if(!result){
    call_out((:get_route($(end), $(start), $(call_back), $(count + 1)):), 10);
    return;
  }
  use_count++;
  call_out((: evaluate($(call_back), $(result)) :), 1);
  return;
}
void dest_me() {
  destruct(this_object());
}
mixed *stats() {
  return  ({
    ({ "routes done", use_count }),
  });
}