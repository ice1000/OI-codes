var BN = require("bignumber.js");

const add = (x, y) => new BN(x).add(new BN(y)).toNumber();
const subtract = (x, y) => new BN(x).sub(new BN(y)).toNumber();
const multiply = (x, y) => new BN(x).mul(new BN(y)).toNumber();
