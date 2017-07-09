CurryIt = fn => {
		var ac = [];
		var fn2;
		return function(...args) {
				if (Array.isArray(this)) ac = [...this];
				if (typeof args[0] === 'function') {
						fn2 = args[0];
				} else {
						if (args.length === 0) {
								const copied = [...ac];
								ac = [];
								if (typeof fn2 === 'function') {
										if (typeof fn === 'function') return fn.call(copied, fn2);
										return fn2(...copied);
								}
								return fn(...copied);
						}
						ac = [...ac, ...args];
				}
		};
};
