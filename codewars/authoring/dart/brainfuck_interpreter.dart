dynamic getOrElse(List<dynamic> l, int index, dynamic d) =>
    index >= l.length ? d : l[index];

String getOrElse2(String l, int index, String d) =>
    index >= l.length ? d : l[index];

String brainLuck(String code, String input) {
  List data = new List.filled(10000, 0), output = [];
  int pos = 0, ipos = 0, skipping = 0, backwards = 0;

  var COMMANDS = {
    '>': () => ++pos,
    '<': () => --pos,
    '+': () => data[pos] = (getOrElse(data, pos, 0) + 1) % 256,
    '-': () => data[pos] = (getOrElse(data, pos, 0) + 255) % 256,
    '.': () => output.add(data[pos]),
    ',': () {
      data[pos] = getOrElse2(input, ipos++, '').codeUnitAt(0);
    },
    '[': () {
      if (data[pos] == 0) skipping = 1;
    },
    ']': () {
      if (data[pos] != 0) backwards = 1;
    }
  };

  for (var cpos = 0, l = code.length; cpos <= l; ++cpos) {
    if (skipping != 0) {
      if (code[cpos] == '[') skipping++;
      if (code[cpos] == ']') skipping--;
    } else if (backwards != 0) {
      cpos -= 2;
      if (code[cpos] == ']') backwards++;
      if (code[cpos] == '[') backwards--;
    } else if (code.length > cpos) COMMANDS[code[cpos]]();
  }

  return new String.fromCharCodes(output);
}
