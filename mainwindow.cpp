#include "counting.h"
#include "parser.h"
#include <QSet>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->pushButton_0, SIGNAL(clicked()), this, SLOT(enter()));
    connect(ui->pushButton_1, SIGNAL(clicked()), this, SLOT(enter()));
    connect(ui->pushButton_2, SIGNAL(clicked()), this, SLOT(enter()));
    connect(ui->pushButton_3, SIGNAL(clicked()), this, SLOT(enter()));
    connect(ui->pushButton_4, SIGNAL(clicked()), this, SLOT(enter()));
    connect(ui->pushButton_5, SIGNAL(clicked()), this, SLOT(enter()));
    connect(ui->pushButton_6, SIGNAL(clicked()), this, SLOT(enter()));
    connect(ui->pushButton_7, SIGNAL(clicked()), this, SLOT(enter()));
    connect(ui->pushButton_8, SIGNAL(clicked()), this, SLOT(enter()));
    connect(ui->pushButton_9, SIGNAL(clicked()), this, SLOT(enter()));
    connect(ui->pushButton_pi, SIGNAL(clicked()), this, SLOT(enter()));
    connect(ui->pushButton_plus, SIGNAL(clicked()), this, SLOT(enter()));
    connect(ui->pushButton_minus, SIGNAL(clicked()), this, SLOT(enter()));
    connect(ui->pushButton_div, SIGNAL(clicked()), this, SLOT(enter()));
    connect(ui->pushButton_mult, SIGNAL(clicked()), this, SLOT(enter()));
    connect(ui->pushButton_sqr, SIGNAL(clicked()), this, SLOT(enter()));
    connect(ui->pushButton_sqrt, SIGNAL(clicked()), this, SLOT(enter()));
    connect(ui->pushButton_mod, SIGNAL(clicked()), this, SLOT(enter()));
    connect(ui->openBracket, SIGNAL(clicked()), this, SLOT(enter()));
    connect(ui->closeBracket, SIGNAL(clicked()), this, SLOT(enter()));
    connect(ui->pushButton_percent, SIGNAL(clicked()), this, SLOT(enter()));
    connect(ui->pushButton_dot, SIGNAL(clicked()), this, SLOT(enter()));

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::enter() //ввод строки
{
    QPushButton *button = (QPushButton *)sender();
    if (ui->input_line->text().length() < 34) {
        if ((button->text() != '0' && button->text() != 'x' && button->text() != '/' && button->text() != "mod") ||
                !ui->input_line->text().isEmpty()) {
            if (button->text() == "x") {
                ui->input_line->setText(ui->input_line->text() + "*");
            } else {
                ui->input_line->setText(ui->input_line->text() + button->text());
            }
        }
    }
}



void MainWindow::on_pushButton_del_clicked()
{
    ui->input_line->setText("");
}


void MainWindow::on_pushButton_equal_clicked()
{
    if (!ui->input_line->text().isEmpty()) {
        QString s = ui->input_line->text() + '=';
        Analyzer a;
        if (a.str_test(s, 0)) {
            Alg RPN;

            ui->resultPlace->setText(RPN.count(s));
        } else {
            ui->resultPlace->setText("uncorrect");

        }
    }
}



