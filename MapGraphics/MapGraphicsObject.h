#ifndef MAPGRAPHICSOBJECT_H
#define MAPGRAPHICSOBJECT_H

#include <QObject>
#include <QPointF>
#include <QRectF>
#include <QPainter>
#include <QStyleOptionGraphicsItem>
#include <QGraphicsSceneContextMenuEvent>
#include <QGraphicsItem>

#include "MapGraphics_global.h"

class MAPGRAPHICSSHARED_EXPORT MapGraphicsObject : public QObject
{
    Q_OBJECT

public:
    enum MapGraphicsObjectFlag
    {
        ObjectIsMovable = 0x01,
        ObjectIsSelectable = 0x02,
        ObjectIsFocusable = 0x04
    };
    Q_DECLARE_FLAGS(MapGraphicsObjectFlags,MapGraphicsObjectFlag)

    //PrivateQGraphicsObject will call some of our protected event handlers that nobody else needs to touch
    friend class PrivateQGraphicsObject;
public:
    explicit MapGraphicsObject(bool sizeIsZoomInvariant = false, MapGraphicsObject *parent = nullptr);
    ~MapGraphicsObject() override;

    bool sizeIsZoomInvariant() const { return _sizeIsZoomInvariant; }

    /*!
     \brief You need to implement this. If sizeIsZoomInvariant() is true, this should return the size of the
     rectangle you want in PIXELS. If false, this should return the size of the rectangle in METERS. The
     rectangle should be centered at (0, 0) regardless.

     \return QRectF
    */
    virtual QRectF boundingRect() const = 0;

    /*!
     \brief You can reimplement this if you want. Given a point in geographic coordinates (lat/lon),
     return true if the object contains that point. Return false otherwise. The default implementation just uses
     boundingRect() to decide.

     \param geoPos
     \return bool
    */
    virtual bool contains(const QPointF &geoPos) const;

    /**
     * @brief Paints the contents of the Object in ENU coordinates if the object is not zoom invariant.
     * If it is zoom invariant, the units are pixels. That is, this painter should operate in the same
     * units as returned by boundingRect().
     * You must implement this.
     *
     * @param painter
     * @param option
     * @param widget
     */
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) = 0;

    bool enabled() const { return _enabled; }
    void setEnabled(bool);

    qreal opacity() const { return _opacity; }
    void setOpacity(qreal);

    MapGraphicsObject *parent() const { return _parent; }
    void setParent(MapGraphicsObject *);

    const QPointF &pos() const { return _pos; }
    virtual void setPos(const QPointF &);

    qreal rotation() const { return _rotation; }
    void setRotation(qreal);

    bool visible() const { return _visible; }
    void setVisible(bool);

    qreal longitude() const { return _pos.x(); }
    void setLongitude(qreal);

    qreal latitude() const { return _pos.y(); }
    void setLatitude(qreal);

    qreal zValue() const { return _zValue; }
    void setZValue(qreal);

    bool isSelected() const { return _selected; }
    void setSelected(bool);

    QString toolTip() const { return _toolTip; }
    void setToolTip(const QString &toolTip);

    MapGraphicsObject::MapGraphicsObjectFlags flags() const { return _flags; }
    void setFlag(MapGraphicsObjectFlag, bool enabled = true);
    void setFlags(MapGraphicsObject::MapGraphicsObjectFlags);

protected:
    virtual void contextMenuEvent(QGraphicsSceneContextMenuEvent *event);
    virtual QVariant itemChange(QGraphicsItem::GraphicsItemChange change, const QVariant &value);
    virtual void keyPressEvent(QKeyEvent *event);
    virtual void keyReleaseEvent(QKeyEvent *event);
    virtual void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event);
    virtual void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    virtual void mousePressEvent(QGraphicsSceneMouseEvent *event);
    virtual void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
    virtual void wheelEvent(QGraphicsSceneWheelEvent *event);

signals:
    void enabledChanged();
    void opacityChanged();
    void parentChanged();
    void posChanged();
    void rotationChanged();
    void visibleChanged();
    void zValueChanged();
    void toolTipChanged(const QString &toolTip);

    void flagsChanged();

    //Please do not use this for now. It should only be used internally for now. Ugly, I know.
    void selectedChanged();

    void newObjectGenerated(MapGraphicsObject *);

    /*!
     \brief Emitted when we'd like to be redrawn
    */
    void redrawRequested();

    /*!
     \brief Emitted when this MapGraphicsObject wants keyboard focus. (to receive keyboard events)
    */
    void keyFocusRequested();

private slots:
    void setConstructed();

private:
    MapGraphicsObject *_parent = nullptr;

    MapGraphicsObject::MapGraphicsObjectFlags _flags;
    QPointF _pos = QPointF(0.0, 0.0);
    qreal _rotation = 0.0;
    qreal _opacity = 1.0;
    qreal _zValue = 0.0;
    QString _toolTip;

    bool _constructed = false;
    bool _enabled = true;
    bool _selected = false;
    bool _visible = true;

    bool _sizeIsZoomInvariant;
};

Q_DECLARE_OPERATORS_FOR_FLAGS(MapGraphicsObject::MapGraphicsObjectFlags)

#endif // MAPGRAPHICSOBJECT_H
