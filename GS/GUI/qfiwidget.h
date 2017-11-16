#ifndef QFIWIDGET_H
#define QFIWIDGET_H

#include <QWidget>
#include <QVBoxLayout>
#include "qfi_PFD.h"
#include "qfi_TC.h"


class QFIWidget : public QWidget
{
    Q_OBJECT
public:
    explicit QFIWidget (QWidget * parent = nullptr);
    QVBoxLayout *layout;

    inline void update()
    {
        m_pfd->update();
        m_tc->update();
    }

    inline void setRoll( float roll )
    {
        m_pfd->setRoll(roll);
    }

    inline void setPitch( float pitch )
    {
        m_pfd->setPitch( pitch );
    }

    inline void setFlightPathMarker( float aoa, float sideslip )
    {
        m_pfd->setFlightPathMarker( aoa, sideslip );
    }

    inline void setSlipSkid( float slipSkid )
    {
        m_pfd->setSlipSkid( slipSkid );
        m_tc->setSlipSkid( slipSkid );
    }

    inline void setDevH( float devH )
    {
        m_pfd->setBarH( devH );
        m_pfd->setDotH( devH );
    }

    inline void setDevV( float devV )
    {
        m_pfd->setBarV( devV );
        m_pfd->setDotV( devV );
    }

    inline void setAltitude( float altitude )
    {
        m_pfd->setAltitude( altitude );
    }

    inline void setPressure( float pressure )
    {
        // qfi_PFD Units: STD Standard, IN Inches of Mercury
        m_pfd->setPressure(pressure, qfi_PFD::PressureUnit::STD);
    }

    inline void setAirspeed( float airspeed )
    {
        m_pfd->setAirspeed( airspeed );
    }

    inline void setMachNo( float machNo )
    {
        m_pfd->setMachNo( machNo );
    }

    inline void setHeading( float heading )
    {
        m_pfd->setHeading( heading );
    }

    inline void setTurnRate( float turnRate )
    {
        m_pfd->setTurnRate( turnRate );
        m_tc->setTurnRate( turnRate );
    }

    inline void setClimbRate( float climbRate )
    {
        m_pfd->setClimbRate( climbRate );
    }

private:
    qfi_PFD     *m_pfd;
    qfi_TC      *m_tc;
};

#endif // QFIWIDGET_H
