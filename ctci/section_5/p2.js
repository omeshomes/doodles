
function bintostring(num) {
	if (num > 1 || num < 0) {
		console.log("ERROR");
		return;
	}

	var final = '.';
	while (num > 0) {
		if (final.length > 32) {
			console.log("ERROR");
			return;
		}

		var n = num * 2;
		if (n >= 1) {
			final += '1';
			num = n-1;
		} else {
			final += '0';
			num = n;
		}
	}

	// for (var i = 1; i < 33; i++) {
	// 	var shifted = num << i;
	// 	var mask = (~0) ^ 1; // all ones, except one's place is 0
	// 	console.log(mask);
	// 	if (shifted & mask === shifted) {
	// 		final += '1';
	// 	} else {
	// 		final += '0';
	// 	}
	// }

	console.log(final);
}

bintostring(.5);
bintostring(.25);
bintostring(.75);
bintostring(.72);