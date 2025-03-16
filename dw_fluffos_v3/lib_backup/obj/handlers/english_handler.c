float *freq=({ 0.070012, 15.782218, 0.011949, 43.328090, 0.021800, 31.780955,
                 0.041222, 22.534301, 0.081093, 11.110506, 0.016799, 34.952377,
                 0.019235, 35.094824, 0.031751, 21.939816, 0.055348, 15.959625,
                 0.001028, 116.456628, 0.007624, 57.669862, 0.029144,
                 22.558570, 0.028764, 31.148966, 0.047194, 18.490345, 0.054178,
                 15.319177, 0.014415, 36.228697, 0.001335, 116.456628,
                 0.047561, 18.817823, 0.050139, 17.975454, 0.058789, 13.617099,
                 0.020638, 32.978418, 0.005222, 63.346619, 0.011713, 42.180909,
                 0.001264, 116.456628, 0.014661, 40.185678, 0.000530,
                 116.456628, 0.171614, 40.0, 0.000666, 116.456628,
                 0.084311, 10.304674
});
int FreqTest( string line ) {
  int len,i,ch;
  float badness,term;
  int *let;
  let=allocate(29);
  i = len = strlen(line);
  while (i--) {
    ch = line[i];
    if ((ch>=65 && ch<65+26) || (ch>=97 && ch<97+26)) let[(ch&31)-1]++;
    else if (ch==' ') let[26]++;
    else if (ch>='0' && ch<='9') let[27]++;
    else let[28]++;
  }
  badness = 0.0;
  for (i=0;i<29;i++) {
    term = to_float((to_float(let[i]) - freq[i<<1] * len) * freq[(i<<1)+1]);
    badness += (term>0 ? term : -term);
  }
  badness /= (29.0*len);
  i = 100 - 50*badness*badness;
  if (i<1) i=1;
  return i;
}
int ProfaneTest( string strin ) {
  int i,profane=0;
  string str,s;
  if (sizeof(strin)<1) return 0;
  strin=lower_case(strin)+" ";
  str="";
  for (i=0;i<sizeof(strin);i++) {
    if (strin[i]>='a' && strin[i]<='z') str+=strin[i..i];
  }
  if (sizeof(str)<2) return 0;
  s=str[0..0];
  for (i=1;i<sizeof(str);i++) {
    if (s[<1]!=str[i]) s+=str[i..i];
  }
  if (regexp(s,"bastard|tit|shaft|viag")
     || regexp(str,"poo|ass|butt")) profane+=25;
  if (regexp(s,"arse|sex|sux|crap|testic|fart|orgasm|orgy|turd|porn|niple|nazi|jesus|christ|satan|sperm|smeg|toilet|genital")
     || regexp(str,"piss|root|buttw|assho")
     || regexp(strin,"butt |ass ")) profane+=50;
  if (regexp(s,"netsex|arse|shit|screw|urine|rectum|tampon|vibrator|rectal|scatol|semen|suck|lick|dyke|dike|wank|mutha|prost|fag|feck|gay|homo|fuq|horny|blowjob|cuni")
     || regexp(str,"phall|hooter|poof")) profane+=100;
  if (regexp(s,"anal|rape|rapist|fuck|fuk|fuch|kuck|cunt|kunt|whor|slut|clit|masturb|masterb|penis|cock|dick|pusy|bitch|vagina")) profane+=200;
  return profane;
}