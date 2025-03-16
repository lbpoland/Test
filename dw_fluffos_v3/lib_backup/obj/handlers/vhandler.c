mapping stored_variables;
void create()
{
  seteuid(geteuid(this_object()));
  stored_variables=([ ]);
  restore_object(file_name(this_object()));
}
mixed query_variable_status(string vname)
{
  return stored_variables[vname];
}
int set_variable_status(string vname, mixed vvalue)
{
  stored_variables[vname]=vvalue;
  save_object(file_name(this_object()));
}