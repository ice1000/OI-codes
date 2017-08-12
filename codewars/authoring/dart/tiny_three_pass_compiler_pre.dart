abstract class Ast {
  String op();
}

class BinOp implements Ast {
  String _op;
  Ast a;
  Ast b;

  BinOp(String op, Ast a, Ast b) {
    this._op = op;
    this.a = a;
    this.b = b;
  }

  @override
  String op() {
    return _op;
  }

  @override
  bool operator ==(Object o) {
    if (this == o) return true;
    if (!(o is BinOp)) return false;
    BinOp that = o as BinOp;
    return (_op == that._op) && (a == that.a) && (b == that.b);
  }

  @override
  String toString() => "{'op':'$_op','a':$a,'b':$b}";
}

class UnOp implements Ast {
  String _op;
  int n;

  UnOp(String op, int n) {
    this._op = op;
    this.n = n;
  }

  @override
  String op() {
    return _op;
  }

  @override
  bool operator ==(Object o) {
    if (this == o) return true;
    if (!(o is UnOp)) return false;
    UnOp that = o as UnOp;
    return (_op == that._op) && n == that.n;
  }

  @override
  String toString() => "{'op':'$op','n':$n}";
}

class Simulator {
  static int simulate(List<String> asm, List<int> argv) {
    int r0 = 0;
    int r1 = 0;
    List<int> stack = new List();
    asm.forEach((ins) {
      switch (ins.substring(0, 2)) {
        case "IM":
          r0 = int.parse(ins.substring(2).trim());
          break;
        case "AR":
          r0 = argv[int.parse(ins.substring(2).trim())];
          break;
        case "SW":
          int tmp = r0;
          r0 = r1;
          r1 = tmp;
          break;
        case "PU":
          stack.add(r0);
          break;
        case "PO":
          r0 = stack.removeLast();
          break;
        case "AD":
          r0 += r1;
          break;
        case "SU":
          r0 -= r1;
          break;
        case "MU":
          r0 *= r1;
          break;
        case "DI":
          r0 ~/= r1;
          break;
      }
    });
    return r0;
  }
}
