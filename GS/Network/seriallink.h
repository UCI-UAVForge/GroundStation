#ifndef SERIALLINK_H
#define SERIALLINK_H

#include <QObject>

class seriallink : public QObject
{
    Q_OBJECT
public:
    explicit seriallink(QObject *parent = nullptr);

signals:

public slots:
};

#endif // SERIALLINK_H