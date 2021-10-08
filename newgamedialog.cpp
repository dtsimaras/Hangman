#include "dialog.h"

Dialog::Dialog(QVector<QString> cat)
{
    setModal(true);
    setFixedSize(200,120);
    setWindowTitle("New Game");

    // Creating Layout
    layout = new QVBoxLayout;
    setLayout(layout);

    // Creating Widgets ( Components )
    label = new QLabel;
    label->setText("Select category: ");
    label->setAlignment(Qt::AlignVCenter);

    // Create Combo Box
    combo = new QComboBox;
    for (int i=0;i<cat.size();i++) {
        combo->addItem(cat[i]);
    }

    button = new QPushButton;
    button->setText("Start Game");
    connect(button,SIGNAL(clicked()),this,SLOT(accept()));

    layout->addWidget(label);
    layout->addWidget(combo);
    layout->addWidget(button);
}

QString Dialog::getCategory()
{
    return combo->currentText();
}
