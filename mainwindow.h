#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

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
    void clicked_home();

    void on_one_clicked();

    void on_two_clicked();

    void on_three_clicked();

    void on_four_clicked();

    void on_five_clicked();

    void on_six_clicked();

    void on_seven_clicked();

    void on_eight_clicked();

    void on_nine_clicked();

    void on_diamond_clicked();

    void on_zero_clicked();

    void on_ddiamond_clicked();

    void on_vodown_clicked();

    void on_volup_clicked();

    void on_mute_clicked();

    void on_recall_clicked();

    void on_chdown_clicked();

    void on_chup_clicked();

    void buttonClick(QString buttonName);

    void on_rwd_pressed();

    void on_rwd_released();

    void on_ffd_pressed();

    void on_ffd_released();

    void on_play_clicked();

    void on_back_clicked();

    void on_info_clicked();

    void on_down_clicked();

    void on_left_clicked();

    void on_right_clicked();

    void on_select_clicked();

    void on_options_clicked();

    void on_up_clicked();

    void on_voice_clicked();

    void on_dvr_clicked();

    void on_guide_clicked();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
