#include "AboutDialog.h"

#include <QLabel>
#include <QVBoxLayout>
#include <QDialogButtonBox>

AboutDialog::AboutDialog(QWidget *parent) :
    QDialog(parent)
{
    /* GUI */
    QLabel *shortcutLabel = new QLabel(this);
    shortcutLabel->setText(tr("<b> Горячие клавиши</b><br>"
                              "<b> CTRL+Q</b> --- <i>Выйти</i><br>"
                              "<b> CTRL+Z</b> --- <i>Очистить все</i>"
                              "<b> CTRL+A</b> --- <i>Выделить все</i><br>"
                              "<b> CTRL+X</b> --- <i>Выделить X</i><br>"
                              "<b> CTRL+Y</b> --- <i>Выделить Y</i><br>"
                              "<b> CTRL+C</b> --- <i>Копировать выделенное</i><br>"
                              "<b> F1</b>     --- <i>Справка</i><br>"));

    QLabel *authorLabel = new QLabel(this);
    authorLabel->setText(tr("Автор: Сергей Хасанов <s.a.khasanov@gmail.com>"));

    QDialogButtonBox *btnBox = new QDialogButtonBox(QDialogButtonBox::Ok);

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addWidget(shortcutLabel);
    mainLayout->addWidget(authorLabel);
    mainLayout->addStretch();
    mainLayout->addWidget(btnBox);

    setLayout(mainLayout);

    setWindowTitle(tr("О программе"));
    setFixedSize(sizeHint());
    /* !GUI */

    connect(btnBox, SIGNAL(accepted()), this, SLOT(accept()));
}
