#ifndef STATUS_WIDGET_H
#define STATUS_WIDGET_H

#include "QPlainTextEdit.h"
#include "QTimer.h"
#include "QString.h"
#include "QObject.h"
#include "messagebox.h"

class StatusWidget : public QPlainTextEdit
{
private:
	QTimer StatusTimer;

	QString start;

    messagebox * mb ;

public:
	explicit StatusWidget(QObject* parent);

	~StatusWidget();

	void initiate(messagebox * mbin);

	QTimer getStatusTimer();

	void setStatusTimer(QTimer newStatusTimer);

private slots:

    void showStatus();

signals:

    void updateMe() ;

};
#endif
