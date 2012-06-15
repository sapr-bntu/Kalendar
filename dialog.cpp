#include "dialog.h"
#include "ui_dialog.h"
#include <QtGui>
#include <QtSql>
#include <QRadioButton>
#include <QTimer>
 #include <QToolTip>
#include <qapplication.h>
 #include <qlabel.h>
#include <QMessageBox>



Dialog::Dialog(QWidget *parent) :
        QDialog(parent),
        ui(new Ui::Dialog)
{
    ui->setupUi(this);
    ui->groupBox->hide();

    trIcon = new QSystemTrayIcon();
    trIcon->setIcon(QIcon("icon.png"));
    trIcon->show();
    connect(trIcon,SIGNAL(activated(QSystemTrayIcon::ActivationReason)),this,SLOT(showHide(QSystemTrayIcon::ActivationReason)));
    QFile file("Calendar.s3db") ;
    QSqlDatabase db;
    if (file.exists())
    {

        db = QSqlDatabase::addDatabase("QSQLITE");
        db.setDatabaseName("Calendar.s3db");
        db.open();
        QSqlQuery query;
        query.exec("CREATE TABLE Dannie ("
                   "ID INTEGER  NOT NULL PRIMARY KEY AUTOINCREMENT,"
                   "Data DATE  NULL,"
                   "Vremyanachala TIME  NULL,"
                   "Vremyakonca TIME  NULL,"
                   "Sobitie TEXT  NULL,"
                   "comment TEXT  NULL)");
    }
    else
    {
        db = QSqlDatabase::addDatabase("QSQLITE");
        db.setDatabaseName("Calendar.s3db");
        db.open();

    }
    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(process()));
    timer->start(500);


    model = new QSqlTableModel(this);
    model->setTable("Dannie");
    model->select();
    model->setFilter("");
    ui->tableView1->selectRow(0);
    ui->tableView1->setModel(model);
    //     ui->tableView1->hideColumn(0);
    //ui->tableView1->hideColumn(1);

    QDateTime  finishTime = QDateTime::currentDateTime();

    ui->timeEdit->setTime(QTime(finishTime.time().hour(), 0 ));
    ui->timeEdit_2->setTime(QTime(finishTime.time().hour(), 0 ));
    QDateTime dateTime=QDateTime::currentDateTime();
    ui-> dateEdit->setDate(dateTime.date());
    ui->dateEdit->setDate(dateTime.date());
    connect(ui->tableView1,SIGNAL(clicked(QModelIndex)),this,SLOT(on_cliked(QModelIndex)));

   connect(ui->pushButton_2,SIGNAL(clicked()),this,SLOT(delete1()));
  connect(ui->radioButton,SIGNAL(clicked()),this,SLOT(plu()));

   // connect(ui->pushButton,SIGNAL(clicked()),this, SLOT(on_pushButton_clicked()));

}

Dialog::~Dialog()
{
    delete ui;
}

bool Dialog::on_cliked(QModelIndex index)
{
    qDebug()<<"onclick";
     QString str;

    id= model->record(index.row()).value("ID").toInt();
    currentid = id;
    str = model->record(index.row()).value(1).toString();

    // ui->comment->setText("<span><a href=\"http://m.tut.by/news/economics/259932.html\">Лукашенко не хочет вновь наступать на грабли \"шоковой терапии\" 90-х годов&nbsp;<img src=\"http://img.tyt.by/pda/icon/pda_vpav_vid.gif\" border=\"0\" alt=\"Видео\" width=\"14\" height=\"10\" /></a></span><br>retuieotuio");
return true;
}


bool Dialog::on_pushButton_clicked()
{

    QString text;



    text = ui->textEdit->toPlainText();

    QString comment;

    comment = ui->textEdit_2->toPlainText();
    QTime time;
    time = ui->timeEdit->time();
    QTime time1;
    time1 = ui->timeEdit_2->time();

    QString t=time.toString();
    QString t2=time1.toString();
    QDate date;
    date= ui->calendarWidget->selectedDate();
    QString d=date.toString("yyyy-MM-dd");
    qDebug()<<d;
    QSqlQuery query;

   // qDebug()<<"date"<<date.toString();


   query.exec("INSERT INTO Dannie ( Data, Vremyanachala, Vremyakonca, Sobitie, comment)  VALUES('"+d+"','"+t+"','"+t2+"','"+text+"','"+comment+"')");

    model->select();
    if(ui->radioButton->isChecked())
    {
        QDate dat1 = ui->calendarWidget->selectedDate();
        QDate dat2 = ui->dateEdit->date();

        while (dat2 > dat1)
        {
            QString text;

            text = ui->textEdit->toPlainText();
            QString comment;
            comment = ui->textEdit_2->toPlainText();
            QTime time;
            time = ui->timeEdit->time();
            QTime time1;
            time1 = ui->timeEdit_2->time();
            QString t=time.toString();
            QString t2=time1.toString();
         dat1 = dat1.addDays(1);
         QString dat3 = dat1.toString("yyyy-MM-dd");
            qDebug()<<dat3;
          QSqlQuery query;
         query.exec("INSERT INTO Dannie ( Data, Vremyanachala, Vremyakonca, Sobitie, comment)  VALUES('"+dat3+"','"+t+"','"+t2+"','"+text+"','"+comment+"')");
     model->select();
     }
    }
    if(ui->radioButton_2->isChecked())
    {
        QDate dat1 = ui->calendarWidget->selectedDate();
        QDate dat2 = ui->dateEdit->date();
        while (dat2 > dat1)
        {
            QString text;

            text = ui->textEdit->toPlainText();
            QString comment;
            comment = ui->textEdit_2->toPlainText();
            QTime time;
            time = ui->timeEdit->time();
            QTime time1;
            time1 = ui->timeEdit_2->time();
            QString t=time.toString();
            QString t2=time1.toString();
         dat1 = dat1.addDays(7);
         QString dat3 = dat1.toString("yyyy-MM-dd");
            qDebug()<<dat3;
          QSqlQuery query;
         query.exec("INSERT INTO Dannie ( Data, Vremyanachala, Vremyakonca, Sobitie, comment)  VALUES('"+dat3+"','"+t+"','"+t2+"','"+text+"','"+comment+"')");
     model->select();
     }
    }
    if(ui->radioButton_3->isChecked())
    {
        QDate dat1 = ui->calendarWidget->selectedDate();
        QDate dat2 = ui->dateEdit->date();
        while (dat1 < dat2)
        {
            QString text;

            text = ui->textEdit->toPlainText();
            QString comment;
            comment = ui->textEdit_2->toPlainText();
            QTime time;
            time = ui->timeEdit->time();
            QTime time1;
            time1 = ui->timeEdit_2->time();
            QString t=time.toString();
            QString t2=time1.toString();
         dat1 = dat1.addMonths(1);
         QString dat3 = dat1.toString("yyyy-MM-dd");
            qDebug()<<dat3;
          QSqlQuery query;
         query.exec("INSERT INTO Dannie ( Data, Vremyanachala, Vremyakonca, Sobitie, comment)  VALUES('"+dat3+"','"+t+"','"+t2+"','"+text+"','"+comment+"')");
     model->select();
     }
    }
return true;
}

bool Dialog::delete1()
{
QSqlQuery quer;
qDebug()<<currentid;
quer.exec(QString("DELETE FROM Dannie WHERE ID = '%1'").arg(currentid));
model->select();
return true;
}
bool Dialog::on_calendarWidget_clicked(QDate date)
{
    model ->setFilter(QString("Data = '%1'").arg(date.toString("yyyy-MM-dd")));
    return true;
}

bool Dialog::process ()
{
    qDebug()<<"process";
    QTime time;
    time = ui->timeEdit->time();
     QString tim=time.currentTime().toString();

    QDate date2;

   QString d=date2.currentDate().toString("yyy-MM-dd");

    QSqlQuery quer(QString("SELECT Sobitie FROM Dannie WHERE Data = '%1'").arg(d));
    QSqlQuery quer1(QString("SELECT Vremyanachala,Sobitie FROM Dannie WHERE Data = '%1' AND Vremyanachala = '%2' ").arg(d,tim));
//     QSqlQuery quer1(QString("SELECT Vremyanachala,Sobitie FROM Dannie WHERE Data = '%1' ").arg(d));
     quer1.exec();
    quer.next();
    quer1.next();

    QVariant var1 = quer.value(0);
    QVariant var2 = quer1.value(0);
    qDebug()<<var2.toString();

    if (var2.toString()==tim)
    {
         QMessageBox msgBox;
         msgBox.setText(var2.toString());
         msgBox.exec();
    }

return true;

}

bool Dialog::on_checkBox_stateChanged(int arg1)
{
    if(arg1 == Qt::Unchecked)
    {
        ui->pushButton->hide();
        ui->pushButton_2->hide();
    }
    else
    {
        ui->pushButton->show();
        ui->pushButton_2->show();


    }
    return true;
}
bool Dialog::showHide(QSystemTrayIcon::ActivationReason r)
{
    if (r==QSystemTrayIcon::Trigger)
    if (!this->isVisible()) {
       this->show();
    } else {
       this->hide();
    }
    return true;
}







