#ifndef EDITVARIABLESDIALOG_H
#define EDITVARIABLESDIALOG_H

#include "core/Cutter.h"
#include <QDialog>

namespace Ui {
class EditVariablesDialog;
}

class EditVariablesDialog : public QDialog
{
    Q_OBJECT

public:
    explicit EditVariablesDialog(RVA offset, QWidget *parent = nullptr);
    ~EditVariablesDialog();

private slots:
    void applyFields();
    void updateFields();

private:
    Ui::EditVariablesDialog *ui;
    QList<VariableDescription> variables;

    void populateTypesComboBox();
};

#endif // EDITVARIABLESDIALOG_H
