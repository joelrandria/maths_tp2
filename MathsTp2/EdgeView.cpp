#include "EdgeView.h"

#include <QPainter>
#include <QPen>
#include <QMouseEvent>
#include <QString>
#include <QElapsedTimer>
#include <QDebug>

#include <complex>

EdgeView::EdgeView(QWidget *parent) :
    QGraphicsView(parent),
    m_edgeColor(0, 0, 255),
    m_filteredEdgeColor(255, 0, 0)
{
}

void EdgeView::paintEvent(QPaintEvent* event)
{
    QGraphicsView::paintEvent(event);

    QPainter painter(viewport());

    drawEdge(painter, m_edge, m_edgeColor, 2);
    drawEdge(painter, m_filteredEdge, m_filteredEdgeColor, 2);
}
void EdgeView::drawEdge(QPainter& painter, const Edge &edge, const QColor &color, qreal width)
{
    int valueCount;
    std::vector<std::complex<double> > edgeValues;

    edgeValues = edge.constValues();
    valueCount = edgeValues.size();

    QPen pen(color, width);

    painter.setPen(pen);
    painter.setRenderHint(QPainter::Antialiasing);

    for (int i = 0; i < valueCount; ++i)
        painter.drawPoint(edgeValues[i].real(), edgeValues[i].imag());
}

void EdgeView::mouseReleaseEvent(QMouseEvent *event)
{
    QList<QPoint> edgePoints;

    QPoint pos = event->pos();

    if (!m_lastSelectedPoint.isNull())
    {
        Edge::getEdgePoints(m_lastSelectedPoint, pos, edgePoints);

        for (int i = 0; i < edgePoints.count(); ++i)
            m_edge.addValue(std::complex<double>(edgePoints[i].x(), edgePoints[i].y()));
    }

    m_lastSelectedPoint = pos;

    viewport()->update();
}

void EdgeView::applyLowPassFilter(float percentThreshold)
{
    if (percentThreshold <= 0)
    {
        m_filteredEdge = Edge();
    }
    else
    {
        QElapsedTimer timer;
        timer.start();

        EdgeFT edgeFT(m_edge);

        qDebug() << QString("Transformée de Fourier effectuée en %1 secondes s/ %2 points")
                    .arg((double)timer.elapsed() / 1000.f).arg(m_edge.constValues().size());

        timer.restart();

        edgeFT.lowPassFilter(percentThreshold);

        m_filteredEdge = edgeFT.edge();

        qDebug() << QString("Transformée de Fourier inverse effectuée en %1 secondes s/ %2 fréquences")
                    .arg((double)timer.elapsed() / 1000.f).arg(edgeFT.fourierCoefficients().size());
    }

    viewport()->update();
}

void EdgeView::reset()
{
    m_lastSelectedPoint = QPoint();

    m_edge = Edge();
    m_filteredEdge = Edge();

    viewport()->update();
}
