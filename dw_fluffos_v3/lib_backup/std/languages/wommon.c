string long() {
  return
"International womens day language.\n";
}
string filter_string(string str) {
  return replace(" "+str,
      ({ " he ", " they ",
         " He ", " They ",
         " HE ", " THEY ",
         " his ", " theirs ",
         " His ", " Theirs ",
         " HIs ", " THEIrs ",
         " HIS ", " THEIRS ",
         " him ", " them ",
         " Him ", " Them ",
         " HIm ", " THem ",
         " HIM ", " THEM ",
         "man", "person",
         "Man", "Person",
         "MAn", "PERson",
         "MAN", "PERSON", }))[1..10000];
}
mixed garble_tell(string start, string mess) {
  return ({ start, filter_string(mess) });
}
mixed garble_shout(string start, string mess) {
  return ({ start, filter_string(mess) });
}
mixed garble_say(string start, string mess) {
  return ({ start, filter_string(mess) });
}
mixed garble_text(string str, object ob) {
  return filter_string(str);
}