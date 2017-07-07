go = (a) => a < 16 ? `0${a.toString(16)}` : a.toString(16);
colorOf = (r,g,b) => `#${go(r)}${go(g)}${go(b)}`;
