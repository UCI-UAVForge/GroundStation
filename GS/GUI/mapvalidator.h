#ifndef MAPVALIDATOR_H
#define MAPVALIDATOR_H

#include <QDoubleValidator>
#include <QValidator>
//This class is used for the Latitude and Longitude input validation
//but we have to override the validate function so that values are within the range specified by the users
//credit: http://stackoverflow.com/questions/19571033/allow-entry-in-qlineedit-only-within-range-of-qdoublevalidator
//By: Daniel Ortega
class MapValidator : public QDoubleValidator
{

public:
    MapValidator(double bottom, double top, int decimals, QObject * parent);

    QValidator::State validate(QString &s, int &i) const;

};
#endif // MAPVALIDATOR_H
