#include "MapGraphicsScene.h"

#include <QtDebug>

MapGraphicsScene::MapGraphicsScene(QObject *parent)
    : QObject(parent)
{
}

MapGraphicsScene::~MapGraphicsScene()
{
    foreach(MapGraphicsObject * obj, _objects)
        this->removeObject(obj);
}

void MapGraphicsScene::addObject(MapGraphicsObject *object)
{
    if (object == nullptr) {
        return;
    }

    connect(object, &MapGraphicsObject::newObjectGenerated, this, &MapGraphicsScene::handleNewObjectGenerated);
    connect(object, &MapGraphicsObject::destroyed, this, &MapGraphicsScene::handleObjectDestroyed);

    _objects.insert(object);
    emit objectAdded(object);
}

void MapGraphicsScene::removeObject(MapGraphicsObject *object)
{
    _objects.remove(object);
    this->objectRemoved(object);
}

//private slot
void MapGraphicsScene::handleNewObjectGenerated(MapGraphicsObject *newObject)
{
    this->addObject(newObject);
}

//private slot
void MapGraphicsScene::handleObjectDestroyed(QObject *object)
{
    /*
      We have to be careful with this casted pointer as technically at this point the MapGraphicsObject
      portion of it has been destroyed. This signal comes from the QObject destructor.
    */
    MapGraphicsObject *mgObj = (MapGraphicsObject*)object;

    this->removeObject(mgObj);
}
