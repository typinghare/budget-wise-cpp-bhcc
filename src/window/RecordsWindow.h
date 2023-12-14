#ifndef RECORDSWINDOW_H
#define RECORDSWINDOW_H

#include <QWidget>
#include <QStandardItemModel>

namespace Ui { class RecordsWindow; }

class RecordsWindow : public QWidget {
    Q_OBJECT

public:
    explicit RecordsWindow(QWidget *parent = nullptr);

    RecordsWindow(const QString &categoryName, QWidget *parent = nullptr);

    ~RecordsWindow();

public slots:
    void onBackButtonClicked();

private:
    Ui::RecordsWindow *ui;
    QStandardItemModel *itemModel;
    int categoryId;

    void displayRecords();

    void setRow(
        int row,
        QDateTime date,
        const QString& subcategoryName,
        double amount);
};

#endif // RECORDSWINDOW_H
