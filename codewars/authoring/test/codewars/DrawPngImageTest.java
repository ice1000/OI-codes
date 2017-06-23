package codewars;

import org.junit.Test;

import javax.imageio.ImageIO;
import java.awt.*;
import java.awt.image.BufferedImage;
import java.io.IOException;
import java.io.OutputStream;
import java.util.ArrayList;
import java.util.List;
import java.util.Random;

import static org.junit.Assert.assertEquals;

/**
 * Created by ice1000 on 17-6-17.
 *
 * @author ice1000
 */
public class DrawPngImageTest {
	@Test
	public void trivialTest() throws Exception {
		byte[] expected = new byte[]{
				-119, 80, 78, 71, 13, 10, 26, 10, 0, 0, 0, 13, 73, 72, 68, 82, 0, 0, 0, 1, 0, 0, 0, 1, 8, 2, 0, 0, 0, -112,
				119, 83, -34, 0, 0, 0, 12, 73, 68, 65, 84, 120, -38, 99, 96, 96, 96, 0, 0, 0, 4, 0, 1, -56, -22, -21, -7, 0,
				0, 0, 0, 73, 69, 78, 68, -82, 66, 96, -126, 0
		};
		final int[] len = {0};
		byte[] codewarsResult = new byte[expected.length];
		try (OutputStream stream = new OutputStream() {
			@Override
			public void write(int b) throws IOException {
				codewarsResult[len[0]++] = (byte) b;
			}
		}) {
			List<DrawPngImage.Point> points = new ArrayList<>();
			points.add(new DrawPngImage.Point(0, 0, Color.BLACK));
			DrawPngImage.draw(1, 1, stream, points);
			for (int i = 0; i < len[0]; i++) assertEquals("should equal", expected[i], codewarsResult[i]);
		}
	}

	@Test
	public void realTest() throws Exception {
		for (int ___ = 0; ___ < 5; ___++) {
			byte[] expected = new byte[2048 * 1024];
			final int[] len = {0};
			final int[] len2 = {0};
			byte[] codewarsResult = new byte[expected.length];
			OutputStream stream = new OutputStream() {
				@Override
				public void write(int b) throws IOException {
					codewarsResult[len[0]++] = (byte) b;
				}
			};
			OutputStream expectedStream = new OutputStream() {
				@Override
				public void write(int b) throws IOException {
					expected[len2[0]++] = (byte) b;
				}
			};
			List<DrawPngImage.Point> points = new ArrayList<>();
			Random random = new Random(System.currentTimeMillis());
			int width = random.nextInt(100) + 10;
			int height = random.nextInt(100) + 10;
			for (int __ = 0, n = random.nextInt(2000) + 1000; __ < n; __++)
				points.add(new DrawPngImage.Point(random.nextInt(width), random.nextInt(height), new Color(random.nextInt(0xFFFFFF))));
			BufferedImage image = new BufferedImage(width, height, BufferedImage.TYPE_INT_RGB);
			points.forEach(p -> image.setRGB(p.x, p.y, p.color.getRGB()));
			ImageIO.write(image, "png", expectedStream);
			DrawPngImage.draw(width, height, stream, points);
			for (int i = 0; i < expected.length; i++) {
				assertEquals(expected[i], codewarsResult[i]);
			}
		}
	}
}
