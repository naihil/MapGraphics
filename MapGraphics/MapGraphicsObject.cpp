#include "MapGraphicsObject.h"

#include <QtDebug>
#include <QKeyEvent>
#include <QTimer>

MapGraphicsObject::MapGraphicsObject(bool sizeIsZoomInvariant, MapGraphicsObject *parent)
    : QObject()
    , _sizeIsZoomInvariant(sizeIsZoomInvariant)
{
    this->setParent(parent);

    /*
     * When we get back to the event loop, mark us as constructed.
     * This is a hack so that we can set properties of child objects in their constructors
    */
    QTimer::singleShot(1, this, &MapGraphicsObject::setConstructed);
}

MapGraphicsObject::~MapGraphicsObject()
{
}

bool MapGraphicsObject::contains(const QPointF &geoPos) const
{
    return this->boundingRect().contains(geoPos);
}

void MapGraphicsObject::setEnabled(bool nEnabled)
{
    _enabled = nEnabled;
    if (_constructed) {
        emit this->enabledChanged();
    }
    else {
        QTimer::singleShot(1, this, &MapGraphicsObject::enabledChanged);
    }
}

void MapGraphicsObject::setOpacity(qreal nOpacity)
{
    _opacity = nOpacity;
    if (_constructed) {
        emit this->opacityChanged();
    }
    else {
        QTimer::singleShot(1, this, SIGNAL(opacityChanged()));
    }
}

void MapGraphicsObject::setParent(MapGraphicsObject *nParent)
{
    _parent = nParent;
    if (_constructed) {
        emit this->parentChanged();
    }
    else {
        QTimer::singleShot(1, this, &MapGraphicsObject::parentChanged);
    }
}

void MapGraphicsObject::setPos(const QPointF &nPos)
{
    if (nPos == _pos) {
        return;
    }

    _pos = nPos;
    if (_constructed) {
        emit this->posChanged();
    }
    else {
        QTimer::singleShot(1, this, &MapGraphicsObject::posChanged);
    }
}

void MapGraphicsObject::setRotation(qreal nRotation)
{
    if (qFuzzyCompare(nRotation, _rotation)) {
        return;
    }

    _rotation = nRotation;
    if (_constructed) {
        emit this->rotationChanged();
    }
    else {
        QTimer::singleShot(1, this, &MapGraphicsObject::rotationChanged);
    }
}

void MapGraphicsObject::setVisible(bool nVisible)
{
    if (nVisible == _visible) {
        return;
    }

    _visible = nVisible;
    if (_constructed) {
        emit this->visibleChanged();
    }
    else {
        QTimer::singleShot(1, this, &MapGraphicsObject::visibleChanged);
    }
}

void MapGraphicsObject::setLongitude(qreal nLongitude)
{
    this->setPos(QPointF(nLongitude, this->pos().y()));
}

void MapGraphicsObject::setLatitude(qreal nLatitude)
{
    this->setPos(QPointF(this->pos().x(), nLatitude));
}

void MapGraphicsObject::setZValue(qreal nZValue)
{
    if (qFuzzyCompare(nZValue, _zValue)) {
        return;
    }

    _zValue = nZValue;
    if (_constructed) {
        emit this->zValueChanged();
    }
    else {
        QTimer::singleShot(1, this, &MapGraphicsObject::zValueChanged);
    }
}

void MapGraphicsObject::setSelected(bool sel)
{
    if (_selected == sel) {
        return;
    }

    _selected = sel;
    if (_constructed) {
        emit this->selectedChanged();
    }
    else {
        QTimer::singleShot(1, this, &MapGraphicsObject::selectedChanged);
    }
}

void MapGraphicsObject::setToolTip(const QString &toolTip)
{
    if (_toolTip == toolTip) {
        return;
    }

    _toolTip = toolTip;
    emit this->toolTipChanged(toolTip);
}

void MapGraphicsObject::setFlag(MapGraphicsObject::MapGraphicsObjectFlag flag, bool enabled)
{
    if (enabled) {
        _flags = _flags | flag;
    }
    else {
        _flags = _flags & (~flag);
    }

    emit this->flagsChanged();
}

void MapGraphicsObject::setFlags(MapGraphicsObject::MapGraphicsObjectFlags flags)
{
    _flags = flags;

    if (_constructed)
        this->flagsChanged();
    else
        QTimer::singleShot(1, this, SIGNAL(flagsChanged()));
}

//protected
void MapGraphicsObject::contextMenuEvent(QGraphicsSceneContextMenuEvent *event)
{
    event->ignore();
}

//protected
QVariant MapGraphicsObject::itemChange(QGraphicsItem::GraphicsItemChange change, const QVariant &value)
{
    Q_UNUSED(change)
    return value;
}

//protected
void MapGraphicsObject::keyPressEvent(QKeyEvent *event)
{
    event->ignore();
}

//protected
void MapGraphicsObject::keyReleaseEvent(QKeyEvent *event)
{
    event->ignore();
}

//protected
void MapGraphicsObject::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event)
{
    event->ignore();
}

//protected
void MapGraphicsObject::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    event->ignore();
}

//protected
void MapGraphicsObject::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    //The default is to accept this if we are selectable and/or movable. Otherwise, ignore!
    if (this->flags() & MapGraphicsObject::ObjectIsMovable ||
            this->flags() & MapGraphicsObject::ObjectIsSelectable) {
        event->accept();
        if (this->flags() & MapGraphicsObject::ObjectIsFocusable) {
            this->keyFocusRequested();
        }
    }
    else {
        event->ignore();
    }
}

//protected
void MapGraphicsObject::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    event->ignore();
}

//protected
void MapGraphicsObject::wheelEvent(QGraphicsSceneWheelEvent *event)
{
    event->ignore();
}

//private slot
void MapGraphicsObject::setConstructed()
{
    _constructed = true;
}
