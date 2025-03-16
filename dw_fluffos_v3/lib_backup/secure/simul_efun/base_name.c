string base_name(mixed val) {
  string name, base;
  if(!val)
    return "";
  if (stringp(val))
    name = val;
  else
    name = file_name(val);
  if (sscanf(name, "%s#%*d", base) == 2)
    return base;
  return name;
}