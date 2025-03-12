varargs string mxp_tag(string tag, string output, mixed player) {
#if efun_defined(has_mxp)
   if (!player) {
      player = this_player();
   }
   if (player == 1 || player->is_mxp_enabled()) {
      return "MXP<" + tag + "MXP>" + output + "MXP</" + tag + "MXP>";
   }
#endif
   return output;
}
varargs string mxp_tag_args(string tag, string args, string output, mixed player) {
#if efun_defined(has_mxp)
   if (!player) {
      player = this_player();
   }
   if (player == 1 || player->is_mxp_enabled()) {
      return "MXP<" + tag + " " + args + "MXP>" + output + "MXP</" + tag + "MXP>";
   }
#endif
   return output;
}
varargs string mxp_choice(string non_mxp, string mxp, mixed player) {
#if efun_defined(has_mxp)
   if (!player) {
      player = this_player();
   }
   if (player == 1 || player->is_mxp_enabled()) {
      return mxp;
   }
#endif
   return non_mxp;
}
varargs string mxp_secure(object player) {
#if efun_defined(has_mxp)
   if (!player) {
      player = this_player();
   }
   if (player->is_mxp_enabled()) {
      return sprintf("%c[6z", 27);
   }
#endif
   return "";
}
varargs string mxp_open(object player) {
#if efun_defined(has_mxp)
   if (!player) {
      player = this_player();
   }
   if (player->is_mxp_enabled()) {
      return sprintf("%c[5z", 27);
   }
#endif
   return "";
}
varargs string mxp_next_secure(object player) {
#if efun_defined(has_mxp)
   if (!player) {
      player = this_player();
   }
   if (player->is_mxp_enabled()) {
      return sprintf("%c[4z", 27);
   }
#endif
   return "";
}
varargs string mxp_expire(string category, object player) {
#if efun_defined(has_mxp)
   if (!player) {
      player = this_player();
   }
   if (player->is_mxp_enabled()) {
      return "MXP<EXPIRE " + category + "MXP>";
   }
#endif
   return "";
}