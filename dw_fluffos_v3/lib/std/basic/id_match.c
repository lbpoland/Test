#include <obj_parser.h>
private int _no_all;
protected void set_no_all(int no_all) {
   _no_all = no_all;
}
int query_no_all() {
   return _no_all;
}
protected int is_matching_object(string* input,
                          object viewer,
                          class obj_match_context context )
{
   string *adj;
   string *padj;
   string *names;
   string *pnames;
   int n;
   int ret;
   if( this_object() == context->him &&
       input[<1] == "him" ) {
      ret |= OBJ_PARSER_MATCH_SINGULAR;
   } else if( this_object() == context->her &&
              input[<1] == "her" ) {
      ret |= OBJ_PARSER_MATCH_SINGULAR;
   } else if( this_object() == context->it &&
              input[<1] == "it" ) {
      ret |= OBJ_PARSER_MATCH_SINGULAR;
   } else if( context->plural &&
              input[<1] == "them" &&
              member_array( this_object(), context->plural ) != -1 ) {
      ret |= OBJ_PARSER_MATCH_PLURAL;
   } else if( this_object() == viewer &&
              input[<1] == "me" ) {
      ret |= OBJ_PARSER_MATCH_SINGULAR;
   } else if (!_no_all && input[<1] == "all") {
      ret |= OBJ_PARSER_MATCH_PLURAL;
   } else if (!_no_all && (input[<1] == "things" || input[<1] == "ones")) {
      ret |= OBJ_PARSER_MATCH_PLURAL;
   } else if (!_no_all && (input[<1] == "thing" || input[<1] == "one")) {
      ret |= OBJ_PARSER_MATCH_SINGULAR;
   }
   if (!ret) {
      if (input[<1] == "here" &&
          viewer != environment() &&
          sizeof(input) > 1) {
         input = input[0..<2];
      }
      names = this_object()->parse_command_id_list();
      pnames = this_object()->parse_command_plural_id_list();
      if( member_array( input[<1], pnames ) != -1 ) {
         ret |= OBJ_PARSER_MATCH_PLURAL;
      }
      if( member_array( input[<1], names ) != -1 ) {
         ret |= OBJ_PARSER_MATCH_SINGULAR;
      }
      if (!ret) {
         return 0;
      }
   }
   adj = this_object()->parse_command_adjectiv_id_list();
   padj = this_object()->parse_command_plural_adjectiv_id_list();
   if( environment() == context->him ) {
      adj += ({ "his" });
   } else if( environment() == context->her ) {
      adj += ({ "her" });
   } else if( environment() == context->it ) {
      adj += ({ "its" });
   } else if( environment() == viewer ) {
      adj += ({ "my" });
   } else if( context->plural &&
                   member_array( environment(), context->plural ) != -1 ) {
      adj += ({ "their" });
   }
   for( n = 0; n < sizeof( input ) - 1; n++ )
   {
      if( member_array( input[n], adj ) == -1 ) {
         if (!padj || member_array(input[n], padj) == -1) {
            return 0;
         } else {
            ret &= ~OBJ_PARSER_MATCH_SINGULAR;
            ret |= OBJ_PARSER_MATCH_PLURAL;
         }
      }
   }
   return ret;
}
protected int update_parse_match_context(class obj_match_context context,
                                         int num,
                                         int singular) {
   if (context->ordinal) {
      if (context->ordinal == -1) {
         return 1;
      }
      if (context->ordinal > num) {
         context->ordinal -= num;
         return 0;
      }
      context->ignore_rest = 1;
      return 1;
   } else if (context->number_included) {
      if (context->number_included <= num) {
         context->ignore_rest = 1;
         num = context->number_included;
         context->number_included = 0;
         return num;
      }
      context->number_included -= num;
      return num;
   } else {
      if (num > 0 && (singular & OBJ_PARSER_MATCH_SINGULAR)) {
         return 1;
      }
      return num;
   }
}
mixed parse_match_object( string* input,
                          object viewer,
                          class obj_match_context context )
{
   int ret;
   ret = is_matching_object(input, viewer, context);
   if (!ret) {
      return 0;
   }
   if (!update_parse_match_context(context, 1, ret)) {
      return 0;
   }
   return ({ ret, ({ this_object() }) });
}