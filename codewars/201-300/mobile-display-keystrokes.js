function mobileKeyboard(str){
		console.log(str);
		var tot = 0;
		for (var ii = 0; ii < str.length; ++ii) {
				var i = str.charAt(ii);
				if (" 1234567890*#".includes(i)) ++tot;
				else if ("adgjmptw".includes(i)) tot += 2;
				else if ("behknqux".includes(i)) tot += 3;
				else if ("cfilorvy".includes(i)) tot += 4;
				else if (      "sz".includes(i)) tot += 5;
		}
		return tot;
}
