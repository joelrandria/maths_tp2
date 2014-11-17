#ifndef EDGE_H
#define EDGE_H

#include <QList>
#include <QPoint>
#include <QDebug>

#include <complex>
#include <vector>

class Edge
{
    friend class EdgeFT;

private:

    int m_closureValueCount;
    std::vector<std::complex<double> > m_values;

public:

    Edge()
        :m_closureValueCount(0){}

    void print() const
    {
        qDebug() << "----- Contour initial -----";

        for (int i = 0; i < (int)m_values.size(); ++i)
            qDebug() << QString("<%1,%2>")
                        .arg(m_values[i].real())
                        .arg(m_values[i].imag());

        qDebug() << "---------------------------";
    }

    void addValue(std::complex<double> value)
    {
        deleteClosureValues();

        m_values.push_back(value);

        close();
    }

    const std::vector<std::complex<double> >& constValues() const { return m_values; }

    static void getEdgePoints(const QPoint &p1, const QPoint &p2, QList<QPoint> &points)
    {
        int drow, dcol, i, e;
        int incR, incC, inc1, inc2;
        int row,col;

        int col1 = p1.x();
        int row1 = p1.y();

        int col2 = p2.x();
        int row2 = p2.y();

        points.clear();

        drow = abs(row2 - row1);
        dcol = abs(col2 - col1);

        incR = 1;
        if(row2 < row1) incR = -1;
        incC = 1;
        if(col2 < col1) incC = -1;
        row = row1;
        col = col1;

        points.push_back(QPoint(col, row));

        if(drow > dcol)
        {
            e = 2 * dcol - drow;
            inc1 = 2 * (dcol -drow);
            inc2 = 2 * dcol;
            for(i = 0; i < drow; ++i)
            {
                if(e >= 0)
                {
                    col += incC;
                    e += inc1;
                }
                else
                {
                    e += inc2;
                }

                row += incR;

                points.push_back(QPoint(col, row));
            }
        }
        else
        {
            e = 2 * drow - dcol;
            inc1 = 2 * (drow - dcol);
            inc2 = 2 * drow;
            for(i = 0; i < dcol; ++i)
            {
                if(e >= 0)
                {
                    row += incR;
                    e += inc1;
                }
                else
                {
                    e += inc2;
                }

                col += incC;

                points.push_back(QPoint(col, row));
            }
        }
    }

private:

    void deleteClosureValues()
    {
        while (m_closureValueCount-- > 0)
            m_values.pop_back();
    }
    void close()
    {
        if (m_values.size() < 2)
            return;

        QPoint start(m_values[m_values.size() - 1].real(), m_values[m_values.size() - 1].imag());
        QPoint end(m_values[0].real(), m_values[0].imag());
        QList<QPoint> closurePoints;

        getEdgePoints(start, end, closurePoints);

        for (int i = 0; i < closurePoints.count(); ++i)
            m_values.push_back(std::complex<double>(closurePoints[i].x(), closurePoints[i].y()));

        m_closureValueCount += closurePoints.count();
    }

};

#endif // EDGE_H
