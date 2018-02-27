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

В массиве размера N, заполненного случ.числами от 0 до 10, подсчитать количество элементов, встречающихся более одного раза.*/

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
		*q=randRange();
	}
}

template <typename T>
void printArray(T *p, int N)
{
	T *ptr_end=p+N;
	cout<<'\n';
	for(T *q=p; q<ptr_end; q++)
	{
		cout<<"A["<<q-p<<"]="<<*q<<"  ";
	}
	cout<<"\n\n";
}

template <typename T>
void createArrPointers(T** arrPointers, T *arrSource, int N)
{	
	for (T* p=arrSource; p<arrSource+N; p++)
		*arrPointers++=p;
}

template <typename T>
int quantityOfRepeatingElements(T *p, int N)
{
	int sum=0;
	T** arrPointers= new T* [N];
	createArrPointers(arrPointers, p, N);	
	T** ptr_end=arrPointers+N;
	T valueCheck=0;

	for(T** q=arrPointers; q<ptr_end-1; q++)//last element doesn't matter, if previous was checked
	{
		if(*q) valueCheck=**q;
		else continue;
		bool init=false;
		for(T** r=q+1; r<ptr_end; r++)
		{				
			if(*r!=0&&**r==valueCheck)
			{
				*r=0;
				if(!init) sum++;
				init=true;
			}
		}
	}

	delete []arrPointers;

	return sum;
}


void sameElementsDialog()
{
	int N=-1;
	while(N<1)
	{
		cout<<"\nEnter the size of random array, consisting from 0 up to 10 (positive number): \n";
		cin>>N;
	}

	int *arr= new int[N];
	initArray(arr, N);
	printArray(arr, N);
	cout<<"Total quantity of repeating elements is "<<quantityOfRepeatingElements(arr, N);
	delete []arr;
}

int main()
{
	setlocale(LC_ALL, "Ru");
		
	while(1)
	{
		sameElementsDialog();

		char q=0;
		cout<<"\nEnter q - to quit: ";
		cin>>q;
		if(q=='q') break;
	}

	return 0;
}