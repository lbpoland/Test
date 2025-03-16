string *replace_matrix;
void create() {
  replace_matrix =  ({
"the", "zee",
"The", "Zee",
"ir", "ur",
"ow", "oo",
"th", "t",
"au", "oo",
"Au", "Oo",
"u", "oo",
"U", "Oo",
"tion", "shun",
"an", "un",
"An", "Un",
"en ", "ee ",
"ew", "oo",
"a", "e*",
"A", "E*",
"e* ", "e ",
"E* ", "E ",
"e*", "e",
"E*", "E",
"e ", "e-a ",
"f", "ff",
" o", " oo",
" O", " Oo",
"v", "f",
"V", "F",
"w", "v",
"W", "V", });
}
string do_transmute(string str) {
  return replace(" "+str, replace_matrix)[1..10000];
}