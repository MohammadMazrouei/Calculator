#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
	: QMainWindow(parent)
	, ui(new Ui::MainWindow)
{
	ui->setupUi(this);
	on_btn_mod_clicked();
}


MainWindow::~MainWindow()
{
	delete ui;
}


bool MainWindow::valid()
{
	int	n = tmp.size();
	if(n == 0)
		return true;
	int numpar = 0;
	int numau = 0;
	if(tmp[n-1] == '+' || tmp[n-1] == '-' || tmp[n-1] == '*' || tmp[n-1] == '/' || tmp[n-1] == '(' || tmp[n-1] == '^')
		return false;
	for(int i = 0; i < n; i++) {
		if(tmp[i] == '(')
			numpar++;
		if(tmp[i] == ')') {
			if(i != 0 && (tmp[i-1] == '+' || tmp[i-1] == '-' || tmp[i-1] == '*' || tmp[i-1] == '/' || tmp[i-1] == '(' || tmp[i-1] == '^'))
				return false;
			numpar--;
		}
		if(numpar<0)
			return false;
		if(tmp[i] == '.')
			numau++;
		else if(!tmp[i].isDigit())
			numau = 0;
		if(numau == 2)
			return false;
	}
	if(numpar>0)
		return false;

	return true;
}


double MainWindow::comput()
{
	if(tmp.size() == 0)
		return 0;

	QStack<double> nums;
	QStack<QChar> opr;
	QString temp = "";

	for(int i = 0; i < tmp.size(); i++)
	{
		if(tmp[i].isNumber())
		{
			temp = "";
			while(tmp[i].isNumber() || tmp[i] == '.')
			{
				temp += tmp[i];
				if(tmp.size() > i + 1)
					i++;
				else
				{
					i++;
					break;
				}
			}
			nums.push(temp.toDouble());
			i--;
			continue;
		}

		else if(tmp[i] == '(')
			opr.append('(');

		else if(tmp[i] == ')')
		{
			while(opr.top() != '(')
			{
				QChar c = opr.pop();
				double a, b;
				a = nums.pop();
				b = nums.pop();
				switch(c.toLatin1())
				{
					case '*':{
						nums.push(a * b);
						break;
					}
					case '/':{
						nums.push(b / a);
						break;
					}
					case '^':{
						nums.push(pow(b, a));
						 break;
					}
					case '-':{
						nums.push(b - a);
						break;
					}
					case '+':{
						nums.push(b + a);
						break;
					}
				}
			}
			opr.pop();
		}

		else
		{
			int priority = pri(tmp[i]);
			while(!opr.isEmpty() && pri(opr.top()) >= priority)
			{
				if(opr.top() == '^' && tmp[i] == '^')
					break;
				double a, b;
				a = nums.pop();
				b = nums.pop();
				QChar c = opr.pop();
				switch(c.toLatin1()){
					case '*':{
						nums.push(a * b);
						break;
					}
					case '/':{
						nums.push(b / a);
						break;
					}
					case '^':{
						nums.push(pow(b, a));
						 break;
					}
					case '-':{
						nums.push(b - a);
						break;
					}
					case '+':{
						nums.push(b + a);
						break;
					}
				}
			}
			opr.push(tmp[i]);
		}
	}

	while(!opr.isEmpty())
	{
		double a, b;
		QChar c = opr.pop();
		a = nums.pop();
		b = nums.pop();
		switch(c.toLatin1())
		{
			case '*':{
				nums.push(a * b);
				break;
			}
			case '/':{
				nums.push(b / a);
				break;
			}
			case '^':{
				nums.push(pow(b, a));
				 break;
			}
			case '-':{
				nums.push(b - a);
				break;
			}
			case '+':{
				nums.push(b + a);
				break;
			}
		}
	}
	return nums.top();
}


int MainWindow::pri(QChar a)
{
	int pr;
	if(a == '-' || a == '+')
		pr = 1;
	else if(a == '*' || a == '/')
		pr = 2;
	else if(a == '(' || a == ')')
		pr = 0;
	else
		pr = 3;

	return pr;
}


bool MainWindow::parenMatch()
{
	QStack<char> s;
	for(int i = 0; i < tmp.size(); i++){
		if(tmp[i] == '(')
			s.push('(');
		else if(tmp[i] == ')'){
			if(s.isEmpty())
				return false;
			if(s.top() != '(')
				return false;
			s.pop();
		}
		if(s.isEmpty())
			return true;
		else
			return false;
	}
	return true;
}


bool MainWindow::isValid()
{
	int n = tmp.size();
	if(n != 0)
		return tmp[n-1].isNumber() || tmp[n-1] == ')';
	return false;
}


void MainWindow::on_btn_mod_clicked()
{
	mod = !mod;

	// PushButton
	{
		if(mod)  // Darkmod
		{
			ui->btn_0->setStyleSheet("QPushButton{color:#2397e7; background-color:#2e2f35}"
									 "QPushButton:hover{color:#b3daff; background-color:rgb(94, 92, 100)}");
			ui->btn_1->setStyleSheet("QPushButton{color:#2397e7; background-color:#2e2f35}"
									 "QPushButton:hover{color:#b3daff; background-color:rgb(94, 92, 100)}");
			ui->btn_2->setStyleSheet("QPushButton{color:#2397e7; background-color:#2e2f35}"
									 "QPushButton:hover{color:#b3daff; background-color:rgb(94, 92, 100)}");
			ui->btn_3->setStyleSheet("QPushButton{color:#2397e7; background-color:#2e2f35}"
									 "QPushButton:hover{color:#b3daff; background-color:rgb(94, 92, 100)}");
			ui->btn_4->setStyleSheet("QPushButton{color:#2397e7; background-color:#2e2f35}"
									 "QPushButton:hover{color:#b3daff; background-color:rgb(94, 92, 100)}");
			ui->btn_5->setStyleSheet("QPushButton{color:#2397e7; background-color:#2e2f35}"
									 "QPushButton:hover{color:#b3daff; background-color:rgb(94, 92, 100)}");
			ui->btn_6->setStyleSheet("QPushButton{color:#2397e7; background-color:#2e2f35}"
									 "QPushButton:hover{color:#b3daff; background-color:rgb(94, 92, 100)}");
			ui->btn_7->setStyleSheet("QPushButton{color:#2397e7; background-color:#2e2f35}"
									 "QPushButton:hover{color:#b3daff; background-color:rgb(94, 92, 100)}");
			ui->btn_8->setStyleSheet("QPushButton{color:#2397e7; background-color:#2e2f35}"
									 "QPushButton:hover{color:#b3daff; background-color:rgb(94, 92, 100)}");
			ui->btn_9->setStyleSheet("QPushButton{color:#2397e7; background-color:#2e2f35}"
									 "QPushButton:hover{color:#b3daff; background-color:rgb(94, 92, 100)}");
			ui->btn_auditor->setStyleSheet("QPushButton{color:#2397e7; background-color:#2e2f35}"
										   "QPushButton:hover{color:#b3daff; background-color:rgb(94, 92, 100)}");
			ui->btn_clear->setStyleSheet("QPushButton{color:#2397e7; background-color:#2e2f35}"
										 "QPushButton:hover{color:#b3daff; background-color:rgb(94, 92, 100)}");
			ui->btn_reset->setStyleSheet("QPushButton{color:#2397e7; background-color:#2e2f35}"
										 "QPushButton:hover{color:#b3daff; background-color:rgb(94, 92, 100)}");
			ui->btn_openpar->setStyleSheet("QPushButton{color:#2397e7; background-color:#2e2f35}"
										   "QPushButton:hover{color:#b3daff; background-color:rgb(94, 92, 100)}");
			ui->btn_closepar->setStyleSheet("QPushButton{color:#2397e7; background-color:#2e2f35}"
											"QPushButton:hover{color:#b3daff; background-color:rgb(94, 92, 100)}");
			ui->btn_power->setStyleSheet("QPushButton{color:#2397e7; background-color:#2e2f35}"
										 "QPushButton:hover{color:#b3daff; background-color:rgb(94, 92, 100)}");
			ui->btn_mod->setStyleSheet("QPushButton{color:#2397e7; background-color:#2e2f35}"
									   "QPushButton:hover{color:#b3daff; background-color:rgb(94, 92, 100)}");
			ui->btn_equal->setStyleSheet("QPushButton{color:#2397e7; background-color:#005db2}"
									   "QPushButton:hover{color:#b3daff}");
			ui->btn_sum->setStyleSheet("QPushButton{color:#2397e7; background-color:#005db2}"
									   "QPushButton:hover{color:#b3daff}");
			ui->btn_sub->setStyleSheet("QPushButton{color:#2397e7; background-color:#005db2}"
									   "QPushButton:hover{color:#b3daff}");
			ui->btn_mul->setStyleSheet("QPushButton{color:#2397e7; background-color:#005db2}"
									   "QPushButton:hover{color:#b3daff}");
			ui->btn_division->setStyleSheet("QPushButton{color:#2397e7; background-color:#005db2}"
									   "QPushButton:hover{color:#b3daff}");
		}

		else //Lightmod
		{
			ui->btn_0->setStyleSheet("QPushButton{color:#ffffff; background-color:#bed6e7}"
									 "QPushButton:hover{color:#ffffff; background-color:#19acff}");
			ui->btn_1->setStyleSheet("QPushButton{color:#ffffff; background-color:#bed6e7}"
									 "QPushButton:hover{color:#ffffff; background-color:#19acff}");
			ui->btn_2->setStyleSheet("QPushButton{color:#ffffff; background-color:#bed6e7}"
									 "QPushButton:hover{color:#ffffff; background-color:#19acff}");
			ui->btn_3->setStyleSheet("QPushButton{color:#ffffff; background-color:#bed6e7}"
									 "QPushButton:hover{color:#ffffff; background-color:#19acff}");
			ui->btn_4->setStyleSheet("QPushButton{color:#ffffff; background-color:#bed6e7}"
									 "QPushButton:hover{color:#ffffff; background-color:#19acff}");
			ui->btn_5->setStyleSheet("QPushButton{color:#ffffff; background-color:#bed6e7}"
									 "QPushButton:hover{color:#ffffff; background-color:#19acff}");
			ui->btn_6->setStyleSheet("QPushButton{color:#ffffff; background-color:#bed6e7}"
									 "QPushButton:hover{color:#ffffff; background-color:#19acff}");
			ui->btn_7->setStyleSheet("QPushButton{color:#ffffff; background-color:#bed6e7}"
									 "QPushButton:hover{color:#ffffff; background-color:#19acff}");
			ui->btn_8->setStyleSheet("QPushButton{color:#ffffff; background-color:#bed6e7}"
									 "QPushButton:hover{color:#ffffff; background-color:#19acff}");
			ui->btn_9->setStyleSheet("QPushButton{color:#ffffff; background-color:#bed6e7}"
									 "QPushButton:hover{color:#ffffff; background-color:#19acff}");
			ui->btn_auditor->setStyleSheet("QPushButton{color:#ffffff; background-color:#bed6e7}"
									 "QPushButton:hover{color:#ffffff; background-color:#19acff}");
			ui->btn_clear->setStyleSheet("QPushButton{color:#ffffff; background-color:#bed6e7}"
									 "QPushButton:hover{color:#ffffff; background-color:#19acff}");
			ui->btn_reset->setStyleSheet("QPushButton{color:#ffffff; background-color:#bed6e7}"
									 "QPushButton:hover{color:#ffffff; background-color:#19acff}");
			ui->btn_openpar->setStyleSheet("QPushButton{color:#ffffff; background-color:#bed6e7}"
									 "QPushButton:hover{color:#ffffff; background-color:#19acff}");
			ui->btn_closepar->setStyleSheet("QPushButton{color:#ffffff; background-color:#bed6e7}"
									 "QPushButton:hover{color:#ffffff; background-color:#19acff}");
			ui->btn_power->setStyleSheet("QPushButton{color:#ffffff; background-color:#bed6e7}"
									 "QPushButton:hover{color:#ffffff; background-color:#19acff}");
			ui->btn_mod->setStyleSheet("QPushButton{color:#ffffff; background-color:#bed6e7}"
									 "QPushButton:hover{color:#ffffff; background-color:#19acff}");
			ui->btn_equal->setStyleSheet("QPushButton{color:#4999db; background-color:#8bbce3}"
									 "QPushButton:hover{color:#ffffff; background-color:#19acff}");
			ui->btn_sum->setStyleSheet("QPushButton{color:#4999db; background-color:#8bbce3}"
									 "QPushButton:hover{color:#ffffff; background-color:#19acff}");
			ui->btn_sub->setStyleSheet("QPushButton{color:#4999db; background-color:#8bbce3}"
									 "QPushButton:hover{color:#ffffff; background-color:#19acff}");
			ui->btn_mul->setStyleSheet("QPushButton{color:#4999db; background-color:#8bbce3}"
									 "QPushButton:hover{color:#ffffff; background-color:#19acff}");
			ui->btn_division->setStyleSheet("QPushButton{color:#4999db; background-color:#8bbce3}"
									 "QPushButton:hover{color:#ffffff; background-color:#19acff}");
		}
	}

	// PlainTextEdit
	{
		if(mod) // Darkmod
		{
			ui->pte_showexp->setStyleSheet("color:#FFFFFF; background-color:#17181a");
			ui->pte_showres->setStyleSheet("color:#FFFFFF; background-color:#17181a");
		}

		else // Lightmod
		{
			ui->pte_showres->setStyleSheet("color:#000000; background-color:#bde0f9");
			ui->pte_showexp->setStyleSheet("color:#000000; background-color:#bde0f9");
		}
	}

	// MainWindow
	{
		if(mod) // Darkmod
		{
			setStyleSheet("MainWindow{background-color:#17181a} QPushButton{border-radius:14px}");
		}

		else // Lightmod
		{
			setStyleSheet("MainWindow{background-color:#bde0f9} QPushButton{border-radius:14px}");
		}
	}
}


void MainWindow::on_btn_0_clicked()
{
	tmp += '0';
	tmp2 += '0';

	ui->pte_showexp->setPlainText(tmp2);
}


void MainWindow::on_btn_auditor_clicked()
{
	if(!isValid())
	{
		tmp += '0';
		tmp2 += '0';
	}
	tmp += '.';
	tmp2 += '.';
	isauditor = true;

	ui->pte_showexp->setPlainText(tmp2);
}


void MainWindow::on_btn_1_clicked()
{
	tmp += '1';
	tmp2 += '1';

	ui->pte_showexp->setPlainText(tmp2);
}


void MainWindow::on_btn_2_clicked()
{
	tmp += '2';
	tmp2 += '2';

	ui->pte_showexp->setPlainText(tmp2);
}


void MainWindow::on_btn_3_clicked()
{
	tmp += '3';
	tmp2 += '3';

	ui->pte_showexp->setPlainText(tmp2);
}


void MainWindow::on_btn_4_clicked()
{
	tmp += '4';
	tmp2 += '4';

	ui->pte_showexp->setPlainText(tmp2);
}


void MainWindow::on_btn_5_clicked()
{
	tmp += '5';
	tmp2 += '5';

	ui->pte_showexp->setPlainText(tmp2);
}


void MainWindow::on_btn_6_clicked()
{
	tmp += '6';
	tmp2 += '6';

	ui->pte_showexp->setPlainText(tmp2);
}


void MainWindow::on_btn_7_clicked()
{
	tmp += '7';
	tmp2 += '7';

	ui->pte_showexp->setPlainText(tmp2);
}


void MainWindow::on_btn_8_clicked()
{
	tmp += '8';
	tmp2 += '8';

	ui->pte_showexp->setPlainText(tmp2);
}


void MainWindow::on_btn_9_clicked()
{
	tmp += '9';
	tmp2 += '9';

	ui->pte_showexp->setPlainText(tmp2);
}


void MainWindow::on_btn_division_clicked()
{
	if(!isValid())
		return;
	tmp += '/';
	tmp2 += '/';

	ui->pte_showexp->setPlainText(tmp2);
}


void MainWindow::on_btn_mul_clicked()
{
	if(!isValid())
		return;
	tmp += '*';
	tmp2 += '*';

	ui->pte_showexp->setPlainText(tmp2);
}


void MainWindow::on_btn_sub_clicked()
{
	if(tmp.size() != 0 && (tmp[tmp.size()-1] == '+' || tmp[tmp.size()-1] == '-' || tmp[tmp.size()-1] == '*' || tmp[tmp.size()-1] == '/' ||tmp[tmp.size()-1] == '^'))
		return;

	if(tmp.size() == 0)
		tmp += '0';

	if(tmp[tmp.size()-1] == '(')
		tmp += '0';

	if(tmp[tmp.size()-1] == '-')
		return;

	tmp += '-';
	tmp2 += '-';

	ui->pte_showexp->setPlainText(tmp2);
}


void MainWindow::on_btn_sum_clicked()
{
	if(!isValid())
		return;
	tmp += '+';
	tmp2 += '+';

	ui->pte_showexp->setPlainText(tmp2);
}


void MainWindow::on_btn_power_clicked()
{
	if(!isValid())
		return;
	tmp += '^';
	tmp2 += '^';

	ui->pte_showexp->setPlainText(tmp2);
}


void MainWindow::on_btn_clear_clicked()
{
	QString t, t2;
	int n = tmp.size();
	int n2 = tmp2.size();
	for(int i = 0; i < n-1; i++)
		t[i] = tmp[i];
	for(int i = 0; i < n2-1; i++)
		t2[i] = tmp2[i];

	tmp.clear();
	tmp2.clear();
	tmp = t;
	tmp2 = t2;

	ui->pte_showexp->setPlainText(tmp2);
}


void MainWindow::on_btn_reset_clicked()
{
	tmp.clear();
	tmp2.clear();

	ui->pte_showexp->setPlainText(tmp2);
	ui->pte_showres->setPlainText(tmp2);
}


void MainWindow::on_btn_openpar_clicked()
{
	if(tmp.size() > 0 && tmp[tmp.size()-1].isDigit())
		tmp += "*";
	tmp += '(';
	tmp2 += '(';
	ui->pte_showexp->setPlainText(tmp2);
}


void MainWindow::on_btn_closepar_clicked()
{
	tmp += ')';
	tmp2 += ')';
	ui->pte_showexp->setPlainText(tmp2);
}


void MainWindow::on_btn_equal_clicked()
{
	if(valid())
		ui->pte_showres->setPlainText(QString::number(comput()));
	else
		ui->pte_showres->setPlainText("Unvalid");
}
