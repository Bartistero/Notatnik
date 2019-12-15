#ifndef NOTATNIK_H
#define NOTATNIK_H

#include <QMainWindow>
#include <QTextEdit>
#include <tab.h>
#include <QCloseEvent>
QT_BEGIN_NAMESPACE
namespace Ui { class notatnik; }
QT_END_NAMESPACE

class notatnik : public QMainWindow
{
    Q_OBJECT

public:
    notatnik(QWidget *parent = nullptr);

    ~notatnik();


private slots:
    void on_tabWidget_tabCloseRequested(int index);
    void on_actionnew_triggered();
    void save();
    void open();
    void on_bold_triggered();

    void on_italic_triggered();

    void on_underline_triggered();

private:
    Ui::notatnik *ui;

    int how_card;
    QString fileName;

    QString setFileName(int);


    QString createTabName(int *how_card);
    void creatNewTab(const QString &title);

    void closeEvent(QCloseEvent *event);
};
#endif // NOTATNIK_H
