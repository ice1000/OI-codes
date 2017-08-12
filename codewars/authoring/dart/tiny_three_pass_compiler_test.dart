import 'package:test/test.dart';

import 'pre.dart';
import 'source.dart';

main() {
  Compiler compiler = new Compiler();
  String prog = "[ x y z ] ( 2*3*x + 5*y - 3*z ) / (1 + 3 + 2*2)";
  Ast t1 = new BinOp(
      "/",
      new BinOp(
          "-",
          new BinOp(
              "+",
              new BinOp(
                  "*",
                  new BinOp("*", new UnOp("imm", 2), new UnOp("imm", 3)),
                  new UnOp("arg", 0)),
              new BinOp("*", new UnOp("imm", 5), new UnOp("arg", 1))),
          new BinOp("*", new UnOp("imm", 3), new UnOp("arg", 2))),
      new BinOp("+", new BinOp("+", new UnOp("imm", 1), new UnOp("imm", 3)),
          new BinOp("*", new UnOp("imm", 2), new UnOp("imm", 2))));
  Ast t2 = new BinOp(
      "/",
      new BinOp(
          "-",
          new BinOp("+", new BinOp("*", new UnOp("imm", 6), new UnOp("arg", 0)),
              new BinOp("*", new UnOp("imm", 5), new UnOp("arg", 1))),
          new BinOp("*", new UnOp("imm", 3), new UnOp("arg", 2))),
      new UnOp("imm", 8));
  Ast p1 = compiler.pass1(prog);
  Ast p2 = compiler.pass2(p1);
  group("test simple program: pass 1/2", () {
    test("pass 1", () => expect(t1.toString(), equals(p1.toString())));
    test("pass 2", () => expect(t2.toString(), equals(p2.toString())));
  });
  group("test simple program: pass 3", () {
    List<String> p3 = compiler.pass3(p2);
    test("prog(4,0,0) == 3",
        () => expect(Simulator.simulate(p3, const [4, 0, 0]), equals(3)));
    test("prog(4,8,0) == 8",
        () => expect(Simulator.simulate(p3, const [4, 8, 0]), equals(8)));
    test("prog(4,8,16) == 2",
        () => expect(Simulator.simulate(p3, const [4, 8, 16]), equals(2)));
  });
  group("test order of operators", () {
    String prog2 = "[ x y z ] x - y - z + 10 / 5 / 2 - 7 / 1 / 7";
    Compiler c = new Compiler();
    List<String> asm = c.compile(prog2);
    test("$prog2 @ [5,4,1]",
        () => expect(Simulator.simulate(asm, const [5, 4, 1]), equals(0)));
  });
}
