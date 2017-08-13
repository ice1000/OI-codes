import 'dart:math';

import 'package:test/test.dart';

import 'source.dart';

main() {
Random r = new Random();
test(
    "test echo until byte 255 encountered",
    () => expect(
        brainLuck(",+[-.,+]", "Codewars${new String.fromCharCode(255)}"),
        equals("Codewars")));
test(
    "hello world",
    () => expect(
        brainLuck(
            '++++++++++[>+++++++>++++++++++>+++>+<<<<-]>++.>+.+++++++..+++.>++.<<+++++++++++++++.>.+++.------.--------.>+.',
            ''),
        equals('Hello World!')));

test("random tokens", () {
  String tk = r.nextInt(10000).toString();
  expect(brainLuck(',+[-.,+]', "$tk${new String.fromCharCode(255)}"),
      equals(tk));
  tk = r.nextInt(10000).toString();
  expect(
      brainLuck(',[.[-],]', "$tk${new String.fromCharCode(0)}"), equals(tk));
});
test("multiplying", () {
  List<int> nums = [
    r.nextInt(sqrt(255).toInt()),
    r.nextInt(sqrt(255).toInt())
  ];
  expect(
      brainLuck(',>,<[>[->+>+<<]>>[-<<+>>]<<<-]>>.',
          new String.fromCharCodes([nums[0], nums[1]])),
      new String.fromCharCode(nums[0] * nums[1]));
});
test(
    "fibonacci number",
    () => expect(
        brainLuck(
            ',>+>>>>++++++++++++++++++++++++++++++++++++++++++++>++++++++++++++++++++++++++++++++<<<<<<[>[>>>>>>+>+<<<<<<<-]>>>>>>>[<<<<<<<+>>>>>>>-]<[>++++++++++[-<-[>>+>+<<<-]>>>[<<<+>>>-]+<[>[-]<[-]]>[<<[>>>+<<<-]>>[-]]<<]>>>[>>+>+<<<-]>>>[<<<+>>>-]+<[>[-]<[-]]>[<<+>>[-]]<<<<<<<]>>>>>[++++++++++++++++++++++++++++++++++++++++++++++++.[-]]++++++++++<[->-<]>++++++++++++++++++++++++++++++++++++++++++++++++.[-]<<<<<<<<<<<<[>>>+>+<<<<-]>>>>[<<<<+>>>>-]<-[>>.>.<<<[-]]<<[>>+>+<<<-]>>>[<<<+>>>-]<<[<+>-]>[<+>-]<<<-]',
            new String.fromCharCode(10)),
        '1, 1, 2, 3, 5, 8, 13, 21, 34, 55'));
}
