#include "addpanel.h"
#include "ui_addpanel.h"
#include "QSpinBox"

addPanel::addPanel(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::addPanel)
{
    ui->setupUi(this);
    setWindowTitle("Добавление пациентов");
    ui->dateBirth->setDate(QDate());
}

QString addPanel::getSurname() const {
    return surname;
}

void addPanel::setSurname(const QString &surname) {
    this->surname = surname;
    ui->surname->setText(surname);
}

QString addPanel::getName() const {
    return name;
}

void addPanel::setName(const QString &name) {
    this->name = name;
    ui->name->setText(name);
}

QString addPanel::getLastName() const {
    return lastName;
}

void addPanel::setLastName(const QString &lastName) {
    this->lastName = lastName;
    ui->lastName->setText(lastName);
}

QDate addPanel::getBirthDate() const {
    return birthDate;
}

void addPanel::setBirthDate(const QDate &birthDate) {
    this->birthDate = birthDate;
    ui->dateBirth->setDate(birthDate);
}

QString addPanel::getHeight() const {
    return height;
}

void addPanel::setHeight(const QString &height) {
    this->height = height;
    ui->height->setValue(height.toInt());
}

QString addPanel::getWeight() const {
    return weight;
}

void addPanel::setWeight(const QString &weight) {
    this->weight = weight;
    ui->weight->setValue(weight.toInt());
}

addPanel::~addPanel(){
    delete ui;
}

void addPanel::on_add_clicked(){
    surname = ui->surname->text();
    name = ui->name->text();
    lastName = ui->lastName->text();
    birthDate = ui->dateBirth->date();
    int intHeight = ui->height->value();
    height = QString::number(intHeight);
    int intWeight = ui->weight->value();
    weight = QString::number(intWeight);
    accept();
}


void addPanel::on_exit_clicked(){
    reject();
}

