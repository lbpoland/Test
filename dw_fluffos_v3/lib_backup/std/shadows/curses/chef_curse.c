inherit "/std/effect_shadow";
string *replace_matrix =  ({
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
string mangle_speech( string s ) {
    string s1;
    s1 = player->mangle_speech( s );
    return replace( " " + (stringp(s1)?s1:s), replace_matrix)[1..10000];
}