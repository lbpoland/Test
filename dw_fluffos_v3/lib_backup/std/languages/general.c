string long() {
  return
"This is the normal language spoken by most creatures.\n";
}
mixed garble_tell(string start, string mess) {
  return ({ start, mess });
}
mixed garble_shout(string start, string mess) {
  return ({ start, mess });
}
mixed garble_say(string start, string mess) {
  return ({ start, mess });
}
string garble_text( mixed text, object thing, object player, string skill) {
   string bing;
   if (stringp(text)) {
      return text;
   }
   if ( pointerp( text ) ) {
      if ( ( bing = (string)text[ 0 ]->garble_text( text, thing, player ) ) ) {
         return bing;
      }
   }
   return "You cannot read the furry writing.\n";
}