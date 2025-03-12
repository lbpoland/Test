inherit "/cmds/base";
mixed cmd(string str) {
  if (!interactive(this_player()))
    return "/cmds/living/ho_ld"->cmd(str);
  return notify_fail("Use hold; see help hold for more details.\n");
}