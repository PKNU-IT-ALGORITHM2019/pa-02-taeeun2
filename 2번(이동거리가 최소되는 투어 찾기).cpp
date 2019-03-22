#include<stdio.h>
#pragma warning(disable:4996)
#include<math.h>
#define MAX 100

typedef struct {
	int x;
	int y;
}Point;

int N;
Point tour[20];
double min_sum;
int find_index[20];
int cols[20];


void find(int level);
double distance(Point array[], int a, int b);
bool promising(int level, double sum);

int main() {

	FILE*fp = fopen("input.txt", "r");
	fscanf(fp, "%d", &N);

	for (int i = 0; i < N; i++)
	{
		fscanf(fp, "%d %d", &tour[i].x, &tour[i].y);
	}

	fclose(fp);
	for (int i = 0; i < N - 1; i++)
		min_sum += distance(tour, i, i + 1);
	min_sum += distance(tour, 0, N - 1);

	find(1);
	
	printf("answer : \n");
	printf("%lf\n[", min_sum);
	for (int i = 1; i <= N; i++)
	{
		if (i != N)
			printf("%d, ", find_index[i]);
		else
			printf("%d", find_index[i]);
	}
	printf("]\n");
}

double distance(Point array[], int a, int b) {

	return sqrt(pow(array[a].x - array[b].x, 2) + pow(array[a].y - array[b].y, 2));

}

bool promising(int level, double sum) {

	for (int i = 1; i < level; i++) {
		if (cols[i] == cols[level])
			return false;
	}
	for (int i = 1; i < level; i++)
		sum += distance(tour, cols[i], cols[i + 1]);
	sum += distance(tour, cols[1], cols[level]);
	if (sum > min_sum)
		return false;
	return true;
}

void find(int level) {

	double sum = 0;
	if (!promising(level, sum))
		return;
	else if (level == N) {
		for (int i = 1; i < N; i++)
			sum += distance(tour, cols[i], cols[i + 1]);
		sum += distance(tour, cols[1], cols[N]);

		if (sum < min_sum) {
			min_sum = sum;
			for (int i = 1; i <= N; i++)
				find_index[i] = cols[i];
		}
		return;
	}
	for (int i = 1; i < N; i++)
	{
		cols[level + 1] = i;
		find(level + 1);
	}
	return;
}

