bigToSmall = (arr) => [].concat.apply([], arr).sort((x, y) => x - y).reverse().join(">");
