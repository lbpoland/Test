#include <parser.h>
inherit "/cmds/base";
mixed cmd(string str) {
  mixed res;
  PARSER->init_expr(str);
  res = PARSER->expr();
  printf("Returns: %O\n", ((pointerp(res) && sizeof(res) == 1)?res[0]:res));
  PARSER->finish_expr();
  return 1;
}