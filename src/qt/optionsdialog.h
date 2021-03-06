// Copyright (c) 2011-2015 The Bitcoin Core developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef BITCOIN_QT_OPTIONSDIALOG_H
#define BITCOIN_QT_OPTIONSDIALOG_H

#include <QDialog>
#include <QValidator>

class OptionsModel;
class QValidatedLineEdit;

QT_BEGIN_NAMESPACE
class QBoxLayout;
class QCheckBox;
class QValueComboBox;
class QDataWidgetMapper;
class QSpinBox;
class QString;
class QWidget;
QT_END_NAMESPACE

namespace Ui {
class OptionsDialog;
}

/** Proxy address widget validator, checks for a valid proxy address.
 */
class ProxyAddressValidator : public QValidator
{
    Q_OBJECT

public:
    explicit ProxyAddressValidator(QObject *parent);

    State validate(QString &input, int &pos) const;
};

/** Preferences dialog. */
class OptionsDialog : public QDialog
{
    Q_OBJECT

public:
    explicit OptionsDialog(QWidget *parent, bool enableWallet);
    ~OptionsDialog();

    void setModel(OptionsModel *model);
    void setMapper();

private Q_SLOTS:
    /* set OK button state (enabled / disabled) */
    void setOkButtonState(bool fState);
    void on_resetButton_clicked();
    void on_okButton_clicked();
    void on_cancelButton_clicked();

    void showRestartWarning(bool fPersistent = false);
    void clearStatusLabel();
    void updateProxyValidationState();
    /* query the networks, for which the default proxy is used */
    void updateDefaultProxyNets();
    void checkLineEdit();
    void maxuploadtargetCheckboxStateChanged(int);

    void blockmaxsize_changed(int);
    void blockmaxsize_increase(int);

Q_SIGNALS:
    void proxyIpChecks(QValidatedLineEdit *pUiProxyIp, int nProxyPort);

private:
    Ui::OptionsDialog *ui;
    OptionsModel *model;
    QDataWidgetMapper *mapper;

    QWidget *prevwidget;
    void FixTabOrder(QWidget *);
    void CreateOptionUI(QBoxLayout *, QWidget *, const QString& text);

    QValueComboBox *mempoolreplacement;
    QSpinBox *maxorphantx;
    QSpinBox *maxmempool;
    QSpinBox *mempoolexpiry;

    QCheckBox *rejectunknownscripts;
    QSpinBox *bytespersigop;
    QSpinBox *limitancestorcount;
    QSpinBox *limitancestorsize;
    QSpinBox *limitdescendantcount;
    QSpinBox *limitdescendantsize;
    QCheckBox *spamfilter;
    QCheckBox *rejectbaremultisig;
    QSpinBox *datacarriersize;

    QSpinBox *blockmaxsize, *blockprioritysize, *blockminsize;
    QCheckBox *priorityaccurate;
};

#endif // BITCOIN_QT_OPTIONSDIALOG_H
