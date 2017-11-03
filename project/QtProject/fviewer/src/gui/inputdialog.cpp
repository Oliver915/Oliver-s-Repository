#include "inputdialog.h"

InputDialog::InputDialog(int index, QWidget* parent)
    : QDialog(parent)
{    
    if (index == 1)
    {
        searchUAV();
    }
}

void InputDialog::searchUAV()
{
    setWindowTitle(tr("Search UAV"));

    nameLabel1 = new QLabel;
    nameLabel1->setText(tr("Index of UAV： "));
    nameLabel2 = new QLabel;
    nameLabel2->setText(tr("  "));
    nameLabel2->setFrameStyle(
            QFrame::Panel | QFrame::Sunken);
    nameBtn = new QPushButton;
    nameBtn->setText(tr("Modify"));

    mainLayout = new QGridLayout(this);
    mainLayout->addWidget(nameLabel1, 0, 0);
    mainLayout->addWidget(nameLabel2, 0, 1);
    mainLayout->addWidget(nameBtn, 0, 2);

    connect(nameBtn, SIGNAL(clicked()), this,
            SLOT(changeUAV()));
}

void InputDialog::changeUAV()
{
    bool ok;
    indexOfUAV = QInputDialog::getInt(
            this, tr("Input the index of UAV"),
            tr("Index of UAV："),
            nameLabel2->text().toInt(&ok), 0, 1000, 1, &ok);
    if (ok)
    {
        nameLabel2->setText(
                QString(tr("%1")).arg(indexOfUAV));
    }
}

int InputDialog::outputIndex()
{
    return indexOfUAV;
}
