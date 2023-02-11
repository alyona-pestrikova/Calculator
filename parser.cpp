#include "parser.h"

struct Transition {
    QString c;
    int state;
    int depthDelta;
    bool zeroTest;
};

void Analyzer::init_state_list() {
    state_list_length = new int[12];
    state_list = new Transition * [12];

    state_list_length[0] = 6; //проверка корректности начала строки
    state_list[0] = new Transition[6]{
        {"0123456789", 1, 0, false},
        {"(", 4, 1, false},
        {"sqr", 8, 0, false},
        {"sqrt", 9, 0, false},
        {"pi", 7, 0, false},
        {"+-", 2, 0, false}
    };

    state_list_length[1] = 8; //0...9
    state_list[1] = new Transition[8]{
        {"0123456789", 1, 0, false},
        {"+-", 2, 0, false},
        {"=", 12, 0, true},
        {"x/", 3, 0, false},
        {")", 5, -1, false},
        {"mod", 6, 0, false},
        {".", 10, 0, false},
        {"%", 11, 0, false}
    };

    state_list_length[2] = 5; //+,-
    state_list[2] = new Transition[5]{
        {"0123456789", 1, 0, false},
        {"(", 4, 1, false},
        {"pi", 7, 0, false},
        {"sqr", 8, 0, false},
        {"sqrt", 9, 0, false}
    };

    state_list_length[3] = 5; //*,/
    state_list[3] = new Transition[5]{
        {"0123456789", 1, 0, false},
        {"(", 4, 1, false},
        {"pi", 7, 0, false},
        {"sqr", 8, 0, false},
        {"sqrt", 9, 0, false}
    };

    state_list_length[4] = 6; //(
    state_list[4] = new Transition[6]{
        {"0123456789", 1, 0, false},
        {"(", 4, 1, false},
        {"+-", 2, 0, false},
        {"pi", 7, 0, false},
        {"sqr", 8, 0, false},
        {"sqrt", 9, 0, false}
    };

    state_list_length[5] = 6; //)
    state_list[5] = new Transition[6]{
        {")", 5, -1, false},
        {"+-", 2, 0, false},
        {"=", 12, 0, true},
        {"x/", 3, 0, false},
        {"mod", 6, 0, false},
        {"%", 11, 0, false}
    };

    state_list_length[6] = 5; //mod
    state_list[6] = new Transition[5]{
        {"0123456789", 1, 0, false},
        {"(", 4, 1, false},
        {"pi", 7, 0, false},
        {"sqr", 8, 0, false},
        {"sqrt", 9, 0, false}
    };

    state_list_length[7] = 6; //pi
    state_list[7] = new Transition[6]{
        {")", 5, -1, false},
        {"+-", 2, 0, false},
        {"=", 12, 0, true},
        {"x/", 3, 0, false},
        {"mod", 6, 0, false},
        {"%", 11, 0, false}
    };

    state_list_length[8] = 5; //sqr
    state_list[8] = new Transition[5]{
        {"0123456789", 1, 0, false},
        {"(", 4, 1, false},
        {"pi", 7, 0, false},
        {"sqr", 8, 0, false},
        {"sqrt", 9, 0, false}
    };

    state_list_length[9] = 5; //sqrt
    state_list[9] = new Transition[5]{
        {"0123456789", 1, 0, false},
        {"(", 4, 1, false},
        {"pi", 7, 0, false},
        {"sqr", 8, 0, false},
        {"sqrt", 9, 0, false}
    };

    state_list_length[10] = 1; //.
    state_list[10] = new Transition[1]{
        {"0123456789", 1, 0, false}
    };

    state_list_length[11] = 5; //%
    state_list[11] = new Transition[5]{
        {")", 5, -1, false},
        {"+-", 2, 0, false},
        {"=", 12, 0, true},
        {"x/", 3, 0, false},
        {"mod", 6, 0, false}
    };
}

Analyzer::Analyzer() {
    depth = 0;
    state = 0;
    init_state_list();
}

Analyzer::~Analyzer() {
    for (int i = 0; i < 12; i++) {
        delete [] state_list[i];
    }
    delete [] state_list;
    delete [] state_list_length;
}

bool Analyzer::next_state(QString s) {
    for (int i = 0; i < state_list_length[state]; i++) {
        if (state_list[state][i].c.contains(s)) {
            depth += state_list[state][i].depthDelta;
            if (depth < 0) {
                return false;
            }
            if (state_list[state][i].zeroTest && depth > 0) {

                return false;
            }
            state = state_list[state][i].state;
            return true;
        }
    }
    return false;
}

bool Analyzer::str_test(QString s, int *pos) {
    if (!s.length()) {
        *pos = -1;
        return false;
    }

    while(s.length() > 0) {
        if (s.left(4) == "sqrt") {
            if (!next_state(s.left(4))) {
                return false;
            }
            s = s.right(s.length() - 4);
        } else if (s.left(3) == "sqr" || s.left(3) == "mod") {
            if (!next_state(s.left(3))) {
                return false;
            }
            s = s.right(s.length() - 3);
        } else if (s.left(2) == "pi") {
            if (!next_state(s.left(2))) {
                return false;
            }
            s = s.right(s.length() - 2);
        } else {
            QChar c = s[0];
            if ((c >= '0' && c <= '9') || c == '+' || c == '-' || c == 'x' || c == '/' || c == '%' || c == '=' || c == '.' || c == '(' || c == ')') {
                if (!next_state(s.left(1))) {
                    qDebug() << "ERR " << c;
                    return false;
                }
                s = s.right(s.length() - 1);
            } else {
                return false;
            }
        }
    }
    return true;
}
