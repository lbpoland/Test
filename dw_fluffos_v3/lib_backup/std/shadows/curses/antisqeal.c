inherit "/std/effect_shadow";
string *replace_matrix =  ({
"kewl", "cool",
"l33t", "elite",
" ur ", "your",
" r ", " are ",
" u ", " you ",
" y ", " why ",
"2", "two",
"4", "for",
"sum", "some",
"wut", "what",
"z", "s",
"Z", "s",
"k", "c",
"K", "c",
"wif", "with",
"werk", "work" });
#ifdef 0
string mangle_speech( string s ) {
    string s1;
    s1 = player->mangle_speech( s ); return replace( " " + (stringp(s1)?s1:s),
    replace_matrix)[1..10000]; }
#endif
string mangle_chat( string s ) {
  return replace(s, replace_matrix);
}