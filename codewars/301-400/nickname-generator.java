class Generator {
		public static String nickname (String name) {
				if (name.length() < 4) return "Error: Name too short";
				if ("aeoiu".contains(name.charAt(2) + "")) return name.substring(0, 4);
				return name.substring(0, 3);
		}
}
