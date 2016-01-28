#ifndef MAPVALIDATOR_H
#define MAPVALIDATOR_H

#include <QDoubleValidator>

//This class is used for the Latitude and Longitude input validation
//credit: http://stackoverflow.com/questions/19571033/allow-entry-in-qlineedit-only-within-range-of-qdoublevalidator
class MapValidator : public QDoubleValidator
{
    public:
    MapValidator(double bottom, double top, int decimals, QObject * parent) :
    QDoubleValidator(bottom, top, decimals, parent)
    {
    }

    QValidator::State validate(QString &s, int &i) const
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
};
#endif // MAPVALIDATOR_H
