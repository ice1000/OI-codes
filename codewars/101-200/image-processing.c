#include <stdlib.h>
#include <stdio.h>

#define UC unsigned char *
#define pt(x, y, o) imageData[((x) + (y) * width) * 3 + (o)]
#define rpt(x, y, o) ret[((x) + (y) * width) * 3 + (o)]

int min(int x, int y) {
  return x < y ? x : y;
}

int max(int x, int y) {
  return x > y ? x : y;
}

UC processImage (const UC imageData,
                 int height,
                 int width,
                 void* weights,
                 int n) {
  float (*w)[n] = weights;
  UC ret = (UC) malloc(width * height * 3 * sizeof(unsigned char));
  int i, j, a, b, c;
  fprintf(stdout, "%d %d %d\n\n", width, height, n);
  double res = 0;
  for (a = 0; a < n; ++a) for (b = 0; b < n; ++b) res += w[a][b];
  printf("%.3f\n\n", res);

  for (c = 0; c < 3; ++c)
    for (i = 0; i < width; ++i) {
      for (j = 0; j < height; ++j) {

        float x = 0;
        for (a = 0; a < n; ++a) {
          for (b = 0; b < n; ++b) {
            int x_val = min(width - 1, max(0, i + a - (n >> 1)));
            int y_val = min(height - 1, max(0, j + b - (n >> 1)));
            x += pt(x_val, y_val, c) * w[a][b];
          }
        }
        if (x < 0) x = 0;
        if (x > 255) x = 255;
        rpt(i, j, c) = (int) (x + 0.5);
      }
    }
  putImageData(ret, height, width, 200, 200);
  return ret;
}

