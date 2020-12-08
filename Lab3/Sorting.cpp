// Sorting.cpp
// Лабораторная работа №3.
// Студент группы 494, Тагин Игорь Юрьевич. 2020 год

void Shell(int*& Array, int Size,int& Swaps, int& Compares)
{
	int step, i, j, tmp;
	for (step = Size / 2; step > 0; step /= 2)
		for (i = step; i < Size; i++)
			for (j = i - step; j >= 0; j -= step)
			{
				Compares++;
				if (Array[j] > Array[j + step]) {
					tmp = Array[j];
					Array[j] = Array[j + step];
					Array[j + step] = tmp;
					Swaps++;
				}
				else {
					break;
				}
				
			}
}

void Bubble(int*& Array, int Size, int& Swaps, int& Compares) {
	int temp;
	for (int i = 0; i < Size - 1; i++) {
		for (int j = 0; j < Size - i - 1; j++) {
			if (Array[j] > Array[j + 1]) {
				temp = Array[j];
				Array[j] = Array[j + 1];
				Array[j + 1] = temp;
				Swaps++;
			}
			Compares++;
		}
	}
}

void SelectionSort(int*& Array, int Size, int& Swaps, int& Compares) {
	int temp;
	for (int startIndex = 0; startIndex < Size - 1; ++startIndex)
	{
		int smallestIndex = startIndex;
		for (int currentIndex = startIndex + 1; currentIndex < Size; ++currentIndex)
		{
			if (Array[currentIndex] < Array[smallestIndex]) {
				smallestIndex = currentIndex;
			}
			Compares++;
		}

		temp = Array[startIndex];
		Array[startIndex] = Array[smallestIndex];
		Array[smallestIndex] = temp;
		Swaps++;
	}

}

void Insertion(int*& Array, int Size, int& Swaps, int& Compares) {
	int i, key, j;
	for (i = 1; i < Size; i++)
	{
		key = Array[i];
		j = i - 1;

		while (j >= 0 )
		{
			Compares++;
			if (Array[j] > key) {
				Array[j + 1] = Array[j];
				Swaps++;
				j = j - 1;
			}
			else {
				break;
			}
		}
		Array[j + 1] = key;
	}
}

void QuickSort(int*& Array, int first, int last, int& Swaps, int& Compares)
{
	int mid, temp;
	int f = first, l = last;
	mid = Array[(f + l) / 2];
	do
	{
		while (Array[f] < mid) {
			f++;
			Compares++;
		}
		while (Array[l] > mid) {
			l--;
			Compares++;
		}
		
		if (f <= l)
		{
			temp = Array[f];
			Array[f] = Array[l];
			Array[l] = temp;
			Swaps++;
			f++;
			l--;
		}
	} while (f < l);
	if (first < l) QuickSort(Array, first, l,Swaps,Compares);
	if (f < last) QuickSort(Array, f, last,Swaps,Compares);
}