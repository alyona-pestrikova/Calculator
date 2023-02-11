#ifndef COUNTING_H
#define COUNTING_H

#pragma once

#include <stack>
#include <QString>
#include <cmath>

using namespace std;

struct Priority;

/*метод get_next_elem возвращает первый по порядку элемент арифметического выражения:
число, арифметическую операцию или скобку.
При этом из исходного выражения убирается этот первый элемент.*/
QString get_next_elem(QString& expr);

class Alg {
private:
    Priority* p;
    QString rpn[20];
    int k = 0;
    int get_rang(QString a);
    bool is_num(QString expr);
    bool is_oper(QString expr);
    bool is_binary(QString oper); //проверка операторов на бинарность / унарность
    QString* to_rpn(QString exp); //выражение, приведенное к виду обратной польской записи
public:
    Alg();
    ~Alg();
    QString count(QString torpn); //вычисления
};

#endif // COUNTING_H
