class response {
    string  sender;
    string *triggers;
    string *responses;
    int     probability;
    int     delay;
}
inherit "/std/effect_shadow";
public          object  query_listener      ( );
public  varargs void    query_responses     ( string );
public  varargs void    add_respond_to_talker_with( string, string,
                                                        string *, int, int );
public          int     delete_response     ( string, string, string * );
public          void    receive             ( string, string, string,
                                                        object * );
public          void    process_response    ( string *, string * );
private varargs int     register_listener   ( object );
private         int     compare_arrays      ( mixed *, mixed *);
mapping responses = ([ ]);
object listener;
private varargs int register_listener(object target) {
  if(objectp(target)) {
    listener = target;
  }
  else
    listener = this_object()->arg_of(this_object()->
                                effects_matching("object.talker.response")[0]);
  if(!objectp(listener))
    this_object()->delete_effect(this_object()->
                                effects_matching("object.talker.response")[0]);
  return 1;
}
public object query_listener() {
  return listener;
}
public varargs void query_responses(string key) {
  if(stringp(key)) {
    class response *womble = responses[key];
    foreach(class response cabbage in womble) {
      printf("Channel: %s\n\tChatter: %s\n", key, cabbage->sender);
      printf("\tTrigger:\n");
      foreach(string trigger in cabbage->triggers)
        printf("\t\t\"%s\"\n",trigger);
      printf("\tResponse:\n");
      foreach(string resp in cabbage->responses)
        printf("\t\t\"%s\"\n", resp);
      printf("\tProbability:\t%d\n\tDelay:\t%d\n\n",
             cabbage->probability, cabbage->delay);
    }
    return;
  } else {
    foreach(string nextkey in keys(responses)) {
      query_responses(nextkey);
    }
    return;
  }
}
public varargs void add_respond_to_talker_with(string channel, string sender,
                                               string *trigger,
                                               string *response, int probability,
                                               int delay ) {
  class response new_item;
  if(!listener)
    register_listener();
  if (!channel || !sender || !trigger || !response ){
    listener->call_out("do_command", 3, "'Err. I haven't been setup "
                       "correctly in regards to my talker!");
    return;
  }
  channel = lower_case(channel);
  if (undefinedp(responses[channel]))
    responses[channel] = ({});
  else {
      foreach(class response item in responses[channel]) {
        if(item->sender == sender && item->triggers - trigger == ({}) &&
           item->responses - response == ({}) && item->probability == probability)
            return;
      }
  }
  if(!probability)
    probability = 10;
  if(!delay)
    delay = 1;
  if(delay == -1)
    delay = 0;
  if(probability > 100)
    probability = 100;
  new_item = new(class response, sender : sender, triggers : trigger,
                 responses : response, probability : probability, delay : delay);
  responses[channel] += ({ new_item });
  return;
}
public int delete_response( string channel, string sender, string *triggers ) {
  if( sizeof(responses[channel]) !=
      sizeof(responses[channel]   = responses[channel] -
             filter(filter(responses[channel], (: $1->sender == $(sender) :)),
                    (: compare_arrays( $1->triggers, $(triggers) ) :)) ) )
    return 1;
  return 0;
}
public void receive(string channel, string sender, string text,
                    object *receivers) {
  class response response;
  if(!listener) {
    register_listener();
    return;
  }
  if(sizeof(responses) && listener->query_name() != lower_case(sender) ) {
    if(member_array(lower_case(channel), keys(responses)) > -1 &&
       responses[channel]) {
      foreach( response in responses[channel]) {
        if(response->sender == sender ||
           response->sender == "anyone" ) {
          foreach( string trigger in response->triggers ) {
            if(regexp(text, trigger)) {
              if(random(100) < response->probability) {
                call_out("process_response", response->delay,
                         response->responses,
                         ({ channel, sender, text }));
              }
              break;
            }
          }
        }
      }
    }
  } else {
    query_shadowing(this_object())->receive(channel, sender, text, receivers);
  }
}
private int compare_arrays( mixed *ar1, mixed *ar2 ) {
  int i;
  if ( !ar1 && !ar2 )
    return 0;
  if ( sizeof( ar1 ) != sizeof( ar2 ) )
    return 1;
  i = sizeof( ar1 );
  while ( i-- ) {
    if ( ar1[ i ] != ar2[ i ] ) {
      return 1;
    }
  }
  return 0;
}
public void process_response( string *commands, string *arguments) {
  if(!query_listener()) return;
  foreach(string response in commands) {
    if(response[0] == '#') {
      if(function_exists(response[1..], listener)) {
        call_other( listener, ({ response[1..] }) + arguments);
      }
    } else {
      listener->do_command(response);
    }
  }
}