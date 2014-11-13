#ifndef EDGEVIEW_H
#define EDGEVIEW_H

#include "Edge.h"
#include "EdgeFT.h"

#include <QGraphicsView>

class EdgeView : public QGraphicsView
{
    Q_OBJECT

private:

    Edge m_edge;
    QColor m_edgeColor;

    EdgeFT m_edgeFT;
    QColor m_edgeFTColor;

public:

    explicit EdgeView(QWidget *parent = 0);

    void paintEvent(QPaintEvent* event);
    void mouseReleaseEvent(QMouseEvent *event);

private:

    void drawEdge(QPainter& painter, const Edge& edge, const QColor& color, qreal width);

};

#endif // EDGEVIEW_H
