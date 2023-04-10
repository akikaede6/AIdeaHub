#include "InputDialog.h"

#include <QLabel>
#include <QLineEdit>
#include <QHBoxLayout>
#include <QPushButton>

InputDialog::InputDialog()
{
    QHBoxLayout *mainLayout = new QHBoxLayout();
    QLabel *apiLabel = new QLabel(tr("API key"), this);
    QLineEdit *apiEdit = new QLineEdit(this);

    mainLayout->addWidget(apiLabel);
    mainLayout->addWidget(apiEdit);
}
