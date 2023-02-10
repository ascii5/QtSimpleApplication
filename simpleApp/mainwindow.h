#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QWidget>
#include <QDialog>
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
public slots:
    void shapChanged(void);
    void penChanged(void);
    void onBtnPenColorClicked(void);
    void onBtnBrushColorClicked(void);
    void brushChanged(void);
    void antialiasingChange(void);
    void transformationChanged(void);
private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
