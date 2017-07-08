/////////////////////////////////////////////////////////////////
function Maybe () {
		Object.freeze(this);
};

/////////////////////////////////////////////////////////////////
function Just (x) {
		this.toString = function () { return "Just " + x.toString(); };
		this.just = x;
		Object.freeze(this);
};
Just.prototype = new Maybe();
Just.prototype.constructor = Just;

/////////////////////////////////////////////////////////////////
function Nothing () {
		this.toString = function () { return "Nothing"; };
		Object.freeze(this);
};
Nothing.prototype = new Maybe();
Nothing.prototype.constructor = Nothing;

/////////////////////////////////////////////////////////////////
Maybe.unit = (x) => new Just(x) ;

Maybe.bind = (f) => {
		return (m) => {
				if (m instanceof Maybe) return typeof(m.just) == 'undefined' ? new Nothing : f(m.just);
				throw "fuck";
		};
};

Maybe.lift = (f) => (x) => {
		try{ return Maybe.unit(f(x)); } catch(_) { return new Nothing; }
};

Maybe.do = function(m) {
		var fns = Array.prototype.slice.call(arguments, 1);
		for (var f of fns) m = Maybe.bind(f)(m);
		return m;
};

