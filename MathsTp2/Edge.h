#ifndef EDGE_H
#define EDGE_H

#include <QDebug>

#include <complex>
#include <vector>

class Edge
{
protected:

    std::vector<std::complex<double> > m_values;

public:

    void print() const
    {
        qDebug() << "----- Contour initial -----";

        for (int i = 0; i < (int)m_values.size(); ++i)
            qDebug() << QString("<%1,%2>")
                        .arg(m_values[i].real())
                        .arg(m_values[i].imag());

        qDebug() << "---------------------------";
    }

    std::vector<std::complex<double> >& values() { return m_values; }
    const std::vector<std::complex<double> >& constValues() const { return m_values; }
};

#endif // EDGE_H
