int valid_compile_to_c() {
  if (previous_object() == this_object())
    return 1;
  if (previous_object() != find_object("/secure/cmds/creator/compile"))
    return 0;
  if (!interactive(previous_object(1)))
    return 0;
  if (!this_object()->query_lord(previous_object(-1)))
    return 0;
  return 1;
}