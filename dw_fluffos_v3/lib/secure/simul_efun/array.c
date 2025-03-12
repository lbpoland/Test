mixed delete(mixed arr, int start, int len) {
  return arr[0..start-1] + arr[start+len..];
}
mixed insert(mixed arr, mixed el, int pos) {
  if (stringp(arr))
    return arr[0..pos-1] + el + arr[pos..];
  return arr[0..pos-1] + ({ el }) + arr[pos..];
}
object *all_environment(object ob){
  object *ret = ({});
  if(!ob)
    ob = previous_object();
  while(environment(ob)){
    ob = environment(ob);
    ret += ({ob});
  }
  return ret;
}