﻿
#include <stdio.h>
#include <iostream> 
#include <stdlib.h>  
#include <time.h>
#include <cmath>
#include <omp.h>  
#include <windows.h>
#include <string> 
using namespace std;



int main() {
	setlocale(LC_ALL, "Rus");// чтоб в консоли был русский язык
	srand(time(0));// для того, чтоб в генераторе чисел каждый раз при запуске прогаммы были разные числа
	int n;// кол-во потокв
	int N;// рамер массива
	int* a;// указатель на массив
	bool fail = false;// для проверки ввода

	do {
		fail = false;
		cout << "Введите размер массива = ";// текствое сообщение
		cin >> N;// ввод перменной
		if (cin.fail() || N <= 0) {// если не может преобразовать 
			cout << "Вы ввели не число или число меньше нуля. Повторите ввод заново!" << endl;
			fail = true;
		}
		cin.clear();// сбрасывает то, что введено в потоке
		cin.ignore();//пропускает для следущего ввода в потоке
	} while (fail);

	do {
		fail = false;
		cout << "Введите кол-во потоков = ";
		cin >> n;// вводим кол-во потоков
		if (cin.fail() || n <= 0) {
			cout << "Вы ввели не число или число меньше/равное нулю. Повторите ввод заново!" << endl;
			fail = true;
		}
		cin.clear();
		cin.ignore();
	} while (fail);	

	a = new int[N];// объявляем массив размерность Эн

	for (int i = 0; i < N; i++) {
		a[i] = 100 + rand() % 10000000;// запоняем массив
	}
	
	double time = omp_get_wtime();// вкл. счетчик времени
	omp_set_dynamic(false);//отключение динамической регулировки потоков, не можем во время выполнения программы регулировать кол-во потокв
	omp_set_num_threads(n);// определяем сколько потоков, записывается введеная перменная 

	long unsigned int summa = 0;// результат выполнения
	long unsigned int sum = 0;// результат выполнения

#pragma omp parallel firstprivate(sum) shared(summa) // выполнение в первую очередь и параллельно, второе в общем потоке без парарллельного выполнения
	{
		sum = 0;

#pragma omp for// цикл фор выполняется парарллельно
		for (int i = 0; i < N; i++)
		{
			if (i % 2 == 0)
			{
				sum += a[i];// чет. индк склыдываем
			}
			else
			{
				sum -= a[i];// нечетный вычитаем
			}
		}
#pragma omp critical// критическая область (выполняется в общем потоке), для того чтоб сложить все результаты
		{
			summa += sum;

		}
	}
	cout << "Значение выражения с потоками = " << summa << "\n"; // выводим результат
	time = omp_get_wtime() - time;// считаем время выполнения программы
	cout << "Время вычислений = " << time << "\n";// выводим время

	//-----------------------------

	time = omp_get_wtime();// запускаем таймер

	summa = 0;// обнулем сумму

#pragma omp parallel for reduction (+: summa)  // расспараллеливаем цикл фор, summa - редукционная переменная ( с котрой выполняется действие сложение)

	for (int i = 0; i < N; i++)
	{
		if (i % 2 == 0)
		{
			summa += a[i];
		}
		else
		{
			summa -= a[i];
		}
	}

	time = omp_get_wtime() - time;// вычислем время выполнения
	
	cout << "Значение выражения с потоками через редукцию = " << summa << "\n";// выводим результат
	cout << "Время вычислений = " << time << "\n";// выводим время

	//-----------------------------

	time = omp_get_wtime();// запускаем таймер

	summa = 0;// обнуляем резуьтат
	// выполнение твоего задания без потоков
	for (int i = 0; i < N; i++)
	{
		if (i % 2 == 0)
		{
			summa += a[i];
		}
		else
		{
			summa -= a[i];
		}
	}

	time = omp_get_wtime() - time;// считаем время выполнения
	cout << "Значение выражения без потоков = " << summa << "\n"; // выводим резульат
	cout << "Время вычислений = " << time << "\n";// выводим время выполнения

	//---------------------


	system("pause");
	return 0;
}



