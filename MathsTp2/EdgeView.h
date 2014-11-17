#ifndef EDGEVIEW_H
#define EDGEVIEW_H

#include "Edge.h"
#include "EdgeFT.h"

#include <QPoint>
#include <QGraphicsView>

class EdgeView : public QGraphicsView
{
    Q_OBJECT

private:

    QPoint m_lastSelectedPoint;

    Edge m_edge;
    QColor m_edgeColor;

    Edge m_filteredEdge;
    QColor m_filteredEdgeColor;

public:

    explicit EdgeView(QWidget *parent = 0);

    void paintEvent(QPaintEvent* event);
    void mouseReleaseEvent(QMouseEvent *event);

    void applyLowPassFilter(float percentThreshold);

    void reset();

private:

    void drawEdge(QPainter& painter, const Edge& edge, const QColor& color, qreal width);

};

#endif // EDGEVIEW_H
