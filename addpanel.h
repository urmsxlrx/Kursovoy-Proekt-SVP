#ifndef ADDPANEL_H
#define ADDPANEL_H

#include <QDialog>
#include <QDate>

namespace Ui {
class addPanel;
}

class addPanel : public QDialog
{
    Q_OBJECT

public:
    explicit addPanel(QWidget *parent = nullptr);
    ~addPanel();
    QString getSurname() const;
    QString getName() const;
    QString getLastName() const;
    QDate getBirthDate() const;
    QString getHeight() const;
    QString getWeight() const;
    void setSurname(const QString &surname);
    void setName(const QString &name);
    void setLastName(const QString &lastName);
    void setBirthDate(const QDate &birthDate);
    void setHeight(const QString &height);
    void setWeight(const QString &weight);

private slots:
    void on_add_clicked();
    void on_exit_clicked();

private:
    Ui::addPanel *ui;
    QString surname, name, lastName, height, weight;
    QDate birthDate;
};

#endif // ADDPANEL_H
