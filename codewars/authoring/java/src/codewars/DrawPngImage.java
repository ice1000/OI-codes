package codewars;

import javax.imageio.ImageIO;
import java.awt.*;
import java.awt.image.BufferedImage;
import java.io.IOException;
import java.io.OutputStream;
import java.util.List;
import java.util.stream.IntStream;

/**
 * Created by ice1000 on 17-6-17.
 *
 * @author ice1000
 */
public class DrawPngImage {
	public static void draw(int width, int height, OutputStream outputFile, List<Point> points) throws IOException {
		BufferedImage image = new BufferedImage(width, height, BufferedImage.TYPE_INT_RGB);
		points.forEach(p -> image.setRGB(p.x, p.y, p.color.getRGB()));
		ImageIO.write(image, "png", outputFile);
	}

	static class Point {
		int x, y;
		Color color;

		Point(int x, int y, Color color) {
			this.x = x;
			this.y = y;
			this.color = color;
		}
	}

	public class LuckyTicket {
		int to(int n) {
			return n % 10 + n / 10 % 10 + n / 100;
		}

		boolean is(int n) {
			return to(n % 1000) == to(n / 1000);
		}

		public int numberOfTickets(int from, int to) {
			return (int) IntStream.rangeClosed(from, to).filter(this::is).count();
		}
	}
}

