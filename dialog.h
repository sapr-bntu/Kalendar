#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QtSql>
#include <QSystemTrayIcon>

namespace Ui {
    class Dialog;

}
class QSqlTableModel;
class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = 0);
    ~Dialog();
    QModelIndex index;
       int curentIndex;

private:
    QSystemTrayIcon *trIcon;
    Ui::Dialog *ui;
    QSqlTableModel *model;
    int currentid;
    int id;

public slots:



   bool on_calendarWidget_clicked(QDate date);
   bool on_cliked (QModelIndex index );
    bool on_pushButton_clicked();

      bool delete1();
      bool on_checkBox_stateChanged(int arg1);
      //

      bool showHide(QSystemTrayIcon::ActivationReason);
      bool process();




};

#endif // DIALOG_H
