#include<stdio.h>
#include<math.h>

#define true 1
#define false 0

float x[4];
int tf = false;

void work(float a, float b, float c, float d) {
	if (fabs(a + (b + (c + d)) - 24) < 0.01) tf = true;
	if (fabs(a + (b + (c - d)) - 24) < 0.01) tf = true;
	if (fabs(a + (b + (c * d)) - 24) < 0.01) tf = true;
	if (fabs(a + (b + (c / d)) - 24) < 0.01) tf = true;
	if (fabs(a + (b - (c + d)) - 24) < 0.01) tf = true;
	if (fabs(a + (b - (c - d)) - 24) < 0.01) tf = true;
	if (fabs(a + (b - (c * d)) - 24) < 0.01) tf = true;
	if (fabs(a + (b - (c / d)) - 24) < 0.01) tf = true;
	if (fabs(a + (b * (c + d)) - 24) < 0.01) tf = true;
	if (fabs(a + (b * (c - d)) - 24) < 0.01) tf = true;
	if (fabs(a + (b * (c * d)) - 24) < 0.01) tf = true;
	if (fabs(a + (b * (c / d)) - 24) < 0.01) tf = true;
	if (fabs(a + (b / (c + d)) - 24) < 0.01) tf = true;
	if (fabs(a + (b / (c - d)) - 24) < 0.01) tf = true;
	if (fabs(a + (b / (c * d)) - 24) < 0.01) tf = true;
	if (fabs(a + (b / (c / d)) - 24) < 0.01) tf = true;
	if (fabs(a - (b + (c + d)) - 24) < 0.01) tf = true;
	if (fabs(a - (b + (c - d)) - 24) < 0.01) tf = true;
	if (fabs(a - (b + (c * d)) - 24) < 0.01) tf = true;
	if (fabs(a - (b + (c / d)) - 24) < 0.01) tf = true;
	if (fabs(a - (b - (c + d)) - 24) < 0.01) tf = true;
	if (fabs(a - (b - (c - d)) - 24) < 0.01) tf = true;
	if (fabs(a - (b - (c * d)) - 24) < 0.01) tf = true;
	if (fabs(a - (b - (c / d)) - 24) < 0.01) tf = true;
	if (fabs(a - (b * (c + d)) - 24) < 0.01) tf = true;
	if (fabs(a - (b * (c - d)) - 24) < 0.01) tf = true;
	if (fabs(a - (b * (c * d)) - 24) < 0.01) tf = true;
	if (fabs(a - (b * (c / d)) - 24) < 0.01) tf = true;
	if (fabs(a - (b / (c + d)) - 24) < 0.01) tf = true;
	if (fabs(a - (b / (c - d)) - 24) < 0.01) tf = true;
	if (fabs(a - (b / (c * d)) - 24) < 0.01) tf = true;
	if (fabs(a - (b / (c / d)) - 24) < 0.01) tf = true;
	if (fabs(a * (b + (c + d)) - 24) < 0.01) tf = true;
	if (fabs(a * (b + (c - d)) - 24) < 0.01) tf = true;
	if (fabs(a * (b + (c * d)) - 24) < 0.01) tf = true;
	if (fabs(a * (b + (c / d)) - 24) < 0.01) tf = true;
	if (fabs(a * (b - (c + d)) - 24) < 0.01) tf = true;
	if (fabs(a * (b - (c - d)) - 24) < 0.01) tf = true;
	if (fabs(a * (b - (c * d)) - 24) < 0.01) tf = true;
	if (fabs(a * (b - (c / d)) - 24) < 0.01) tf = true;
	if (fabs(a * (b * (c + d)) - 24) < 0.01) tf = true;
	if (fabs(a * (b * (c - d)) - 24) < 0.01) tf = true;
	if (fabs(a * (b * (c * d)) - 24) < 0.01) tf = true;
	if (fabs(a * (b * (c / d)) - 24) < 0.01) tf = true;
	if (fabs(a * (b / (c + d)) - 24) < 0.01) tf = true;
	if (fabs(a * (b / (c - d)) - 24) < 0.01) tf = true;
	if (fabs(a * (b / (c * d)) - 24) < 0.01) tf = true;
	if (fabs(a * (b / (c / d)) - 24) < 0.01) tf = true;
	if (fabs(a / (b + (c + d)) - 24) < 0.01) tf = true;
	if (fabs(a / (b + (c - d)) - 24) < 0.01) tf = true;
	if (fabs(a / (b + (c * d)) - 24) < 0.01) tf = true;
	if (fabs(a / (b + (c / d)) - 24) < 0.01) tf = true;
	if (fabs(a / (b - (c + d)) - 24) < 0.01) tf = true;
	if (fabs(a / (b - (c - d)) - 24) < 0.01) tf = true;
	if (fabs(a / (b - (c * d)) - 24) < 0.01) tf = true;
	if (fabs(a / (b - (c / d)) - 24) < 0.01) tf = true;
	if (fabs(a / (b * (c + d)) - 24) < 0.01) tf = true;
	if (fabs(a / (b * (c - d)) - 24) < 0.01) tf = true;
	if (fabs(a / (b * (c * d)) - 24) < 0.01) tf = true;
	if (fabs(a / (b * (c / d)) - 24) < 0.01) tf = true;
	if (fabs(a / (b / (c + d)) - 24) < 0.01) tf = true;
	if (fabs(a / (b / (c - d)) - 24) < 0.01) tf = true;
	if (fabs(a / (b / (c * d)) - 24) < 0.01) tf = true;
	if (fabs(a / (b / (c / d)) - 24) < 0.01) tf = true;

	if (fabs(a + ((b + c) + d) - 24) < 0.01) tf = true;
	if (fabs(a + ((b + c) - d) - 24) < 0.01) tf = true;
	if (fabs(a + ((b + c) * d) - 24) < 0.01) tf = true;
	if (fabs(a + ((b + c) / d) - 24) < 0.01) tf = true;
	if (fabs(a + ((b - c) + d) - 24) < 0.01) tf = true;
	if (fabs(a + ((b - c) - d) - 24) < 0.01) tf = true;
	if (fabs(a + ((b - c) * d) - 24) < 0.01) tf = true;
	if (fabs(a + ((b - c) / d) - 24) < 0.01) tf = true;
	if (fabs(a + ((b * c) + d) - 24) < 0.01) tf = true;
	if (fabs(a + ((b * c) - d) - 24) < 0.01) tf = true;
	if (fabs(a + ((b * c) * d) - 24) < 0.01) tf = true;
	if (fabs(a + ((b * c) / d) - 24) < 0.01) tf = true;
	if (fabs(a + ((b / c) + d) - 24) < 0.01) tf = true;
	if (fabs(a + ((b / c) - d) - 24) < 0.01) tf = true;
	if (fabs(a + ((b / c) * d) - 24) < 0.01) tf = true;
	if (fabs(a + ((b / c) / d) - 24) < 0.01) tf = true;
	if (fabs(a - ((b + c) + d) - 24) < 0.01) tf = true;
	if (fabs(a - ((b + c) - d) - 24) < 0.01) tf = true;
	if (fabs(a - ((b + c) * d) - 24) < 0.01) tf = true;
	if (fabs(a - ((b + c) / d) - 24) < 0.01) tf = true;
	if (fabs(a - ((b - c) + d) - 24) < 0.01) tf = true;
	if (fabs(a - ((b - c) - d) - 24) < 0.01) tf = true;
	if (fabs(a - ((b - c) * d) - 24) < 0.01) tf = true;
	if (fabs(a - ((b - c) / d) - 24) < 0.01) tf = true;
	if (fabs(a - ((b * c) + d) - 24) < 0.01) tf = true;
	if (fabs(a - ((b * c) - d) - 24) < 0.01) tf = true;
	if (fabs(a - ((b * c) * d) - 24) < 0.01) tf = true;
	if (fabs(a - ((b * c) / d) - 24) < 0.01) tf = true;
	if (fabs(a - ((b / c) + d) - 24) < 0.01) tf = true;
	if (fabs(a - ((b / c) - d) - 24) < 0.01) tf = true;
	if (fabs(a - ((b / c) * d) - 24) < 0.01) tf = true;
	if (fabs(a - ((b / c) / d) - 24) < 0.01) tf = true;
	if (fabs(a * ((b + c) + d) - 24) < 0.01) tf = true;
	if (fabs(a * ((b + c) - d) - 24) < 0.01) tf = true;
	if (fabs(a * ((b + c) * d) - 24) < 0.01) tf = true;
	if (fabs(a * ((b + c) / d) - 24) < 0.01) tf = true;
	if (fabs(a * ((b - c) + d) - 24) < 0.01) tf = true;
	if (fabs(a * ((b - c) - d) - 24) < 0.01) tf = true;
	if (fabs(a * ((b - c) * d) - 24) < 0.01) tf = true;
	if (fabs(a * ((b - c) / d) - 24) < 0.01) tf = true;
	if (fabs(a * ((b * c) + d) - 24) < 0.01) tf = true;
	if (fabs(a * ((b * c) - d) - 24) < 0.01) tf = true;
	if (fabs(a * ((b * c) * d) - 24) < 0.01) tf = true;
	if (fabs(a * ((b * c) / d) - 24) < 0.01) tf = true;
	if (fabs(a * ((b / c) + d) - 24) < 0.01) tf = true;
	if (fabs(a * ((b / c) - d) - 24) < 0.01) tf = true;
	if (fabs(a * ((b / c) * d) - 24) < 0.01) tf = true;
	if (fabs(a * ((b / c) / d) - 24) < 0.01) tf = true;
	if (fabs(a / ((b + c) + d) - 24) < 0.01) tf = true;
	if (fabs(a / ((b + c) - d) - 24) < 0.01) tf = true;
	if (fabs(a / ((b + c) * d) - 24) < 0.01) tf = true;
	if (fabs(a / ((b + c) / d) - 24) < 0.01) tf = true;
	if (fabs(a / ((b - c) + d) - 24) < 0.01) tf = true;
	if (fabs(a / ((b - c) - d) - 24) < 0.01) tf = true;
	if (fabs(a / ((b - c) * d) - 24) < 0.01) tf = true;
	if (fabs(a / ((b - c) / d) - 24) < 0.01) tf = true;
	if (fabs(a / ((b * c) + d) - 24) < 0.01) tf = true;
	if (fabs(a / ((b * c) - d) - 24) < 0.01) tf = true;
	if (fabs(a / ((b * c) * d) - 24) < 0.01) tf = true;
	if (fabs(a / ((b * c) / d) - 24) < 0.01) tf = true;
	if (fabs(a / ((b / c) + d) - 24) < 0.01) tf = true;
	if (fabs(a / ((b / c) - d) - 24) < 0.01) tf = true;
	if (fabs(a / ((b / c) * d) - 24) < 0.01) tf = true;
	if (fabs(a / ((b / c) / d) - 24) < 0.01) tf = true;

	if (fabs((a + (b + c)) + d - 24) < 0.01) tf = true;
	if (fabs((a + (b + c)) - d - 24) < 0.01) tf = true;
	if (fabs((a + (b + c)) * d - 24) < 0.01) tf = true;
	if (fabs((a + (b + c)) / d - 24) < 0.01) tf = true;
	if (fabs((a + (b - c)) + d - 24) < 0.01) tf = true;
	if (fabs((a + (b - c)) - d - 24) < 0.01) tf = true;
	if (fabs((a + (b - c)) * d - 24) < 0.01) tf = true;
	if (fabs((a + (b - c)) / d - 24) < 0.01) tf = true;
	if (fabs((a + (b * c)) + d - 24) < 0.01) tf = true;
	if (fabs((a + (b * c)) - d - 24) < 0.01) tf = true;
	if (fabs((a + (b * c)) * d - 24) < 0.01) tf = true;
	if (fabs((a + (b * c)) / d - 24) < 0.01) tf = true;
	if (fabs((a + (b / c)) + d - 24) < 0.01) tf = true;
	if (fabs((a + (b / c)) - d - 24) < 0.01) tf = true;
	if (fabs((a + (b / c)) * d - 24) < 0.01) tf = true;
	if (fabs((a + (b / c)) / d - 24) < 0.01) tf = true;
	if (fabs((a - (b + c)) + d - 24) < 0.01) tf = true;
	if (fabs((a - (b + c)) - d - 24) < 0.01) tf = true;
	if (fabs((a - (b + c)) * d - 24) < 0.01) tf = true;
	if (fabs((a - (b + c)) / d - 24) < 0.01) tf = true;
	if (fabs((a - (b - c)) + d - 24) < 0.01) tf = true;
	if (fabs((a - (b - c)) - d - 24) < 0.01) tf = true;
	if (fabs((a - (b - c)) * d - 24) < 0.01) tf = true;
	if (fabs((a - (b - c)) / d - 24) < 0.01) tf = true;
	if (fabs((a - (b * c)) + d - 24) < 0.01) tf = true;
	if (fabs((a - (b * c)) - d - 24) < 0.01) tf = true;
	if (fabs((a - (b * c)) * d - 24) < 0.01) tf = true;
	if (fabs((a - (b * c)) / d - 24) < 0.01) tf = true;
	if (fabs((a - (b / c)) + d - 24) < 0.01) tf = true;
	if (fabs((a - (b / c)) - d - 24) < 0.01) tf = true;
	if (fabs((a - (b / c)) * d - 24) < 0.01) tf = true;
	if (fabs((a - (b / c)) / d - 24) < 0.01) tf = true;
	if (fabs((a * (b + c)) + d - 24) < 0.01) tf = true;
	if (fabs((a * (b + c)) - d - 24) < 0.01) tf = true;
	if (fabs((a * (b + c)) * d - 24) < 0.01) tf = true;
	if (fabs((a * (b + c)) / d - 24) < 0.01) tf = true;
	if (fabs((a * (b - c)) + d - 24) < 0.01) tf = true;
	if (fabs((a * (b - c)) - d - 24) < 0.01) tf = true;
	if (fabs((a * (b - c)) * d - 24) < 0.01) tf = true;
	if (fabs((a * (b - c)) / d - 24) < 0.01) tf = true;
	if (fabs((a * (b * c)) + d - 24) < 0.01) tf = true;
	if (fabs((a * (b * c)) - d - 24) < 0.01) tf = true;
	if (fabs((a * (b * c)) * d - 24) < 0.01) tf = true;
	if (fabs((a * (b * c)) / d - 24) < 0.01) tf = true;
	if (fabs((a * (b / c)) + d - 24) < 0.01) tf = true;
	if (fabs((a * (b / c)) - d - 24) < 0.01) tf = true;
	if (fabs((a * (b / c)) * d - 24) < 0.01) tf = true;
	if (fabs((a * (b / c)) / d - 24) < 0.01) tf = true;
	if (fabs((a / (b + c)) + d - 24) < 0.01) tf = true;
	if (fabs((a / (b + c)) - d - 24) < 0.01) tf = true;
	if (fabs((a / (b + c)) * d - 24) < 0.01) tf = true;
	if (fabs((a / (b + c)) / d - 24) < 0.01) tf = true;
	if (fabs((a / (b - c)) + d - 24) < 0.01) tf = true;
	if (fabs((a / (b - c)) - d - 24) < 0.01) tf = true;
	if (fabs((a / (b - c)) * d - 24) < 0.01) tf = true;
	if (fabs((a / (b - c)) / d - 24) < 0.01) tf = true;
	if (fabs((a / (b * c)) + d - 24) < 0.01) tf = true;
	if (fabs((a / (b * c)) - d - 24) < 0.01) tf = true;
	if (fabs((a / (b * c)) * d - 24) < 0.01) tf = true;
	if (fabs((a / (b * c)) / d - 24) < 0.01) tf = true;
	if (fabs((a / (b / c)) + d - 24) < 0.01) tf = true;
	if (fabs((a / (b / c)) - d - 24) < 0.01) tf = true;
	if (fabs((a / (b / c)) * d - 24) < 0.01) tf = true;
	if (fabs((a / (b / c)) / d - 24) < 0.01) tf = true;

	if (fabs(((a + b) + c) + d - 24) < 0.01) tf = true;
	if (fabs(((a + b) + c) - d - 24) < 0.01) tf = true;
	if (fabs(((a + b) + c) * d - 24) < 0.01) tf = true;
	if (fabs(((a + b) + c) / d - 24) < 0.01) tf = true;
	if (fabs(((a + b) - c) + d - 24) < 0.01) tf = true;
	if (fabs(((a + b) - c) - d - 24) < 0.01) tf = true;
	if (fabs(((a + b) - c) * d - 24) < 0.01) tf = true;
	if (fabs(((a + b) - c) / d - 24) < 0.01) tf = true;
	if (fabs(((a + b) * c) + d - 24) < 0.01) tf = true;
	if (fabs(((a + b) * c) - d - 24) < 0.01) tf = true;
	if (fabs(((a + b) * c) * d - 24) < 0.01) tf = true;
	if (fabs(((a + b) * c) / d - 24) < 0.01) tf = true;
	if (fabs(((a + b) / c) + d - 24) < 0.01) tf = true;
	if (fabs(((a + b) / c) - d - 24) < 0.01) tf = true;
	if (fabs(((a + b) / c) * d - 24) < 0.01) tf = true;
	if (fabs(((a + b) / c) / d - 24) < 0.01) tf = true;
	if (fabs(((a - b) + c) + d - 24) < 0.01) tf = true;
	if (fabs(((a - b) + c) - d - 24) < 0.01) tf = true;
	if (fabs(((a - b) + c) * d - 24) < 0.01) tf = true;
	if (fabs(((a - b) + c) / d - 24) < 0.01) tf = true;
	if (fabs(((a - b) - c) + d - 24) < 0.01) tf = true;
	if (fabs(((a - b) - c) - d - 24) < 0.01) tf = true;
	if (fabs(((a - b) - c) * d - 24) < 0.01) tf = true;
	if (fabs(((a - b) - c) / d - 24) < 0.01) tf = true;
	if (fabs(((a - b) * c) + d - 24) < 0.01) tf = true;
	if (fabs(((a - b) * c) - d - 24) < 0.01) tf = true;
	if (fabs(((a - b) * c) * d - 24) < 0.01) tf = true;
	if (fabs(((a - b) * c) / d - 24) < 0.01) tf = true;
	if (fabs(((a - b) / c) + d - 24) < 0.01) tf = true;
	if (fabs(((a - b) / c) - d - 24) < 0.01) tf = true;
	if (fabs(((a - b) / c) * d - 24) < 0.01) tf = true;
	if (fabs(((a - b) / c) / d - 24) < 0.01) tf = true;
	if (fabs(((a * b) + c) + d - 24) < 0.01) tf = true;
	if (fabs(((a * b) + c) - d - 24) < 0.01) tf = true;
	if (fabs(((a * b) + c) * d - 24) < 0.01) tf = true;
	if (fabs(((a * b) + c) / d - 24) < 0.01) tf = true;
	if (fabs(((a * b) - c) + d - 24) < 0.01) tf = true;
	if (fabs(((a * b) - c) - d - 24) < 0.01) tf = true;
	if (fabs(((a * b) - c) * d - 24) < 0.01) tf = true;
	if (fabs(((a * b) - c) / d - 24) < 0.01) tf = true;
	if (fabs(((a * b) * c) + d - 24) < 0.01) tf = true;
	if (fabs(((a * b) * c) - d - 24) < 0.01) tf = true;
	if (fabs(((a * b) * c) * d - 24) < 0.01) tf = true;
	if (fabs(((a * b) * c) / d - 24) < 0.01) tf = true;
	if (fabs(((a * b) / c) + d - 24) < 0.01) tf = true;
	if (fabs(((a * b) / c) - d - 24) < 0.01) tf = true;
	if (fabs(((a * b) / c) * d - 24) < 0.01) tf = true;
	if (fabs(((a * b) / c) / d - 24) < 0.01) tf = true;
	if (fabs(((a / b) + c) + d - 24) < 0.01) tf = true;
	if (fabs(((a / b) + c) - d - 24) < 0.01) tf = true;
	if (fabs(((a / b) + c) * d - 24) < 0.01) tf = true;
	if (fabs(((a / b) + c) / d - 24) < 0.01) tf = true;
	if (fabs(((a / b) - c) + d - 24) < 0.01) tf = true;
	if (fabs(((a / b) - c) - d - 24) < 0.01) tf = true;
	if (fabs(((a / b) - c) * d - 24) < 0.01) tf = true;
	if (fabs(((a / b) - c) / d - 24) < 0.01) tf = true;
	if (fabs(((a / b) * c) + d - 24) < 0.01) tf = true;
	if (fabs(((a / b) * c) - d - 24) < 0.01) tf = true;
	if (fabs(((a / b) * c) * d - 24) < 0.01) tf = true;
	if (fabs(((a / b) * c) / d - 24) < 0.01) tf = true;
	if (fabs(((a / b) / c) + d - 24) < 0.01) tf = true;
	if (fabs(((a / b) / c) - d - 24) < 0.01) tf = true;
	if (fabs(((a / b) / c) * d - 24) < 0.01) tf = true;
	if (fabs(((a / b) / c) / d - 24) < 0.01) tf = true;

	if (fabs((a + b) + (c + d) - 24) < 0.01) tf = true;
	if (fabs((a - b) + (c + d) - 24) < 0.01) tf = true;
	if (fabs((a * b) + (c + d) - 24) < 0.01) tf = true;
	if (fabs((a / b) + (c + d) - 24) < 0.01) tf = true;
	if (fabs((a + b) + (c - d) - 24) < 0.01) tf = true;
	if (fabs((a - b) + (c - d) - 24) < 0.01) tf = true;
	if (fabs((a * b) + (c - d) - 24) < 0.01) tf = true;
	if (fabs((a / b) + (c - d) - 24) < 0.01) tf = true;
	if (fabs((a + b) + (c * d) - 24) < 0.01) tf = true;
	if (fabs((a - b) + (c * d) - 24) < 0.01) tf = true;
	if (fabs((a * b) + (c * d) - 24) < 0.01) tf = true;
	if (fabs((a / b) + (c * d) - 24) < 0.01) tf = true;
	if (fabs((a + b) + (c / d) - 24) < 0.01) tf = true;
	if (fabs((a - b) + (c / d) - 24) < 0.01) tf = true;
	if (fabs((a * b) + (c / d) - 24) < 0.01) tf = true;
	if (fabs((a / b) + (c / d) - 24) < 0.01) tf = true;
	if (fabs((a + b) - (c + d) - 24) < 0.01) tf = true;
	if (fabs((a - b) - (c + d) - 24) < 0.01) tf = true;
	if (fabs((a * b) - (c + d) - 24) < 0.01) tf = true;
	if (fabs((a / b) - (c + d) - 24) < 0.01) tf = true;
	if (fabs((a + b) - (c - d) - 24) < 0.01) tf = true;
	if (fabs((a - b) - (c - d) - 24) < 0.01) tf = true;
	if (fabs((a * b) - (c - d) - 24) < 0.01) tf = true;
	if (fabs((a / b) - (c - d) - 24) < 0.01) tf = true;
	if (fabs((a + b) - (c * d) - 24) < 0.01) tf = true;
	if (fabs((a - b) - (c * d) - 24) < 0.01) tf = true;
	if (fabs((a * b) - (c * d) - 24) < 0.01) tf = true;
	if (fabs((a / b) - (c * d) - 24) < 0.01) tf = true;
	if (fabs((a + b) - (c / d) - 24) < 0.01) tf = true;
	if (fabs((a - b) - (c / d) - 24) < 0.01) tf = true;
	if (fabs((a * b) - (c / d) - 24) < 0.01) tf = true;
	if (fabs((a / b) - (c / d) - 24) < 0.01) tf = true;
	if (fabs((a + b) * (c + d) - 24) < 0.01) tf = true;
	if (fabs((a - b) * (c + d) - 24) < 0.01) tf = true;
	if (fabs((a * b) * (c + d) - 24) < 0.01) tf = true;
	if (fabs((a / b) * (c + d) - 24) < 0.01) tf = true;
	if (fabs((a + b) * (c - d) - 24) < 0.01) tf = true;
	if (fabs((a - b) * (c - d) - 24) < 0.01) tf = true;
	if (fabs((a * b) * (c - d) - 24) < 0.01) tf = true;
	if (fabs((a / b) * (c - d) - 24) < 0.01) tf = true;
	if (fabs((a + b) * (c * d) - 24) < 0.01) tf = true;
	if (fabs((a - b) * (c * d) - 24) < 0.01) tf = true;
	if (fabs((a * b) * (c * d) - 24) < 0.01) tf = true;
	if (fabs((a / b) * (c * d) - 24) < 0.01) tf = true;
	if (fabs((a + b) * (c / d) - 24) < 0.01) tf = true;
	if (fabs((a - b) * (c / d) - 24) < 0.01) tf = true;
	if (fabs((a * b) * (c / d) - 24) < 0.01) tf = true;
	if (fabs((a / b) * (c / d) - 24) < 0.01) tf = true;
	if (fabs((a + b) / (c + d) - 24) < 0.01) tf = true;
	if (fabs((a - b) / (c + d) - 24) < 0.01) tf = true;
	if (fabs((a * b) / (c + d) - 24) < 0.01) tf = true;
	if (fabs((a / b) / (c + d) - 24) < 0.01) tf = true;
	if (fabs((a + b) / (c - d) - 24) < 0.01) tf = true;
	if (fabs((a - b) / (c - d) - 24) < 0.01) tf = true;
	if (fabs((a * b) / (c - d) - 24) < 0.01) tf = true;
	if (fabs((a / b) / (c - d) - 24) < 0.01) tf = true;
	if (fabs((a + b) / (c * d) - 24) < 0.01) tf = true;
	if (fabs((a - b) / (c * d) - 24) < 0.01) tf = true;
	if (fabs((a * b) / (c * d) - 24) < 0.01) tf = true;
	if (fabs((a / b) / (c * d) - 24) < 0.01) tf = true;
	if (fabs((a + b) / (c / d) - 24) < 0.01) tf = true;
	if (fabs((a - b) / (c / d) - 24) < 0.01) tf = true;
	if (fabs((a * b) / (c / d) - 24) < 0.01) tf = true;
	if (fabs((a / b) / (c / d) - 24) < 0.01) tf = true;
}

int main(int argc, const char *argv[]) {
	scanf("%f %f %f %f", &x[0], &x[1], &x[2], &x[3]);
	float a, b, c, d;
	while (x[0] > 0 && x[1] > 0 && x[2] > 0 && x[3] > 0) {
		tf = false;
		for (int ia = 0; ia < 4; ++ia)
			for (int ib = 0; ib < 4; ++ib)
				if (ib != ia)
					for (int ic = 0; ic < 4; ++ic)
						if (ic != ia && ic != ib)
							for (int id = 0; id < 4; ++id)
								if (id != ia && id != ib && id != ic) {
									a = x[ia], b = x[ib], c = x[ic], d = x[id];
									work(a, b, c, d);
								}
		if (tf) puts("YES");
		else puts("NO");
		scanf("%f %f %f %f", &x[0], &x[1], &x[2], &x[3]);
	}
	return 0;
}
