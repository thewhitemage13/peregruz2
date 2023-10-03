#include "Mazex.h"

int main()
{
	System("title Maze");
	Console();
	srand(time(0)); // запуск алгоритма генерации СЧ

	const int width = 60; // ширина лабиринта
	const int height = 15; // высота лабиринта
	int maze[height][width] = {}; // заготовка для лабиринта в виде двумерного массива, заполненного нулями
	int two = 0;//создал переменную для посчета кол-ва монет 

	for (int y = 0; y < height; y++)
	{
		for (int x = 0; x < width; x++)
		{
			maze[y][x] = rand() % 5; // 0 1 2 3

			// установка стен по бокам (делаем рамки)
			if (x == 0 || y == 0 || x == width - 1 || y == height - 1)
				maze[y][x] = 1; // стенка слева

			// определение точки входа и выхода из лабиринта
			if (x == 0 && y == 2 || x == 1 && y == 2 || x == 2 && y == 2 ||
				x == width - 1 && y == height - 3)
				maze[y][x] = 0;

			// если текущий элемент 2д-массива - это враг,
			// то ниже код, который уменьшает их количество
			// условно, произойдёт жеребьёвка (или же подбрасывание монетки)

			if (maze[y][x] == 3)
			{
				int r = rand() % 10; // 0...9
				// если выпадает 0 - враг остаётся (10% случаев)
				if (r != 0) // если выпадает не 0 (а число от 1 до 9) - врага убираем (вероятность 90%)
				{
					maze[y][x] = 0; // убираем врага
				}
			}
			if (maze[y][x] == 4)
			{
				int a = rand() % 10; // 0...9
				// если выпадает 0 - аптечка остаётся (10% случаев)
				if (a != 0) // если выпадает не 0 (а число от 1 до 9) - врага убираем (вероятность 90%)
				{
					maze[y][x] = 0; // убираем аптечку 
				}
			}
			if (maze[y][x] == 2)
			{
				two++;//считаем кол-во монет на карте
			}
			if (maze[y][x] == 0)//коридор
			{
				SetCursor(x,y,0, " ");
			}
			else if (maze[y][x] == 1)//стена
			{
				SetCursor(x,y,3, "");
				cout << (char)178;
			}
			else if (maze[y][x] == 2)//монетки
			{
				SetCursor(x,y,14, ".");
			}
			else if (maze[y][x] == 3)//враг
			{
				SetCursor(x,y,12, "");
				cout << (char)1;
			}
			else if (maze[y][x] == 4)//аптечка
			{
				SetCursor(x,y,9, "+");
			}
			else
			{
				cout << maze[y][x];
			}
		}
		cout << "\n";
	}

	COORD position;
	position.X = 0;
	position.Y = 2;

	SetCursor(0, 2, 13, "");

	int coins = 0;
	int health = 100;
	int health2 = 100;
	int money = two;

	cout << (char)1;
	// начинаем интерактив (польщователь управляет смайликом с помощью клавиатуры)
	while (true)
	{
		int code = _getch(); // get character - получение кода нажатой клавиши
		if (code == 224) // если была нажата какая-то стрелка
		{
			code = _getch();
		}
		SetCursor(position.X, position.Y, 0, " ");
		if (code == 77 and maze[position.Y][position.X + 1] != 1) // right
		{
			position.X++; // изменение позиции ГГ вправо на 1 по иксу
		}
		else if (code == 75 and maze[position.Y][position.X - 1] != 1)
		{
			position.X--;
		}
		else if (code == 72 and maze[position.Y - 1][position.X] != 1)
		{
			position.Y--;
		}
		else if (code == 80 and maze[position.Y + 1][position.X] != 1)
		{
			position.Y++;
		}

		SetCursor(position.X, position.Y, 13, "");
		cout << (char)1;

		COORD money_info;
		money_info.X = width + 1;
		money_info.Y = 1;
		SetConsoleCursorPosition(h, money_info); // установка курсора в новые координаты
		SetConsoleTextAttribute(h, 10);
		cout << "The number of coins in the gaim : " << money;

		if (position.X == width - 1 and position.Y == height - 3)
		{
			MessageBoxA(0, "You found your way out of the maze!!!!", "You win!!!", MB_OK);
			break;
		}

		if (maze[position.Y][position.X] == 2)
		{
			coins++;
			maze[position.Y][position.X] = 0;
			COORD coins_info;
			coins_info.X = width + 1;
			coins_info.Y = 2;

			SetConsoleCursorPosition(h, coins_info); // установка курсора в новые координаты
			SetConsoleTextAttribute(h, 14);
			cout << "Number of coins picked up: " << coins;

		}

		if (coins == two)//если мы собрали все монеты,то игра заканчивается выигрышом
		{
			Message("You have collected all the coins!!! ", "You win!!!");
			break;
		}

		if (maze[position.Y][position.X] == 3)
		{
			health -= 20;
			maze[position.Y][position.X] = 0;
			COORD health_info;

			health_info.X = width + 1;
			health_info.Y = 3;
			SetConsoleCursorPosition(h, health_info); // установка курсора в новые координаты
			SetConsoleTextAttribute(h, 13);
			cout << "Hit points: " << health;
			cout << endl;
		}

		if (maze[position.Y][position.X] == 4 and health < 100)
		{
			health += 20;
			maze[position.Y][position.X] = 0;
			COORD health_info;
			health_info.X = width + 1;
			health_info.Y = 3;
			SetConsoleCursorPosition(h, health_info); // установка курсора в новые координаты
			SetConsoleTextAttribute(h, 13);
			cout << "Hit points: " << health;
			cout << " ";
		}

		if (health == 0)
		{
			Message("You have run out of health!!!!", "You are dead!!!!");
			break;
		}
	}
	Finish();
}