function drawLines(points) {
		var canvas = new Canvas(100,100)  //Create a 100 x 100 canvas
		var ctx = canvas.getContext('2d');
		ctx.fillStyle="#ffffff"
		ctx.fillRect(0,0,100,100)  //Draw background
		ctx.strokeStyle="#ff0000"  //Set pen's color
		ctx.beginPath()
		//Don't delete or modify the code above
		//Your code starts here:

		ctx.moveTo(points[0][0], points[0][1]);

		for (var i = 1; i < points.length; i++) {
				ctx.lineTo(points[i][0], points[i][1]);
		}

		//Don't delete or modify the following code
		ctx.stroke()              //Draw the path you made above
		return canvas.toDataURL() //Returns the image data
}
