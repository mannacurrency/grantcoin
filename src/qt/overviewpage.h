#ifndef OVERVIEWPAGE_H
#define OVERVIEWPAGE_H

#include "codecoinunits.h"
#include <QWidget>
#include <QAbstractItemDelegate>

QT_BEGIN_NAMESPACE
class QModelIndex;
QT_END_NAMESPACE

namespace Ui {
    class OverviewPage;
}
class WalletModel;
class TxViewDelegate;
class TransactionFilterProxy;

/** Overview ("home") page widget */
class OverviewPage : public QWidget
{
    Q_OBJECT

public:
    explicit OverviewPage(QWidget *parent = 0);
    ~OverviewPage();

    void setModel(WalletModel *model);
    void showOutOfSyncWarning(bool fShow);

public slots:
    void setBalance(qint64 balance, qint64 stake, qint64 unconfirmedBalance, qint64 immatureBalance);
    void setNumTransactions(int count);

signals:
    void transactionClicked(const QModelIndex &index);

private:
    Ui::OverviewPage *ui;
    WalletModel *model;
    qint64 currentBalance;
    qint64 currentStake;
    qint64 currentUnconfirmedBalance;
    qint64 currentImmatureBalance;

    TxViewDelegate *txdelegate;
    TransactionFilterProxy *filter;

private slots:
    void updateDisplayUnit();
    void handleTransactionClicked(const QModelIndex &index);
};

class TxViewDelegate : public QAbstractItemDelegate
{
	Q_OBJECT

public:
	TxViewDelegate(): QAbstractItemDelegate(), unit(CodecoinUnits::CC)
	{

	}

	void paint(QPainter *painter, const QStyleOptionViewItem &option,
			const QModelIndex &index ) const;

	QSize sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const;

	int unit;

};
#endif // OVERVIEWPAGE_H
