var createOperator = (n, e) => function(a, b) {
		this.eval = () =>
				new Value(e(a.eval(), b.eval()))
		this.toString = () =>
				`${a.toString()} ${n} ${b.toString()}`
};
