#ifndef ___OBJ_PARSER_H
#define ___OBJ_PARSER_H
#ifndef OBJ_PARSER_NO_CLASSES
class obj_match
{
   int result;
   object *objects;
   string text;
}
class obj_match_context
{
   int ordinal;
   int number_included;
   int* fraction;
   int ignore_rest;
   int no_ambiguous;
   object him;
   object her;
   object it;
   object* plural;
}
#endif
#define OBJ_PARSER_SUCCESS         100
#define OBJ_PARSER_NO_MATCH        315
#define OBJ_PARSER_TOO_DARK        316
#define OBJ_PARSER_FRACTION        317
#define OBJ_PARSER_BAD_FRACTION    318
#define OBJ_PARSER_BAD_ENVIRONMENT 319
#define OBJ_PARSER_NOT_LIVING      320
#define OBJ_PARSER_AMBIGUOUS       322
#define OBJ_PARSER_NOT_ENOUGH      323
#define OBJ_PARSER_MATCH_SINGULAR 4
#define OBJ_PARSER_MATCH_PLURAL   16
#define OBJ_PARSER_TYPE_EXISTENCE 1
#define OBJ_PARSER_TYPE_PLAYER    2
#define OBJ_PARSER_TYPE_SLOPPY_MATCHING 4
#define OBJ_PARSER_TYPE_NO_NESTED 8
#define OBJ_PARSER_TYPE_LIVING 16
#define OBJ_PARSER_TYPE_OBJECT 0
#define OBJ_PARSER_MATCH_TYPE     0
#define OBJ_PARSER_OBJECTS        1
#define OBJ_PARSER_AMBIGUOUS_PROP "no ambiguous"
#define OBJ_PARSER_USE_AND_AS_BREAK_PROP "use and"
#endif