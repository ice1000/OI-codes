function validatePIN (pin) {
		if (![4, 6].includes(pin.length))
				return false;
    for (var i = 0; i < pin.length; i++)
				if (!"1234567890".includes(pin[i])) return false;
		return true;
}
