function howManydays(month) {
		var days;
		switch (month) {
		case 2:
				days = 28;
				break;
		case 1:
		case 3:
		case 5:
		case 7:
		case 8:
		case 10:
		case 12:
				days = 31;
				break;
		default:
				days = 30;
				break;
		}
		return days;
}
