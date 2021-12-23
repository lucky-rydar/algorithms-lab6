#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
	srand(time(0));

	ui->pushButton_2->setEnabled(false);
	ui->pushButton_3->setEnabled(false);
	ui->aiLogsEdit->setReadOnly(true);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_clicked() // drop button
{
	auto dices = gs_player.drop();
	ui->label_5->setText(QString::number(dices.first));
	ui->label_6->setText(QString::number(dices.second));

	if(!gs_player.dropAvailable()){
		ui->pushButton_2->setEnabled(true);
		ui->pushButton->setEnabled(false);
	}

	ui->label_6->setText(QString::number(dices.first));
	ui->label_5->setText(QString::number(dices.second));

	updateFront();
}


void MainWindow::on_pushButton_2_clicked() // get button
{
	Operation op = Multiple;
	Number num = Two;

	// operation
	if(ui->radioButton->isChecked()) {
		op = Operation::Multiple;
	} else if(ui->radioButton_2->isChecked()) {
		op = Operation::Divide;
	}

	// number
	if(ui->radioButton_5->isChecked()) {
		num = Number::Two;
	} else if(ui->radioButton_4->isChecked()) {
		num = Number::Three;
	} else if(ui->radioButton_3->isChecked()) {
		num = Number::Four;
	}

	gs_player.chooseOption(op, num);

	ui->pushButton_2->setEnabled(false);
	if(gs_player.m_moves == 0) {
		ui->pushButton->setEnabled(false);
		ui->pushButton_3->setEnabled(true);
	}
	else
		ui->pushButton->setEnabled(true);

	updateFront();
}


void MainWindow::on_pushButton_3_clicked() // ai turn button
{
	int moves = gs_ai.m_moves;
	for(int i = 0; i < moves/2; i++)
	{
		Ai::Step doneStep;
		doneStep = Ai::doNextStep(gs_ai);
		gs_ai.chooseOption(doneStep.move.op, doneStep.move.num);

		ui->label_4->setText(QString::number(gs_ai.m_score));
		ui->label_10->setText(QString::number(gs_ai.m_points));

		QString firstDrop = QString::number(doneStep.fisrtDrop.first) + " " + QString::number(doneStep.fisrtDrop.second);
		QString secondDrop = QString::number(doneStep.secondDrop.first) + " " + QString::number(doneStep.secondDrop.second);

		Operation op = doneStep.move.op;
		QString opStr = (op == Multiple ? "*" : "/");
		QString numStr = QString::number(int(doneStep.move.num));
		ui->aiLogsEdit->append("drop1: " + firstDrop + " drop2: " + secondDrop + " op: " + opStr + numStr + "\n");
	}

	ui->pushButton_3->setEnabled(false);

	runCompareResults();
}

void MainWindow::updateFront()
{
	ui->label_2->setText(QString::number(gs_player.m_score)); // score
	ui->label_8->setText(QString::number(gs_player.m_points)); // points
	ui->label_12->setText(QString::number(gs_player.m_moves)); // moves
}

void MainWindow::runCompareResults()
{
	QMessageBox::information(this, "Game end", gs_player.m_points > gs_ai.m_points ? "Player won" : (gs_player.m_points < gs_ai.m_points) ? "Ai won" : "Equal points");
}

