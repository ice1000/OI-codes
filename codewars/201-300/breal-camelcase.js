solution = (s) => s.split("").map(c => "QWERTYUIOPASDFGHJKLZXCVBNM".includes(c) ? ` ${c}` : c).join("");
