#ifndef SCENE_H
#define SCENE_H

#include <QtCore/QObject>

#include <Qt3DCore/qentity.h>
#include <Qt3DCore/qtransform.h>

#include <Qt3DExtras/QTorusMesh>
#include <Qt3DExtras/QConeMesh>
#include <Qt3DExtras/QCylinderMesh>
#include <Qt3DExtras/QCuboidMesh>
#include <Qt3DExtras/QPlaneMesh>
#include <Qt3DExtras/QSphereMesh>
#include <Qt3DExtras/QPhongMaterial>

class Scene : public QObject
{
    Q_OBJECT
private:
    Qt3DCore::QEntity *m_rootEntity;
    Qt3DExtras::QTorusMesh *m_torus;
    Qt3DCore::QEntity *m_coneEntity;
    Qt3DCore::QEntity *m_cylinderEntity;
    Qt3DCore::QEntity *m_torusEntity;
    Qt3DCore::QEntity *m_cuboidEntity;
    Qt3DCore::QEntity *m_planeEntity;
    Qt3DCore::QEntity *m_sphereEntity;

public:
    explicit Scene(Qt3DCore::QEntity *rootEntity);
    ~Scene();
};

#endif // SCENE_H
