int minima(double * arr, int N, double X, double Y, double * result)
{
	double min = Y;
	int minIndex = -1;

	for (int i = 0; i < N; i++)
	{
		if (arr[i] <= min && arr[i] >= X) {
			min = arr[i];
			minIndex = i;
		}
	}

	if (minIndex == -1)
		return 0;

	*result = min;
	return 1;
}

int average(double * arr, int N, double * result) {
	double sum = 0;
	int indexOfMax = 0;
	double max = arr[0];

	for (int i = 1; i < N; i++)
	{
		if (max < arr[i]) {
			max = arr[i];
			indexOfMax = i;
		}
	}

	if (indexOfMax == N - 1)
		return 0;

	for (int i = indexOfMax + 1; i < N; i++)
	{
		sum += arr[i];
	}

	*result = sum / (N - indexOfMax - 1);
	return 1;
}