#define NATIONAL_ACCENT_PATH "/std/nationality/accents/national/"
mapping accent_lang_map = ([
   "Pumpkin" : "pumpkin",
   ]);
string query_nat_accent( string lang ) {
   return NATIONAL_ACCENT_PATH + lang;
}
string national_garble( string mess, object person, object sayer, int say_type,
                        string def_lang, string accent ) {
   string accent_lang = accent_lang_map[ accent ];
   string nat_accent = query_nat_accent( accent_lang );
   if( def_lang != accent_lang ) {
      if( nat_accent )
         mess = load_object( query_nat_accent( accent_lang ) )->garble_say( mess,
                                                                            person,
                                                                            sayer,
                                                                            say_type );
   } else {
   }
   return mess;
}