# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/std/basic/expressions.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def __init__(self):
            self._variables = ([ ])
            self._functions = ([ ])
            self._user_functions = ([ ])


    def __init__(self):
            self._variables = ([ ])
            self._functions = ([ ])
            self._user_functions = ([ ])
            _func_variables = ([ ])
            _error_string = "no error"
            add_allowed_function("sizeof", EXPRESSION_TYPE_INTEGER,
            [EXPRESSION_TYPE_ARRAY], (: sizeof_function :) )


    def query_last_expression_error(self, ) -> str:
            return _error_string


    def query_last_expression_warning(self, ) -> str:
            return _warning_string


    def add_allowed_variable(self, name: str, type: int, value: Any) -> None:
            class variable_thing bing
            bing = new(class variable_thing)
            bing->type = type
            bing->value = value
            _variables[name] = bing


    def add_allowed_function(self, name: str, type: int, args: Any, value: Any) -> None:
            class function_thing bing
            bing = new(class function_thing)
            bing->type = type
            bing->args = args
            bing->value = value
            _functions[name] = bing


    def query_function_variable_type(self, name: str) -> int:
            if (_func_variables[name]) {
            return ((class func_variable_thing)_func_variables[name])->type


    def query_function_variable_position(self, name: str) -> int:
            if (_func_variables[name]) {
            return ((class func_variable_thing)_func_variables[name])->arg_no


    def query_variable_type(self, name: str) -> int:
            if (_variables[name]) {
            return ((class variable_thing)_variables[name])->type


    def query_function_args_types(self, name: str) -> List[int]:
            if (_functions[name]) {
            return ((class function_thing)_functions[name])->args


    def query_function_type(self, name: str) -> int:
            if (_functions[name]) {
            return ((class function_thing)_functions[name])->type


    def query_user_function_return_type(self, name: str) -> int:
            if (_user_functions[name]) {
            return ((class user_function_thing)_user_functions[name])->type


    def remove_user_expression(self, name: str) -> int:
            if (_user_functions[name]) {
            map_delete(_user_functions, name)
            return 1


    def query_type_value(self, type: str) -> int:
            switch (lower_case(type)) {
            case "integer" :
            case "int"     :
            return EXPRESSION_TYPE_INTEGER
            case "string"  :
            return EXPRESSION_TYPE_STRING
            case "float"   :
            return EXPRESSION_TYPE_FLOAT
            case "boolean" :
            case "bool"    :
            return EXPRESSION_TYPE_BOOLEAN
            case "money" :
            return EXPRESSION_TYPE_MONEY
            case "object" :
            return EXPRESSION_TYPE_OBJECT
            case "array" :
            return EXPRESSION_TYPE_ARRAY
            default :
            return EXPRESSION_TYPE_ERROR


    def query_type_name(self, type: int) -> str:
            if (is_array_type(type)) {
            return "array " + query_type_name(type - EXPRESSION_TYPE_ARRAY_OFFSET)


    def query_operator_name(self, operator: int) -> str:
            switch (operator) {
            case EXPRESSION_AND_NEW   :
            case EXPRESSION_AND       :
            return "and"
            case EXPRESSION_OR_NEW    :
            case EXPRESSION_OR        :
            return "or"
            case EXPRESSION_NOT       :
            return "not"
            case EXPRESSION_FALSE     :
            return "false"
            case EXPRESSION_TRUE      :
            return "true"
            case EXPRESSION_GREATOR_THAN     :
            return ">"
            case EXPRESSION_LESS_THAN        :
            return "<"
            case EXPRESSION_EQUAL_TO         :
            return "="
            case EXPRESSION_NOT_EQUAL_TO         :
            return "<>"
            case EXPRESSION_GREATOR_OR_EQUAL :
            return ">="
            case EXPRESSION_LESS_OR_EQUAL    :
            return "<="
            case EXPRESSION_PLUS             :
            return "+"
            case EXPRESSION_MINUS            :
            return "-"
            case EXPRESSION_MULTIPLY         :
            return "*"
            case EXPRESSION_DIVIDE           :
            return "/"
            case EXPRESSION_IF               :
            return "if"
            default :
            return "unknown"


    def sizeof_function(self, arr: Any, args: Any) -> int:
            return sizeof(arr)


    def query_expression_string(self, parse_node: Any, brief: int) -> str:
            string str
            int i
            string* stack
            int* thing
            string tmp
            string place
            int value
            string indent
            if (!sizeof(expr)) {
            return "No expression set."


    def query_user_function_string(self, func: str) -> str:
            class user_function_thing thing
            int i
            string ret
            thing = _user_functions[func]
            ret = ""
            ret += query_type_name(thing->type) + " " + func + "("
            for (i = 0; i < sizeof(thing->arg_types); i++) {
            ret += query_type_name(thing->arg_types[i]) + " " + thing->arg_names[i]
            if (i < sizeof(thing->arg_types) - 1) {
            ret += ", "



class Expressions(MudObject):

    _variables = '([ ])'

    _functions = '([ ])'

    _user_functions = '([ ])'
