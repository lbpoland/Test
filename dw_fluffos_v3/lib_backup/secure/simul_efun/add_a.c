string add_a(string s) {
  int i;
  if (!stringp(s))
    return 0;
  i = 0;
  while (s[i] == ' ') i++;
  if(s[i..i+1] == "a " || s[i..i+2] == "an ")
    return s;
  switch (s[i]) {
  case 'a':
  case 'e':
  case 'i':
  case 'o':
  case 'u':
  case 'A':
  case 'E':
  case 'I':
  case 'O':
  case 'U':
    return "an " + s[i..];
  default:
    return "a " + s[i..];
  }
}
int vowel(int i) {
  return (i == 'a' || i == 'e' || i == 'i' || i == 'o' || i == 'u' ||
          i == 'A' || i == 'E' || i == 'I' || i == 'O' || i == 'U');
}