import 'dart:math';

import 'package:test/test.dart';

import 'source.dart';

class Test {
  static Random r = new Random(951394653);

  static assertEquals(a, b, [r = ""]) => expect(a, equals(b), reason: r);

  static String randomToken() => r.nextInt(10000).toString();
}

main() {
  Random r = new Random(951394653);
  test("examples", () {
    expect(
        "000000\r\n000000\r\n000000\r\n000000\r\n000000\r\n000000\r\n000000\r\n000000\r\n000000",
        equals(
            paintfuck("*e*e*e*es*es*ws*ws*w*w*w*n*n*n*ssss*s*s*s*", 0, 6, 9)),
        reason:
            "Your interpreter should initialize all cells in the datagrid to 0");
    expect(
        "111100\r\n000000\r\n000000\r\n000000\r\n000000\r\n000000\r\n000000\r\n000000\r\n000000",
        equals(
            paintfuck("*e*e*e*es*es*ws*ws*w*w*w*n*n*n*ssss*s*s*s*", 7, 6, 9)),
        reason:
            "Your interpreter should adhere to the number of iterations specified");
    expect(
        "111100\r\n000010\r\n000001\r\n000010\r\n000100\r\n000000\r\n000000\r\n000000\r\n000000",
        equals(
            paintfuck("*e*e*e*es*es*ws*ws*w*w*w*n*n*n*ssss*s*s*s*", 19, 6, 9)),
        reason: "Your interpreter should traverse the 2D datagrid correctly");
    expect(
        "111100\r\n100010\r\n100001\r\n100010\r\n111100\r\n100000\r\n100000\r\n100000\r\n100000",
        equals(
            paintfuck("*e*e*e*es*es*ws*ws*w*w*w*n*n*n*ssss*s*s*s*", 42, 6, 9)),
        reason:
            "Your interpreter should traverse the 2D datagrid correctly for all of the \"n\", \"e\", \"s\" and \"w\" commands");
    expect(
        "111100\r\n100010\r\n100001\r\n100010\r\n111100\r\n100000\r\n100000\r\n100000\r\n100000",
        equals(
            paintfuck("*e*e*e*es*es*ws*ws*w*w*w*n*n*n*ssss*s*s*s*", 100, 6, 9)),
        reason:
            "Your interpreter should terminate normally and return a representation of the final state of the 2D datagrid when all commands have been considered from left to right even if the number of iterations specified have not been fully performed");
  });

  test("ignore non-command characters", () {
    expect(
        "111100\r\n000000\r\n000000\r\n000000\r\n000000\r\n000000\r\n000000\r\n000000\r\n000000",
        equals(paintfuck(
            "o*e*eq*reqrqp*ppooqqeaqqsr*yqaooqqqfqarppppfffpppppygesfffffffffu*wrs*agwpffffst*w*uqrw*qyaprrrrrw*nuiiiid???ii*n*ynyy??ayd*r:rq????qq::tqaq:y???ss:rqsr?s*qs:q*?qs*tr??qst?q*r",
            7,
            6,
            9)),
        reason:
            "Your interpreter should simply ignore all letters that are not one of \"nesw\" and all punctuation that are not asterisks");
    expect(
        "111100\r\n000010\r\n000001\r\n000010\r\n000100\r\n000000\r\n000000\r\n000000\r\n000000",
        equals(paintfuck(
            "*e*e*e\n\t\n\t\n\t\n\t*es  *es  *ws*w      s*w*w*w*    n*n*      n*sss               s*s*               s    *s*",
            19,
            6,
            9)),
        reason: "Your interpreter should ignore all newlines, tabs and spaces");
    expect(
        "111100\r\n100010\r\n100001\r\n100010\r\n111100\r\n100000\r\n100000\r\n100000\r\n100000",
        equals(paintfuck(
            "*e..*,;e+*e*e-s;<<<<<>>>*,,,e--+s*w+>>>>>>>><;;s*<><<>w.>><>>><<<<><<>><^^^^vvv^v^vv^vv^v^^><>><>.s--*w;;*w>><<>*+^^v^vvv^++w*-+-;;;;+---++-+n;..*n*n++--;;+++-;*ssss.*s*s*s.*",
            42,
            6,
            9)),
        reason:
            "Your interpreter should not recognise any of \",\", \".\", \"<\", \">\", \"+\", \"-\" (valid Brainfuck commands), \";\" (valid Boolfuck command), \"^\" and \"v\" (valid Befunge commands) as valid Paintfuck commands");
    expect(
        "111100\r\n100010\r\n100001\r\n100010\r\n111100\r\n100000\r\n100000\r\n100000\r\n100000",
        equals(paintfuck(
            "*e*eNNESNENSNESNWWEWKSDLFJMCVXNIOWE*e*es*IOWEORUWKVDSVOIRUSKVKLVes*wsIWUENNSLNDKLNSIRIOEDSKKLNSV*ws*w*w*wIOWEURNLSVM,NXVC,MSIWOEU*n*n*n*ssSSEEWWss*s*s*s*EEWWEEWEWSSSNNSWWE",
            100,
            6,
            9)),
        reason:
            "Your interpreter should not treat uppercase \"NESW\" as valid commands");
  });

  test("initialize grids of correct size", () {
    expect("0", equals(paintfuck("", 0, 1, 1)),
        reason:
            "Your interpreter should work correctly for a grid of size 1x1");
    expect("000000\r\n000000\r\n000000\r\n000000\r\n000000\r\n000000",
        equals(paintfuck("", 0, 6, 6)),
        reason:
            "Your interpreter should work correctly for other square grids of side length > 1");
    expect(
        "0000000000\r\n0000000000\r\n0000000000\r\n0000000000\r\n0000000000\r\n0000000000\r\n0000000000\r\n0000000000\r\n0000000000\r\n0000000000",
        equals(paintfuck("", 0, 10, 10)),
        reason:
            "Your interpreter should work correctly for other square grids of side length > 1");
    expect("000", equals(paintfuck("", 0, 3, 1)),
        reason:
            "Your interpreter should properly initialize grids of height 1");
    expect("000000000000000", equals(paintfuck("", 0, 15, 1)),
        reason:
            "Your interpreter should properly initialize grids of height 1");
    expect(
        "0\r\n0\r\n0\r\n0\r\n0\r\n0\r\n0\r\n0", equals(paintfuck("", 0, 1, 8)),
        reason: "Your interpreter should properly initialize grids of width 1");
    expect("0\r\n0\r\n0\r\n0\r\n0\r\n0\r\n0\r\n0\r\n0\r\n0\r\n0",
        equals(paintfuck("", 0, 1, 11)),
        reason: "Your interpreter should properly initialize grids of width 1");
    expect(
        "000000000000000\r\n000000000000000\r\n000000000000000\r\n000000000000000\r\n000000000000000\r\n000000000000000\r\n000000000000000\r\n000000000000000\r\n000000000000000\r\n000000000000000\r\n000000000000000\r\n000000000000000\r\n000000000000000\r\n000000000000000\r\n000000000000000\r\n000000000000000\r\n000000000000000\r\n000000000000000\r\n000000000000000\r\n000000000000000",
        equals(paintfuck("", 0, 15, 20)),
        reason:
            "Your interpreter should properly initialize grids of any valid dimensions");
  });

  test("toroidal behaviour", () {
    expect(
        "00011000\r\n00011000\r\n00011000\r\n11111111\r\n11111111\r\n00011000\r\n00011000\r\n00011000\r\n00011000\r\n00011000",
        equals(paintfuck(
            "eee*s*s*s*w*w*w*w*w*w*w*n*n*n*n*n*n*n*n*n*e*e*e*e*e*e*e*s*s*s*s*s*",
            1000,
            8,
            10)),
        reason: "Your data grid should exhibit toroidal (wrapping) behaviour");
    expect(
        "00011000\r\n00011000\r\n00011000\r\n11111111\r\n00000000\r\n00001000\r\n00001000\r\n00001000\r\n00001000\r\n00001000",
        equals(paintfuck(
            "eee*s*s*s*w*w*w*w*w*w*w*n*n*n*n*n*n*n*n*n*e*e*e*e*e*e*e*s*s*s*s*s*",
            40,
            8,
            10)),
        reason: "");
    expect(
        "00011000\r\n00011000\r\n00011000\r\n11111111\r\n11111111\r\n00011000\r\n00011000\r\n00011000\r\n00011000\r\n00011000",
        equals(paintfuck(
            "eee*s*s*s*w*w*w*w*w*w*w*n*n*n*n*n*n*n*n*n*e*e*e*e*e*e*e*s*s*s*s*s*",
            66,
            8,
            10)),
        reason: "");
    expect(
        "111100\r\n100010\r\n100001\r\n100010\r\n111100\r\n100000\r\n100000\r\n100000\r\n100000",
        equals(paintfuck(
            "sssss*s*s*s*s*www*w*w*seee*ee*s*w*sw*sw*eee*n*es*e*", 1000, 6, 9)),
        reason:
            "Your data grid should exhibit toroidal (wrapping) behaviour, and not just for one example");
  });
  test("toroidal behaviour", () {
    expect("10000\r\n00000\r\n00000\r\n00000\r\n00000\r\n00000",
        equals(paintfuck("*[es*]", 1, 5, 6)),
        reason:
            "Your interpreter should not enter the loop on the first iteration of this program");
    expect("10000\r\n01000\r\n00000\r\n00000\r\n00000\r\n00000",
        equals(paintfuck("*[es*]", 5, 5, 6)),
        reason:
            "Your interpreter should just have executed the last command of the loop and about to approach the matching \"]\"");
    expect("10000\r\n01000\r\n00100\r\n00000\r\n00000\r\n00000",
        equals(paintfuck("*[es*]", 9, 5, 6)),
        reason:
            "Your interpreter should jump to the command straight *after* the matching \"[\" on the iteration where it hits the \"]\" and *not* the matching \"[\" itself");
    expect("11000\r\n01100\r\n00110\r\n00011\r\n00001\r\n10000",
        equals(paintfuck("*[es*]", 37, 5, 6)),
        reason: "Your interpreter should should exhibit toroidal behaviour ;)");
    expect("01111\r\n11111\r\n11111\r\n11111\r\n11111\r\n11111",
        equals(paintfuck("*[es*]", 1000, 5, 6)),
        reason:
            "Your interpreter should exit the loop at the correct conditions");
    expect("11111\r\n11111\r\n11111\r\n11111\r\n11111\r\n11111",
        equals(paintfuck("*[es*]*", 3000, 5, 6)),
        reason:
            "Your interpreter should exit the loop at the correct conditions");
    expect("10000\r\n10000\r\n00000\r\n00000\r\n00000",
        equals(paintfuck("*[s[e]*]", 5, 5, 5)),
        reason: "Your interpreter should also work with nested loops");
    expect("10000\r\n10000\r\n10000\r\n00000\r\n00000",
        equals(paintfuck("*[s[e]*]", 9, 5, 5)),
        reason: "Your interpreter should also work with nested loops");
    expect("11000\r\n10000\r\n10000\r\n10000\r\n10000",
        equals(paintfuck("*[s[e]*]", 23, 5, 5)),
        reason: "Your interpreter should also work with nested loops");
    expect("11000\r\n11000\r\n11000\r\n11000\r\n11000",
        equals(paintfuck("*[s[e]*]", 39, 5, 5)),
        reason: "Your interpreter should also work with nested loops");
    expect("11100\r\n11100\r\n11000\r\n11000\r\n11000",
        equals(paintfuck("*[s[e]*]", 49, 5, 5)),
        reason: "Your interpreter should also work with nested loops");
  });
  String boyNextDoor(String code, int iterations, int width, int height) {
    Set data = new Set();
    int row = 0;
    int col = 0;
    int iteration = 0;
    int codeLength = code.length;
    for (int codeIx = 0;
        codeIx < codeLength && iteration < iterations;
        codeIx++) {
      switch (code[codeIx]) {
        case 'n':
          row--;
          if (row < 0) row = height - 1;
          break;
        case 's':
          row++;
          if (row == height) row = 0;
          break;
        case 'w':
          col--;
          if (col < 0) col = width - 1;
          break;
        case 'e':
          col++;
          if (col == width) col = 0;
          break;
        case '*':
          String location = "$row|$col";
          if (data.contains(location))
            data.remove(location);
          else
            data.add(location);
          break;
        case '[':
          if (!data.contains("$row|$col")) {
            int nextOpenBracket = codeIx;
            int nextCloseBracket = codeIx;
            do {
              nextOpenBracket = code.indexOf('[', nextOpenBracket + 1);
              nextCloseBracket = code.indexOf(']', nextCloseBracket + 1);
            } while (
                nextOpenBracket != -1 && nextOpenBracket < nextCloseBracket);
            codeIx = nextCloseBracket;
          }

          break;
        case ']':
          if (data.contains("$row|$col")) {
            int prevOpenBracket = codeIx;
            int prevCloseBracket = codeIx;
            do {
              prevOpenBracket = code.lastIndexOf('[', prevOpenBracket - 1);
              prevCloseBracket = code.lastIndexOf(']', prevCloseBracket - 1);
            } while (prevOpenBracket < prevCloseBracket);
            codeIx = prevOpenBracket;
          }

          break;
        default:
          continue;
      }
      iteration++;
    }

    List<String> finalData = [];
    for (int r = 0; r < height; r++) {
      String string = "";
      for (int c = 0; c < width; c++)
        string = "$string${(data.contains("$r|$c") ? '1' : '0')}";
      finalData.add(string);
    }

    return finalData.join("\r\n");
  }

  test("random test", () {
    List commands = "nesw*".split('');
    int iterations = (1001 * r.nextDouble()).toInt();
    List randomPaintfuckProgram =
        new List(100 + (901 * r.nextDouble()).toInt());
    for (int i = 0; i < randomPaintfuckProgram.length; i++) {
      randomPaintfuckProgram[i] = commands[(5 * Test.r.nextDouble()).toInt()];
    }
    String code = randomPaintfuckProgram.join('');
    expect(boyNextDoor(code, iterations, 10, 10),
        equals(paintfuck(code, iterations, 10, 10)),
        reason: "");
  });
}
