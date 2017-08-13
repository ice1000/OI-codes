List<int> bits = [1, 2, 4, 8, 16, 32, 64, 128];

String boolfuck(String code, [String input = ""]) {
  int oc = 0, ic = 0, ii = 0, ina = input.length, tp = 0;
  int i = 0, o = 0;
  List<bool> tape = new List<bool>();
  tape.add(false);
  String output = "";
  for (int c = 0, e = code.length; c < e; ++c) {
    switch (code[c]) {
      case '<':
        if (--tp < 0) {
          tape.insert(0, false);
          tp = 0;
        }
        break;
      case '>':
        tape.add(++tp < 0);
        break;
      case '+':
        tape[tp] = !(tape[tp]);
        break;
      case '[':
        if (!(tape[tp])) {
          int b = 1;
          while (b != 0 && ++c < e) {
            if (code[c] == '[')
              ++b;
            else if (code[c] == ']') --b;
          }
        }
        break;
      case ']':
        if (tape[tp]) {
          int b = -1;
          while (b != 0 && --c >= 0)
            if (code[c] == '[')
              ++b;
            else if (code[c] == ']') --b;
        }
        break;
      case ',':
        if (--ic < 0) {
          i = ii < ina ? input[ii++].codeUnitAt(0) : 0;
          ic = 7;
        }
        tape[tp] = (i & 1) > 0;
        i >>= 1;
        break;
      case ';':
        if (tape[tp]) o |= bits[oc];
        if (++oc > 7) {
          output = "$output${new String.fromCharCode(o)}";
          o = 0;
          oc = 0;
        }
        break;
    }
  }
  if (oc > 0) output = "$output${new String.fromCharCode(o)}";
  return output.toString();
}
