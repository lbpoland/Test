varargs string extract(string str, int start, int end) {
  if (end)
    return str[start..end];
  return str[start..];
}