#include "EdgeView.h"

#include <QPainter>
#include <QPen>
#include <QMouseEvent>
#include <QString>
#include <QDebug>

#include <complex>

EdgeView::EdgeView(QWidget *parent) :
    QGraphicsView(parent),
    m_edgeColor(0, 0, 255),
    m_edgeFTColor(255, 0, 0)
{
}

void EdgeView::paintEvent(QPaintEvent* event)
{
    QGraphicsView::paintEvent(event);

    QPainter painter(viewport());

    drawEdge(painter, m_edge, m_edgeColor, 2);
    drawEdge(painter, m_edgeFT.edge(), m_edgeFTColor, 2);
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

    // Dessine les lignes
    for (int i = 0; i < valueCount; ++i)
    {
        if (i < (valueCount - 1))
        {
            painter.drawLine(edgeValues[i].real(), edgeValues[i].imag(),
                             edgeValues[i + 1].real(), edgeValues[i + 1].imag());
        }
        else
        {
            painter.drawLine(edgeValues[i].real(), edgeValues[i].imag(),
                             edgeValues[0].real(), edgeValues[0].imag());
        }
    }

    // Dessine les sommets
    for (int i = 0; i < valueCount; ++i)
        painter.drawEllipse(QPointF(edgeValues[i].real(), edgeValues[i].imag()), 4, 4);
}

void EdgeView::mouseReleaseEvent(QMouseEvent *event)
{
    QPoint pos = event->pos();

    m_edge.values().push_back(std::complex<double>(pos.x(), pos.y()));

    m_edgeFT = EdgeFT(m_edge);

    viewport()->update();
}
