//program by Piskunov Yury MMF IT 19 19102017

#include <iostream>
#include <clocale>
#include <iomanip>
#include <cmath>
#include <ctime>

using namespace std;

/*
•	Размер массива N запрашивать у пользователя;
•	выделение и контроль динамической памяти прямо в main;
•	в зависимости от задания создать одну или несколько функций для обработки массивов, которые передавать туда через указатели;
•	организация циклов с использованием указателей, а не с помощью A[i];

Массив чисел размера N проинициализировать случайными числами из промежутка от -N до N. 
Написать функцию циклического сдвига элементов массива вправо на k элементов.*/

#pragma region randRange
const int MIN_RAND=0;
const int MAX_RAND=9;
int randX=1;//used in randXor()

int randXor(int max=INT_MAX)
{
	int a=21, b=35, c=4;
	randX^=randX<<a;
	randX^=randX>>b;
	randX^=randX<<c;
	randX%=max;
	return randX>0?randX:-randX;
}

int randRange(int min=MIN_RAND, int max=MAX_RAND)
{	
	return (randXor()%(max-min+1))+min; //+1 for including MAX_RAND, range is the whole range i.g. -20, 50 --> 70 +bottom border
}
#pragma endregion

template <typename T>
void initArray(T *p, int N)
{
	T *ptr_end=p+N;
	for(T *q=p; q<ptr_end; q++)
	{
		*q=randRange(-N, N);
	}
}

template <typename T>
void printArray(T *p, int N, char delim=' ')
{
	T *ptr_end=p+N;
	cout<<'\n';
	for(T *q=p; q<ptr_end; q++)
	{
		cout<<*q<<delim;
	}
	cout<<"\n\n";
}

template <typename T>
void copyArrRange(T* arrDestination, T *arrSource, int a, int b, int shift=0)//TODO should throw exception on invalid range
{	
	arrDestination+=shift;
	for (T* p=arrSource+a; p<arrSource+b; p++)
		*arrDestination++=*p;
}

template <typename T>
void kShiftRight(T *dst, T *src, int N, int k)
{
	T* part1= new T [N-k];
	T* part2= new T [k];
	
	copyArrRange(part1, src, 0, N-k);
	copyArrRange(part2, src, N-k, N);
	//place part2 at the first place - part1 at the second
	copyArrRange(dst, part1, 0, N-k, k);
	copyArrRange(dst, part2, 0, k);
	
	delete []part1;
	delete []part2;
}


void kShiftRightDialog()
{
	int N=-1;
	int k=-1;
	while(N<1||k<1)
	{
		cout<<"\nEnter the size (positive number) N of the random array, consisting from -N up to +N: \n";
		cin>>N;
		cout<<"\nEnter the size of a shift (positive number) k: \n";
		cin>>k;
	}

	int *arr= new int[N];
	initArray(arr, N);
	cout<<"The initial array: "<<" \n";
	printArray(arr, N);
	kShiftRight(arr, arr, N, k);
	cout<<"An array after k shift to the right: "<<" \n";
	printArray(arr, N);
	delete []arr;
}

int main()
{
	setlocale(LC_ALL, "Ru");
		
	while(1)
	{
		kShiftRightDialog();
		
		char q=0;
		cout<<"\nEnter q - to quit: ";
		cin>>q;
		if(q=='q') break;
	}

	return 0;
}