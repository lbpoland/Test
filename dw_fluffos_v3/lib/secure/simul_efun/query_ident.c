string query_ident(object ob) {
  switch (explode(file_name(previous_object()), "/")[0]) {
    case "secure" :
    case "obj" :
      return (string)ob->query_my_ident();
  }
  return 0;
}