#include "EdgeFT.h"

#include <QDebug>

EdgeFT::EdgeFT()
{
}
EdgeFT::EdgeFT(const Edge &edge)
{
    const std::vector<std::complex<double> > edgeValues = edge.constValues();
    int edgeValueCount = edgeValues.size();

    m_fourierCoefficients.resize(edgeValueCount);

    int rangeStart = -edgeValueCount / 2;
    int rangeEnd = edgeValueCount % 2 ? edgeValueCount / 2 : (edgeValueCount / 2) - 1;
    ++rangeEnd;

    for (int m = rangeStart; m < rangeEnd; ++m)
    {
        std::complex<double> sum = 0;

        for (int n = 0; n < (int)edgeValues.size(); ++n)
            sum += edgeValues[n] * exp(std::complex<double>(0, -2 * M_PI * m * n / (int)edgeValues.size()));

        m_fourierCoefficients[m >= 0 ? m : (int)m_fourierCoefficients.size() + m] = sum / (double)edgeValues.size();
    }
}
Edge EdgeFT::edge() const
{
    Edge rebuiltEdge;

    int fourierCoefficientCount = (int)m_fourierCoefficients.size();

    rebuiltEdge.m_values.reserve(fourierCoefficientCount);

    int rangeStart = -fourierCoefficientCount / 2;
    int rangeEnd = fourierCoefficientCount % 2 ? fourierCoefficientCount / 2 : (fourierCoefficientCount / 2) - 1;
    ++rangeEnd;

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

        rebuiltEdge.m_values.push_back(sum);
    }

    return rebuiltEdge;
}

void EdgeFT::lowPassFilter(float percentThreshold)
{
    if (percentThreshold == 100)
        m_fourierCoefficients.clear();

    int halfSize = m_fourierCoefficients.size() / 2;
    int maxFreqIndex = m_fourierCoefficients.size() / 2;
    int removeRangeWidth = (int)(percentThreshold * (float)halfSize / 100.f);

    qDebug() << QString("%1 frequences à mettre à 0").arg(removeRangeWidth * 2 + 1);

    for (int i = 0; i < removeRangeWidth; ++i)
    {
        m_fourierCoefficients[maxFreqIndex - i] = 0;
        m_fourierCoefficients[maxFreqIndex + i] = 0;
    }
}
