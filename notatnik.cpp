#include "notatnik.h"
#include "ui_notatnik.h"
#include <qDebug>
#include <QMessageBox>
#include <tab.h>

notatnik::notatnik(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::notatnik)
{

    ui->setupUi(this);
    ui->bold->setCheckable(true);
    how_card=1;
    creatNewTab(createTabName(&how_card));
    QObject::connect(ui->actionsave,SIGNAL(triggered()),this,SLOT(save()));
    QObject::connect(ui->actionopen,SIGNAL(triggered()),this,SLOT(open()));
}

notatnik::~notatnik()
{
    delete ui;
}

void notatnik::creatNewTab(const QString &title)
{
    Tab *obiekt=new Tab;
    ui->tabWidget->addTab(obiekt, title);
    ui->tabWidget->setCurrentWidget(obiekt);
    obiekt->setWindowTitle(title);
}
QString notatnik::createTabName(int *how_card)
{
    QString nowy = QString::number(*how_card);
    QString value = "Nowy ";
    value.append(nowy);
    *how_card+=1;
    return value;
}
void notatnik::on_actionnew_triggered()
{
    creatNewTab(createTabName(&how_card));
}
void notatnik::save()
{
    //preparation for saving
    int index = ui->tabWidget->currentIndex();
    if(index == -1 ) return;
    fileName="nowy ";
    QString nowy = QString::number(index+1);
    fileName.append(nowy);
    QString path=QDir::currentPath();
    path.append("/");
    path.append(fileName);
    QString filters("Pliki tekstowe (*.txt)");
    fileName=QFileDialog::getSaveFileName(this,"Zapis pliku",path,filters);
    //saving
    QFile file(fileName);
    if(!file.open(QFile::WriteOnly | QFile::Text))
    {
        qDebug() <<"nie można odtowrzyć pliku do zapisu";
        return;
    }
    QTextStream out(&file);
    Tab *pointer =dynamic_cast<Tab *>(ui->tabWidget->widget(index));
    out<<pointer->getText();
    QFileInfo fileInfo(file);
    fileName=fileInfo.fileName();
    file.flush();
    file.close();
    //changing the names of file
    ui->tabWidget->setTabText(index,fileName);
    pointer->save();
}
void notatnik::on_tabWidget_tabCloseRequested(int index)
{
    Tab *pointer =dynamic_cast<Tab *>(ui->tabWidget->widget(index));
    bool isEdited=pointer->isEditedPublic();
    if(isEdited==true)
    {
        QMessageBox msgBox;
        msgBox.setText("Dokument został zmodyfikowany");
        msgBox.setInformativeText("Nie zapisałeś pliku, czy na pewno chcesz zamknąć okno?");
        msgBox.setStandardButtons(QMessageBox::Yes |QMessageBox::No |QMessageBox::Cancel);
        int ret = msgBox.exec();
        switch(ret)
        {
        case QMessageBox::Yes:
            qDebug()<<how_card;
            ui->tabWidget->removeTab(index);
            delete(pointer);
            how_card-=1;
            break;
        case QMessageBox::No:
            save();
            if(pointer->isEditedPublic()!=true)
                ui->tabWidget->removeTab(index);
            how_card-=1;
            delete(pointer);
            break;
        case QMessageBox::Cancel:
            return;
        }
    }
    else
    {
        ui->tabWidget->removeTab(index);
        delete(pointer);
        how_card-=1;
    }
}
void notatnik::open()
{
    QString path=QFileDialog::getOpenFileName(this,"Otwieranie Pliku",QDir::currentPath(), "Pliki tekstowe (*.txt);;Wszystkie pliki(*.*)");
    QFile file(path);
    if(!file.open(QIODevice::ReadOnly|QFile::Text))
    {
        return;
    }
    //create new card
    on_actionnew_triggered();
    int index = ui->tabWidget->currentIndex();
    Tab *pointer =dynamic_cast<Tab *>(ui->tabWidget->widget(index));
    QFileInfo fileInfo(file);
    fileName=fileInfo.fileName();
    //set name of card
    ui->tabWidget->setTabText(index,fileName);
    QTextStream in(&file);
    while(!in.atEnd())
    {
        QString line=in.readAll();
        pointer->set_text(line);

    }
    file.close();
}
void notatnik::closeEvent(QCloseEvent *event)
{
    Tab *pointer;
    int i;
    for(int i=0;i<ui->tabWidget->count();i++)
    {
        pointer=dynamic_cast<Tab *>(ui->tabWidget->widget(i));
        if(pointer->isEditedPublic()==true)
        {
            QMessageBox msgBox;
            msgBox.setText("Dokument został zmodyfikowany");
            msgBox.setInformativeText("Nie zapisałeś pliku, czy na pewno wyjść, bez zapisywania?");
            msgBox.setStandardButtons(QMessageBox::Yes |QMessageBox::No |QMessageBox::Cancel);
            int ret = msgBox.exec();
            switch(ret)
            {
            case QMessageBox::Yes:
                event->accept();
                return;
            case QMessageBox::No:
                for(;i<ui->tabWidget->count();i++)
                {
                    pointer=dynamic_cast<Tab *>(ui->tabWidget->widget(i));
                    if(pointer->isEditedPublic()==true)
                    {
                        ui->tabWidget->setCurrentWidget(pointer);
                        save();
                    }
                }
                break;
            case QMessageBox::Cancel:
                return;
            }
        }
    }
}

void notatnik::on_bold_triggered()
{
    int index = ui->tabWidget->currentIndex();
    Tab *pointer =dynamic_cast<Tab *>(ui->tabWidget->widget(index));
    pointer->setBold();
}

void notatnik::on_italic_triggered()
{
    int index = ui->tabWidget->currentIndex();
    Tab *pointer =dynamic_cast<Tab *>(ui->tabWidget->widget(index));
    pointer->setItalic();
}

void notatnik::on_underline_triggered()
{
    int index = ui->tabWidget->currentIndex();
    Tab *pointer =dynamic_cast<Tab *>(ui->tabWidget->widget(index));
    pointer->setUnderline();
}
