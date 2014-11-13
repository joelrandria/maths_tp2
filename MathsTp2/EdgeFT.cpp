#include "EdgeFT.h"

#include <QDebug>

EdgeFT::EdgeFT()
{
}
EdgeFT::EdgeFT(const Edge &edge)
{
//    edge.print();

    const std::vector<std::complex<double> > edgeValues = edge.constValues();
    int edgeValueCount = edgeValues.size();

    m_fourierCoefficients.resize(edgeValueCount);

    int rangeStart = -edgeValueCount / 2;
    int rangeEnd = edgeValueCount % 2 ? edgeValueCount / 2 : (edgeValueCount / 2) - 1;
    ++rangeEnd;

//    qDebug() << QString("FT sur [%1,%2[").arg(rangeStart).arg(rangeEnd);

    for (int m = rangeStart; m < rangeEnd; ++m)
    {
        std::complex<double> sum = 0;

        for (int n = 0; n < (int)edgeValues.size(); ++n)
            sum += edgeValues[n] * exp(std::complex<double>(0, -2 * M_PI * m * n / (int)edgeValues.size()));

        m_fourierCoefficients[m >= 0 ? m : (int)m_fourierCoefficients.size() + m] = sum / (double)edgeValues.size();
    }

//    qDebug() << "---------------- FT ----------------";

//    for (int i = 0; i < (int)m_fourierCoefficients.size(); ++i)
//        qDebug() << QString("<%1,%2>")
//                    .arg(m_fourierCoefficients[i].real())
//                    .arg(m_fourierCoefficients[i].imag());

//    qDebug() << "------------------------------------";
}
Edge EdgeFT::edge() const
{
    Edge rebuiltEdge;

    int fourierCoefficientCount = (int)m_fourierCoefficients.size();

    int rangeStart = -fourierCoefficientCount / 2;
    int rangeEnd = fourierCoefficientCount % 2 ? fourierCoefficientCount / 2 : (fourierCoefficientCount / 2) - 1;
    ++rangeEnd;

//    qDebug() << QString("FT inverse sur [%1,%2[").arg(rangeStart).arg(rangeEnd);

    for (int n = 0; n < (int)m_fourierCoefficients.size(); ++n)
    {
        std::complex<double> sum = 0;

        for (int m = rangeStart; m < rangeEnd; ++m)
        {
            std::complex<double> sm = 0;

            if (m >= 0)
                sm = m_fourierCoefficients[m];
            else
                sm = m_fourierCoefficients[(int)m_fourierCoefficients.size() + m];

            sum += sm * exp(std::complex<double>(0, 2 * M_PI * m * n / (int)m_fourierCoefficients.size()));
        }

        rebuiltEdge.values().push_back(sum);
    }

//    qDebug() << "---------------- FT-1 ----------------";

//    for (int i = 0; i < (int)rebuiltEdge.values().size(); ++i)
//        qDebug() << QString("<%1,%2>")
//                    .arg(rebuiltEdge.values()[i].real())
//                    .arg(rebuiltEdge.values()[i].imag());

//    qDebug() << "---------------------------------------";

    return rebuiltEdge;
}
