#include <iostream>
#include <string>
using namespace std;

// Функция проверки корректности ввода
bool isValidNumber(const string& number) {
    for (char ch : number) { //проходится по каждому знаку в number
        if (!isdigit(ch)) return false; //если хоть один знак не цифра 0-9 = false
    }
    return number.length() > 10;
}

// Функция деления строки на целое число с вычислением остатка используется внутри factorize 
void delenie(string number, int del, string& result, int& ostatok) {
    result.clear();  // Очищаем строку перед использованием
    ostatok = 0;

    //по сути принцип деления столбиком. если есть остатот то его умножем на 10 и прибавляем след. разряд
    for (char digit : number) {  //берет цифру из number 
        int current = ostatok * 10 + (digit - '0');  // (digit - '0') переводит digit из строки в число
        result += (current / del) + '0';
        ostatok = current % del;
    }

    // Удаление лишних нулей
    size_t pos = result.find_first_not_of('0'); //находит индекс первого символа != 0 
    if (pos == string::npos) result = "0";  //если все символы 0 - возвращает 0
    else result = result.substr(pos);  //удаляет все незначащие нули 
}

// Функция для разложения числа на простые множители
void factorize(string number) {
    cout << "Простые множители числа " << number << ": ";

    string quotient;
    int ostatok = 0;

    // Делим на 2, пока возможно
    while (true) {
        delenie(number, 2, quotient, ostatok);
        if (ostatok == 0) {
            cout << "2 ";
            number = quotient;
        }
        else {
            break;
        }
    }

    // Перебираем нечётные делители
    int del = 3;
    while (number != "1") {
        delenie(number, del, quotient, ostatok);
        if (ostatok == 0) {
            cout << del << " ";
            number = quotient;
        }
        else {
            del += 2;  // Переход к следующему нечётному числу
        }
    }
    cout << endl;
}

// Основная программа
int main() {
    setlocale(LC_ALL, "Russian");

    string number;
    cout << "Введите натуральное число (более 10 знаков): ";
    cin >> number;

    // Проверка на корректность ввода
    while (!isValidNumber(number)) {
        cout << "Ошибка! Введите корректное натуральное число: ";
        cin >> number;
    }

    // Вызов функции разложения на множители
    factorize(number);
    return 0;
}

