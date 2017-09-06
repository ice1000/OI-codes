object Logger {
  def log(complex: Array[Double]): Array[Double] = {
    if (complex(0) == 0.0 && complex(1) == 0.0) throw new ArithmeticException("")
    Array(Math.log(Math.hypot(complex(0), complex(1))), Math.atan2(complex(1), complex(0)))
  }
}
