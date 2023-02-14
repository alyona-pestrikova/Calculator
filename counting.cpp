#include "counting.h"

struct Priority {
    QString operation;
    int rang;
};

QString get_next_elem(QString& expr) {
    if (!expr.length()) {
        return "";
    }
    if (expr.left(4) == "sqrt") {
        expr = expr.right(expr.length() - 4);
        return "sqrt";
    } else if (expr.left(3) == "sqr" || expr.left(3) == "mod") {
        QString copy = expr.left(3);
        expr = expr.right(expr.length() - 3);
        return copy;
    } else if (expr.left(2) == "pi") {
       expr = expr.right(expr.length() - 2);
        return "pi";
    } else {
        QString oper = "+-/*%=()";
        QString nums = "0123456789.";
        if (oper.contains(expr.left(1))) {
            QString copy = expr.left(1);
            expr = expr.right(expr.length() - 1);
            return copy;
        } else if (nums.contains(expr.left(1))) {
            QString number = "";
            while (nums.contains(expr.left(1))) {
                number += expr.left(1);
                expr = expr.right(expr.length() - 1);
            }
            return number;
        }
    }

    return "";
}

Alg::Alg() {
    p = new Priority[8];
    p[0] = { "+", 1 };
    p[1] = { "-", 1 };
    p[2] = { "*", 3 };
    p[3] = { "/", 3 };
    p[4] = {"mod", 2};
    p[5] = {"sqr", 3};
    p[6] = {"sqrt", 3};
    p[7] = {"%" , 4};
}

Alg::~Alg() {
    delete[] p;
}

int Alg::get_rang(QString a) {
    for (int i = 0; i < 8; i++) {
        if (p[i].operation == a) {
            return p[i].rang;
        }
    }
    return 0;
}

bool Alg::is_num(QString expr) {
    int counter = 0; //счетчик точек
    for (int i = 0; i < expr.length(); i++) {
        if (expr[i] < '0' || expr[i] > '9') {
            if (expr[i] == '.') {
                counter++;
                if (counter > 1) {
                    return false;
                }
            } else {
                return false;
            }
        }
    }
    return true;
}

bool Alg::is_oper(QString expr) {
    if (expr == "sqrt" || expr == "sqr" || expr == "mod" || expr == "%" || expr == "+" || expr == "-" || expr == "*" || expr == "/") {
        return true;
    }
    return false;
}

bool Alg::is_binary(QString oper) {
    if (is_oper(oper)) {
        if (oper == "sqr" || oper == "sqrt" || oper =='%') {
            return false;
        } else {
            return true;
        }
    } else {
        throw "Not operation";
    }
}

QString* Alg::to_rpn(QString exp) { //Преобразование выражения в форму обратной польской записи (RPN)

    if(!exp.length()) {
        return rpn;
    }

    stack <QString> oper_stack;
    QString elem = get_next_elem(exp);
    if (elem == "-") {
        rpn[k++] = "0";
    }

    do {
        if (is_num(elem) || elem == "pi") {
            rpn[k++] = elem;
        } else if (is_oper(elem)) {
            if (oper_stack.empty()) {
                oper_stack.push(elem);
            } else {
                if (get_rang(elem) >  get_rang(oper_stack.top())) {
                    oper_stack.push(elem);
                } else {
                    while (!oper_stack.empty() && get_rang(elem) <= get_rang(oper_stack.top())) {
                        rpn[k++] = oper_stack.top();
                        oper_stack.pop();
                    }
                    oper_stack.push(elem);
                }
            }
        } else if (elem == ')') {
            while (oper_stack.top() != '(') {
                rpn[k++] = oper_stack.top();
                oper_stack.pop();
            }
            oper_stack.pop();
        } else if (elem == '(') {
            oper_stack.push(elem);
            QString qs = get_next_elem(exp);
            if (qs == "-") {
                rpn[k++] = "0";
            }
            exp = qs + exp;
        }
        elem = get_next_elem(exp);
    } while (exp.length());
    while (!oper_stack.empty()) {
        rpn[k++] = oper_stack.top();
        oper_stack.pop();
    }
    return rpn;
}

QString Alg::count(QString torpn) {
    QString* rpn = to_rpn(torpn);
    stack <QString> count_stack;

    for (int i = 0; i < 20; i++) {
        if (rpn[i].isEmpty()) {
            break;
        }
        if (is_num(rpn[i]) || rpn[i] == "pi") {
            count_stack.push(rpn[i]);

        } else if (is_oper(rpn[i])) {

            QString pi_test = count_stack.top();
            double num1;

            if (pi_test == "pi") {
                num1 = M_PI;
            } else {
                num1 = pi_test.toDouble();
            }

            count_stack.pop();

            bool binary = is_binary(rpn[i]);
            double num2;
            if (binary) {
                pi_test = count_stack.top();
                if (pi_test == "pi") {
                    num2 = M_PI;
                } else {
                    num2 = pi_test.toDouble();
                }
                count_stack.pop();
            }

            double res = 0;

            QString op = rpn[i];
            if (binary) {
                if (op == '+') {
                    res = num1 + num2;
                } else if (op == '-') {
                    res = num2 - num1;
                } else if (op == '*') {
                    res = num2 * num1;
                } else if (op == '/') {
                    res = num2 / num1;
                } else if (op == "mod") {
                    res = fmod(num2, num1);
                }
            } else {
                if (op == '%') {
                    res = num1 / 100;
                } else if (op == "sqr") {
                    res = pow(num1, 2);
                } else if (op == "sqrt") {
                    res = sqrt(num1);
                } else {
                    throw "Invalid";
                }
            }
            count_stack.push(QString::number(res));
        }
    }
    return count_stack.top();
}

