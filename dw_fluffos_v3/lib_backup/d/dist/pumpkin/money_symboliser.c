string symbolise_value( int value ) {
   int dollars;
   int pence;
   string s;
   if (value < 0) {
      s = "-";
      value = - value;
   } else {
      s = "";
   }
   dollars = value / 100;
   pence = ( value % 100 );
   if ( !pence ) {
      return "P$"+ s + dollars;
   }
   if ( !dollars ) {
      return s + pence +"p";
   }
   if ( pence < 10 ) {
      return "P$"+ s + dollars +".0"+ pence;
   }
   return "P$" + s + dollars + "." + pence;
}
int unsymbolise_string( string str ) {
  int dollars;
  int pence;
  if (strlen(str) < 2) {
    return 0;
  }
  if (str[0] == '$' ||
      lower_case(str[0..1]) == "p$") {
     if (str[0] == 'p') {
       str = str[1..];
     }
     if (sscanf(str, "$%d.%d", dollars, pence) == 2) {
        return dollars * 100 + pence;
     } else if (sscanf(str, "$%d", dollars) == 1) {
        return dollars * 100;
     }
  } else if (lower_case(str[<1..<1]) == "p") {
     if (sscanf(str, "%dp", pence) == 1) {
       return pence;
     }
  }
  return 0;
}