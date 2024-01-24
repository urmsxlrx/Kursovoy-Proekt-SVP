#include "tablitsa.h"
#include "./ui_tablitsa.h"
#include "addpanel.h"

tablitsa::tablitsa(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::tablitsa){
    ui->setupUi(this);
    setWindowTitle("Картотека пациентов");
    table = new QTableWidget(this);
    table->setColumnCount(6);
    QStringList headers;
    headers << "Фамилия" << "Имя" << "Отчество" << "Дата рождения" << "Рост" << "Вес";
    table->setHorizontalHeaderLabels(headers);
    setCentralWidget(table);
    loadFromFile();
    table->setEditTriggers(QAbstractItemView::NoEditTriggers);
}

tablitsa::~tablitsa(){
    delete ui;
}

void tablitsa::on_addButton_triggered(){
    addPanel panel;
    if (panel.exec() == QDialog::Accepted) {
        QString surname = panel.getSurname();
        QString name = panel.getName();
        QString lastName = panel.getLastName();
        QDate birthDate = panel.getBirthDate();
        QString height = panel.getHeight();
        QString weight = panel.getWeight();
        int row = table->rowCount();
        table->insertRow(row);
        QTableWidgetItem* itemSurname = new QTableWidgetItem(surname);
        table->setItem(row, 0, itemSurname);
        QTableWidgetItem* itemName = new QTableWidgetItem(name);
        table->setItem(row, 1, itemName);
        QTableWidgetItem* itemLastName = new QTableWidgetItem(lastName);
        table->setItem(row, 2, itemLastName);
        QTableWidgetItem* itemBirthDate = new QTableWidgetItem(birthDate.toString());
        table->setItem(row, 3, itemBirthDate);
        QTableWidgetItem* itemHeight = new QTableWidgetItem(height);
        table->setItem(row, 4, itemHeight);
        QTableWidgetItem* itemWeight = new QTableWidgetItem(weight);
        table->setItem(row, 5, itemWeight);
        saveToFile();
    }
}

void tablitsa::on_delButton_triggered(){
    QList<QTableWidgetItem*> selectedItems = table->selectedItems();
    if (!selectedItems.isEmpty()) {
        int row = table->row(selectedItems.first());
        table->removeRow(row);
        saveToFile();
    }
    else {
        QMessageBox::warning(this, "Ошибка", "Выберите пациента для удаления");
    }
}

void tablitsa::on_editButton_triggered(){
    QList<QTableWidgetItem*> selectedItems = table->selectedItems();
    if (!selectedItems.isEmpty()) {
        int row = table->row(selectedItems.first());
        QString surname = table->item(row, 0)->text();
        QString name = table->item(row, 1)->text();
        QString lastName = table->item(row, 2)->text();
        QDate birthDate = QDate::fromString(table->item(row, 3)->text());
        QString height = table->item(row, 4)->text();
        QString weight = table->item(row, 5)->text();
        addPanel panel;
        panel.setSurname(surname);
        panel.setName(name);
        panel.setLastName(lastName);
        panel.setBirthDate(birthDate);
        panel.setHeight(height);
        panel.setWeight(weight);
        if (panel.exec() == QDialog::Accepted) {
            table->item(row, 0)->setText(panel.getSurname());
            table->item(row, 1)->setText(panel.getName());
            table->item(row, 2)->setText(panel.getLastName());
            table->item(row, 3)->setText(panel.getBirthDate().toString());
            table->item(row, 4)->setText(panel.getHeight());
            table->item(row, 5)->setText(panel.getWeight());
            saveToFile();
        }
    } else {
        QMessageBox::warning(this, "Ошибка", "Выберите пациента для редактирования");
    }
}

void tablitsa::saveToFile(){
    QFile file("database.txt");
    if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QTextStream save(&file);
        for (int row = 0; row < table->rowCount(); ++row) {
            QStringList values;
            for (int column = 0; column < 6; ++column) {
                QTableWidgetItem* item = table->item(row, column);
                if (item) {
                    values.append(item->text());
                } else {
                    values.append("");
                }
            }
            save << values.join(",") << "\n";
        }
        file.close();
    }
    else {
        QMessageBox::warning(this, "Ошибка", "Файл базы данных не существует");
    }
}

void tablitsa::loadFromFile(){
    QFile file("database.txt");
    if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QTextStream load(&file);
        while (!load.atEnd()) {
            QString line = load.readLine();
            QStringList values = line.split(",");
            if (values.size() == 6) {
                int row = table->rowCount();
                table->insertRow(row);
                for (int i = 0; i < 6; ++i) {
                    QTableWidgetItem* item = new QTableWidgetItem(values[i]);
                    table->setItem(row, i, item);
                }
            }
        }
        file.close();
    }
    else {
        QMessageBox::warning(this, "Ошибка", "Файл базы данных не существует");
    }
}

void tablitsa::on_actionGithub_triggered(){
    QDesktopServices::openUrl(QUrl("https://github.com/Raykrad/KursovoySVP"));
}

void tablitsa::on_gorit_triggered(){
    QString message = "Shift+Q - добавление пациента\n"
                      "Shift+W - удаление пациента\n"
                      "Shift+E - редактирование пациента";

    QMessageBox::information(this, "Горячие клавиши", message);
}
