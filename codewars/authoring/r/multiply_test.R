test_that("test for associativity of multiplication", {
		i <- 0
	  while (i < 100) {
		    a <- runif(1, 0, 10000)
				b <- runif(1, 0, 10000)
				c <- runif(1, 0, 10000)
				expect_equal(mul(a, b), a * b)
				expect_equal(mul(mul(a, b), c), a * b * c)
				expect_equal(mul(a, mul(b, c)), a * b * c)
				i <- i + 1
		}
})
