#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "dbmanager.h"
#include "authenticate.h"

#include <QMainWindow>
#include <QTableView>

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
    void on_logInPushButton_released();

    void on_pushButton_released();

    void on_clearPushButton_released();

    void on_comboBox_currentIndexChanged(const QString &arg1);

private:
    Ui::MainWindow *ui;

    QAbstractItemModel *memberModel;
    QAbstractItemModel *salesModel;

    QTableView *memberView;
    QTableView *salesView;

    QSortFilterProxyModel *memberProxyModel;
    QSortFilterProxyModel *salesProxyModel;

    DbManager connection;  /// @var connection DbManager object
    Authenticate logInput; /// @var logInput Authenticate object to keep track of user's login status
};
#endif // MAINWINDOW_H
