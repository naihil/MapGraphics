#ifndef PRIVATEQGRAPHICSVIEW_H
#define PRIVATEQGRAPHICSVIEW_H

#include <QGraphicsView>

class PrivateQGraphicsView : public QGraphicsView
{
    Q_OBJECT

public:
    explicit PrivateQGraphicsView(QWidget *parent = nullptr);
    explicit PrivateQGraphicsView(QGraphicsScene *scene, QWidget *parent = nullptr);
    ~PrivateQGraphicsView() override;

signals:
    void hadMouseDoubleClickEvent(QMouseEvent *event);
    void hadMouseMoveEvent(QMouseEvent *event);
    void hadMousePressEvent(QMouseEvent *event);
    void hadMouseReleaseEvent(QMouseEvent *event);
    void hadContextMenuEvent(QContextMenuEvent *);
    void hadWheelEvent(QWheelEvent *);

protected:
    void mouseDoubleClickEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    void contextMenuEvent(QContextMenuEvent *event) override;
    void wheelEvent(QWheelEvent *event) override;
};

#endif // PRIVATEQGRAPHICSVIEW_H
