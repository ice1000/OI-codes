function Hero (name) {
		this.name = typeof name != "undefined" ? name : 'Hero';
		this.position = '00';
		this.health = 100;
		this.damage = 5;
		this.experience = 0;
}
