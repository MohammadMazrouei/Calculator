#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStack>
#include <QtMath>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
	Q_OBJECT

public:
	MainWindow(QWidget *parent = nullptr);
	~MainWindow();

private slots:
	void on_btn_mod_clicked();

	void on_btn_0_clicked();

	void on_btn_auditor_clicked();

	double comput();

	void on_btn_1_clicked();

	void on_btn_2_clicked();

	void on_btn_3_clicked();

	void on_btn_4_clicked();

	void on_btn_5_clicked();

	void on_btn_6_clicked();

	void on_btn_7_clicked();

	void on_btn_8_clicked();

	void on_btn_9_clicked();

	void on_btn_clear_clicked();

	void on_btn_division_clicked();

	void on_btn_mul_clicked();

	void on_btn_sub_clicked();

	void on_btn_sum_clicked();

	bool isValid();

	bool parenMatch();

	int pri(QChar a);

	bool valid();

	void on_btn_power_clicked();

	void on_btn_reset_clicked();

	void on_btn_openpar_clicked();

	void on_btn_closepar_clicked();

	void on_btn_equal_clicked();

private:
	Ui::MainWindow *ui;
	bool mod = false;
	bool isauditor = false;
	QString tmp = "";
	QString tmp2 = "";
};
#endif // MAINWINDOW_H
