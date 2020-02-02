#ifndef MAPGRAPHICSSCENE_H
#define MAPGRAPHICSSCENE_H

#include "MapGraphics_global.h"
#include "MapGraphicsObject.h"

#include <QObject>
#include <QList>
#include <QSet>

class MAPGRAPHICSSHARED_EXPORT MapGraphicsScene : public QObject
{
    Q_OBJECT

public:
    explicit MapGraphicsScene(QObject *parent = nullptr);
    ~MapGraphicsScene() override;

    /**
     * @brief Adds or re-parents the given MapGraphicsObject to this scene.
     *
     * @param object Added object
     */
    void addObject(MapGraphicsObject *object);

    /**
     * @brief Removes the given MapGraphicsObject from scene.
     *
     * @param object Object that needs to be removed
     */
    void removeObject(MapGraphicsObject *object);

signals:
    /**
     * @brief Fired when a MapGraphicsObject is added to the scene
     *
     * @param object The object that was added
     */
    void objectAdded(MapGraphicsObject *object);

    /**
     * @brief Fired when a MapGraphicsObject is removed from the scene.
     *
     * @param object The object that was removed
     */
    void objectRemoved(MapGraphicsObject *object);

private slots:
    void handleNewObjectGenerated(MapGraphicsObject *newObject);
    void handleObjectDestroyed(QObject *object);

private:
    QSet<MapGraphicsObject *> _objects;
};

#endif // MAPGRAPHICSSCENE_H
