countGrade = (scores) => { return {
		S: scores.filter(i => i == 100).length,
		A: scores.filter(i => i >= 90 && i < 100).length,
		B: scores.filter(i => i >= 80 && i < 90).length,
		C: scores.filter(i => i >= 60 && i < 80).length,
		D: scores.filter(i => i >= 0 && i < 60).length,
		X: scores.filter(i => i >= -1 && i < 0).length,
}};
