#ifndef INPUTDIALOG_H
#define INPUTDIALOG_H

#include <QDialog>
#include <QGridLayout>
#include <QInputDialog>
#include <QLabel>
#include <QPushButton>
#include "mpssideviewmanipulator.h"

class InputDialog : public QDialog
{
    Q_OBJECT
public:
    /**
     * @brief InputDialog
     * @param index
     * @param parent
     */
    InputDialog(int index, QWidget* parent = 0);

    int outputIndex();

private:
    void searchUAV();

private slots:
    void changeUAV();

private:
    QLabel* nameLabel1;
    QLabel* nameLabel2;
    QLabel* sexLabel1;
    QPushButton* nameBtn;
    QPushButton* sexBtn;
    QGridLayout* mainLayout;
    int indexOfUAV;
};

#endif  // INPUTDIALOG_H
