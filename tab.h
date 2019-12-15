#ifndef TAB_H
#define TAB_H
#include <QWidget>
#include <QFileDialog>
#include <QMainWindow>
#include <QTextEdit>
namespace Ui {
class Tab;
}

class Tab : public QWidget
{
    Q_OBJECT

public:
    explicit Tab(QWidget *parent = nullptr);
    ~Tab();
    bool isEditedPublic();
    QString getText();
    void save();
    void set_text(QString tekst);
    void setBold();
    void setItalic();
    void setUnderline();

private:
    Ui::Tab *ui;
    bool edited;
    QString fileName;


private slots:
    void isEdited();
};

#endif // TAB_H
