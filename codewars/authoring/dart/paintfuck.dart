String paintfuck(String code, int iterations, int width, int height) {
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
          } while (nextOpenBracket != -1 && nextOpenBracket < nextCloseBracket);
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
    StringBuilder line = new StringBuilder();
    for (int c = 0; c < width; c++)
      line.append(data.contains("$r|$c") ? '1' : '0');
    finalData.add(line.toString());
  }

  return finalData.join("\r\n");
}

class StringBuilder {
  String string = "";

  void append(String s) => string = "$string$s";

  @override
  String toString() {
    return string;
  }
}

