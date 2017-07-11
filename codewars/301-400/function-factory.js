function functionFactory(a, b, sign) {
  switch (sign) {
    case '+': return () => a + b;
    case '-': return () => a - b;
    case '*': return () => a * b;
    case '/': return () => a / b;
  }
}
