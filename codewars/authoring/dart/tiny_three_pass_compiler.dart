import 'pre.dart';

class Compiler {
  List<String> tokens;
  Map<String, int> args;

  static List<String> tokenize(String prog) {
    List<String> tokens = new List();
    RegExp pattern = new RegExp("[-+*/()\\[\\]]|[a-zA-Z]+|\\d+");
    pattern.allMatches(prog).toList().forEach((m) {
      tokens.add(m.group(0));
    });
    tokens.add("\$"); // end-of-stream
    return tokens;
  }

  String peek() => tokens.first;

  String consume() => tokens.removeAt(0);

  List<String> compile(String prog) => pass3(pass2(pass1(prog)));

  Ast func() {
    consume(); // "["
    int i = 0;
    while (!(peek() == "]")) {
      args[consume()] = i++;
    }
    consume(); // "]"
    return expression();
  }

  Ast expression() {
    Ast result = term();
    while (peek() == ("+") || peek() == ("-")) {
      result = new BinOp(consume(), result, term());
    }
    return result;
  }

  Ast term() {
    Ast result = factor();
    while (peek() == ("*") || peek() == ("/")) {
      result = new BinOp(consume(), result, factor());
    }
    return result;
  }

  bool isDigit(int s) => s >= '0'.codeUnitAt(0) && s <= '9'.codeUnitAt(0);

  Ast factor() {
    String token = consume();
    if (token == ("(")) {
      Ast result = expression();
      consume(); // ")"
      return result;
    } else if (isDigit(token.codeUnitAt(0))) {
      return new UnOp("imm", int.parse(token));
    } else {
      return new UnOp("arg", args[token]);
    }
  }

  int compute(String op, int n1, int n2) {
    switch (op) {
      case "+":
        return n1 + n2;
      case "-":
        return n1 - n2;
      case "*":
        return n1 * n2;
      case "/":
        return n1 ~/ n2;
    }
    return 0;
  }

  /**
   * Returns an un-optimized AST
   */
  Ast pass1(String prog) {
    tokens = tokenize(prog);
    args = new Map();
    return func();
  }

  /**
   * Returns an AST with constant expressions reduced
   */
  Ast pass2(Ast ast) {
    if (ast is BinOp) {
      BinOp binOp = ast;
      Ast a = pass2(binOp.a);
      Ast b = pass2(binOp.b);
      if (a is UnOp && a.op() == "imm" && b is UnOp && b.op() == "imm") {
        return new UnOp("imm", compute(binOp.op(), a.n, b.n));
      }
      return new BinOp(binOp.op(), a, b);
    }
    return ast;
  }

  List<String> pass3(Ast ast) {
    if (ast.op() == "arg") {
      return ["AR ${(ast as UnOp).n}"];
    } else if (ast.op() == "imm") {
      return ["IM ${(ast as UnOp).n}"];
    } else {
      String opcode = _opcode(ast.op());
      BinOp binOp = ast as BinOp;
      List<String> opcodes = new List();
      opcodes.addAll(pass3(binOp.a));
      opcodes.add("PU");
      opcodes.addAll(pass3(binOp.b));
      opcodes.add("SW");
      opcodes.add("PO");
      opcodes.add(opcode);
      return opcodes;
    }
  }

  String _opcode(String op) {
    switch (op) {
      case "+":
        return "AD";
      case "-":
        return "SU";
      case "*":
        return "MU";
      case "/":
        return "DI";
    }
    throw "gg";
  }
}
