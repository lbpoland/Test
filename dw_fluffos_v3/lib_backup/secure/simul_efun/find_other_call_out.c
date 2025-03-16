mixed find_other_call_out(object ob, string co){
  return evaluate(bind((: find_call_out($(co)) :), ob));
}