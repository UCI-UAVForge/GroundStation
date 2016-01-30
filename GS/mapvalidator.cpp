#include "mapplanning.h"

MapValidator::MapValidator(double bottom, double top, int decimals, QObject * parent)
    :QDoubleValidator(bottom, top, decimals, parent)
{
}
MapValidator::QValidator::State MapValidator::validate(QString &s, int &i) const
{
    if (s.isEmpty() || s == "-") {
        return QValidator::Intermediate;
    }

    QLocale locale;

    QChar decimalPoint = locale.decimalPoint();
    int charsAfterPoint = s.length() - s.indexOf(decimalPoint) -1;

    if (charsAfterPoint > decimals() && s.indexOf(decimalPoint) != -1) {
        return QValidator::Invalid;
    }

    bool ok;
    double d = locale.toDouble(s, &ok);

    if (ok && d >= bottom() && d <= top()) {
        return QValidator::Acceptable;
    } else {
        return QValidator::Invalid;
    }
}
