//question1: The top secret file number is...
answer1="2452";

//question2: Super agent's name is...
answer2="zaOll";

//question3: He stole the treasure is...
answer3="Banana peel";

function topSecret(str) {
		fuck = (i) => {
				var ret = i.charCodeAt() - 3;
				if ([62, 63, 64, 94, 95, 96].includes(ret)) ret += 26;
				if (!"qwertyuiopasdfghjklzxcvbnmQWERTYUIOPASDFGHJKLZXCVBNM".includes(i)) return i;
				return String.fromCharCode(ret);
		};
		return str.split("").map(fuck).join("");
}
