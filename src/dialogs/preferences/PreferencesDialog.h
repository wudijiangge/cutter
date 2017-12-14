
#ifndef PREFERENCESDIALOG_H
#define PREFERENCESDIALOG_H

#include <QDialog>
#include <QPushButton>
#include <memory>

#include "cutter.h"

namespace Ui
{
    class PreferencesDialog;
}

class PreferencesDialog : public QDialog
{
Q_OBJECT

public:
    enum class Section { Disassembly };

    explicit PreferencesDialog(QWidget *parent = nullptr);
    ~PreferencesDialog();

    void showSection(Section section);

signals:
    void saveAsDefault();
    void resetToDefault();

private:
    std::unique_ptr<Ui::PreferencesDialog> ui;

    void on_buttonBox_clicked(QAbstractButton *button);
};

#endif //PREFERENCESDIALOG_H