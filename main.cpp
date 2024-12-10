#include <iostream>
#include <cstdlib>
#include <ctime>
#include <limits>
#include <windows.h>

using namespace std;

class CasinoGame {
private:
    int balance;  // Баланс игрока
    int winningNumber;  // Случайное число для угадывания

public:

    CasinoGame(int initialBalance) {
        balance = initialBalance;
        srand(time(0));  // Инициализация генератора случайных чисел
    }

    // Метод для запуска игры
    void playGame() {
        cout << "Добро пожаловать в игру Казино! Ваш начальный баланс: $" << balance << endl;

        while (balance > 0) {  // Игра продолжается, пока есть деньги
            int bet;
            cout << "Введите ставку (или 0 для выхода): $";

            // Проверка, что ставка - это число
            while (!(cin >> bet) || bet < 0) {
                cout << "Некорректный ввод! Пожалуйста, введите положительное число или 0 для выхода: $";
                cin.clear();  // Сбрасываем ошибку
                cin.ignore(numeric_limits<streamsize>::max(), '\n');  // Очищаем остатки ввода
            }

            if (bet == 0) {
                cout << "Выход из игры. Ваш баланс: $" << balance << endl;
                break;
            }

            if (bet > balance) {
                cout << "Недостаточно средств! Попробуйте снова." << endl;
                continue;
            }

            // Генерация случайного числа от 1 до 10
            winningNumber = rand() % 10 + 1;
            int guess;
            cout << "Угадайте число от 1 до 10: ";

            // Проверка, что ввод числа
            while (!(cin >> guess) || guess < 1 || guess > 10) {
                cout << "Некорректный ввод! Пожалуйста, введите число от 1 до 10: ";
                cin.clear();  // Сбрасываем ошибку
                cin.ignore(numeric_limits<streamsize>::max(), '\n');  // Очищаем остатки ввода
            }

            // Проверка результата
            if (guess == winningNumber) {
                cout << "Поздравляем! Вы угадали число. Ваш выигрыш: $" << bet * 2 << endl;
                balance += bet * 2;  // Удваиваем ставку в случае победы
            } else {
                cout << "Вы не угадали! Загаданное число было: " << winningNumber << endl;
                balance -= bet;  // Списываем ставку в случае проигрыша
            }

            cout << "Ваш текущий баланс: $" << balance << endl;
        }

        if (balance <= 0) {
            cout << "У вас закончились деньги! Игра окончена." << endl;
        }
    }
};

int main() {
    SetConsoleOutputCP(65001);  // Устанавливаем кодировку в консоли Windows
    setlocale(LC_ALL, "ru_RU.UTF-8");  // Устанавливаем русскую локаль

    int startingBalance;

    cout << "Введите начальный баланс для игры: $";

    // Проверка на корректный ввод начального баланса
    while (!(cin >> startingBalance) || startingBalance <= 0) {
        cout << "Некорректный ввод! Пожалуйста, введите положительное число: $";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');  // Очищаем остатки ввода
    }

    // Создаем объект игры и запускаем ее
    CasinoGame game(startingBalance);
    game.playGame();

    return 0;
}
