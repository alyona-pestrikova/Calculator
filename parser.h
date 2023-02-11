#ifndef PARSER_H
#define PARSER_H


#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>

using namespace std;

/*
В Transition описаны все возможные следующие значения для каждого элемента - числа или операции,
а также указана информация о том, является ли данный элемент откр. или закр. скобкой или символом "=" - окончанием выражения.
*/
struct Transition;

class Analyzer
{
private:
    int depth; //для проверки равенства количества откр. и закр. скобок
    int state;
    Transition** state_list;
    int* state_list_length;
    void init_state_list();
public:
    Analyzer();
    ~Analyzer();
    bool next_state(QString s); //проверка корректности следующего символа
    bool str_test(QString s, int* pos); //проверка строки на корректность

};

#endif // PARSER_H
