#ifndef EDGEFT_H
#define EDGEFT_H

#include "Edge.h"

#include <complex>
#include <vector>

class EdgeFT : public Edge
{
private:

    std::vector<std::complex<double> > m_fourierCoefficients;

public:

    EdgeFT();
    EdgeFT(const Edge& edge);

    Edge edge() const;

    void print() const;

private:

    std::complex<double> valueToFourierCoefficient(const std::vector<std::complex<double> >& values, double frequencyFactor) const;
    std::complex<double> fourierCoefficientToValue(const std::vector<std::complex<double> >& coefficients, double valueIndex) const;
};

#endif // EDGEFT_H
