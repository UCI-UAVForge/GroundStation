#ifndef FZLAYOUTBOX_H
#define FZLAYOUTBOX_H

#include <QGridLayout>
#include <QLabel>


class fzLayoutBox : public QGridLayout
{
public:
    fzLayoutBox();

private:
    QLabel *nmin, *nmax;
    QGridLayout *boundary;

public slots:
    void setMinMax(QString mini, QString maxi);
};

#endif // FZLAYOUTBOX_H
