#ifndef SUBCATEGORYWINDOW_H
#define SUBCATEGORYWINDOW_H

#include <QWidget>

namespace Ui { class SubcategoryWindow; }

class SubcategoryWindow : public QWidget {
    Q_OBJECT

public:
    explicit SubcategoryWindow(QWidget *parent = nullptr);
    ~SubcategoryWindow();

private:
    Ui::SubcategoryWindow *ui;
};

#endif // SUBCATEGORYWINDOW_H
