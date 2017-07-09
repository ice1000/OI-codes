Array.prototype.max = function() { return parseInt(this.reduce((i, j) => i > j ? i : j)); }
