#include "tab.h"
#include "ui_tab.h"
#include <QMessageBox>
#include <QMainWindow>
#include <QDebug>
Tab::Tab(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Tab)
{
    ui->setupUi(this);
    edited=false;
    QObject::connect(ui->textFied,SIGNAL(textChanged()),this,SLOT(isEdited()));
}

Tab::~Tab()
{
    delete ui;
}
void Tab::isEdited()
{
    edited=true;
}
void Tab::save()
{
    edited=false;
}
bool Tab::isEditedPublic()
{
    return edited;
}
QString Tab::getText()
{
    return ui->textFied->toPlainText();
}
void Tab::set_text(QString tekst)
{
    QTextCursor text_cursor;
    ui->textFied->setPlainText(tekst);
    text_cursor.movePosition(QTextCursor::End);
}
void Tab::setBold()
{
    QTextCharFormat format;
    QTextCursor cursor=ui->textFied->textCursor();
    int StartPos,EndPos;

    StartPos=cursor.selectionStart();
    EndPos=cursor.selectionEnd();

    cursor.setPosition(StartPos, QTextCursor::MoveAnchor);
    cursor.setPosition(EndPos, QTextCursor::KeepAnchor);

    format.setFontWeight(QFont::Bold);
    QTextCharFormat format2=cursor.charFormat();
    if(format2.fontWeight()!=format.fontWeight())
    {
        cursor.mergeCharFormat(format);
    }
    else
    {
        format.setFontWeight(QFont::Thin);
        cursor.mergeCharFormat(format);
    }
}
void Tab::setItalic()
{
    QTextCharFormat format;
    format.setFontItalic(true);
    QTextCursor cursor=ui->textFied->textCursor();
    int StartPos,EndPos;

    StartPos=cursor.selectionStart();
    EndPos=cursor.selectionEnd();

    cursor.setPosition(StartPos, QTextCursor::MoveAnchor);
    cursor.setPosition(EndPos, QTextCursor::KeepAnchor);

    QTextCharFormat format2=cursor.charFormat();
    if(format2.fontItalic()!=format.fontItalic())
    {
        cursor.mergeCharFormat(format);
    }
    else
    {
        format.setFontItalic(false);
        cursor.mergeCharFormat(format);
    }

}
void Tab::setUnderline()
{
    QTextCharFormat format;
    format.setFontUnderline(true);
    QTextCursor cursor=ui->textFied->textCursor();
    int StartPos,EndPos;

    StartPos=cursor.selectionStart();
    EndPos=cursor.selectionEnd();

    cursor.setPosition(StartPos, QTextCursor::MoveAnchor);
    cursor.setPosition(EndPos, QTextCursor::KeepAnchor);

    QTextCharFormat format2=cursor.charFormat();
    if(format2.fontUnderline()!=format.fontUnderline())
    {
        cursor.mergeCharFormat(format);
    }
    else
    {
        format.setFontUnderline(false);
        cursor.mergeCharFormat(format);
    }
}
