mixed *query_strange_inventory(mixed *arr) {
  mixed *inv, desc;
  object ob;
  int i;
  inv = ({ });
  foreach (ob in arr) {
    if (!(desc = (string)ob->short()) || (desc == ""))
      continue;
    if ((i = member_array(desc, inv)) >= 0)
      inv[i+1] += ({ ob });
    else
      inv += ({ desc, ({ ob }) });
  }
  return inv;
}