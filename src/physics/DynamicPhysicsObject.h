//
// Created by artem on 28.04.24.
//

#ifndef INC_2DSDL_DYNAMICPHYSICSOBJECT_H
#define INC_2DSDL_DYNAMICPHYSICSOBJECT_H


#include <box2d/box2d.h>

static float SCALE = 50.f;

class StaticPhysicsObject {
public:
    StaticPhysicsObject(b2World &world, float x, float y, float width, float height) {
        b2BodyDef bodyDef;
        bodyDef.position.Set(x / SCALE, y / SCALE);
        body = world.CreateBody(&bodyDef);

        b2PolygonShape shape;
        shape.SetAsBox(width / SCALE, height / SCALE);

        body->CreateFixture(&shape, 0.0f);
    }

    ~StaticPhysicsObject() {
        // Уничтожаем тело
        body->GetWorld()->DestroyBody(body);
    }

private:
    b2Body *body;
};

class DynamicPhysicsObject {
public:
    DynamicPhysicsObject(b2World &world, float x, float y, float width, float height) {
        b2BodyDef bodyDef;
        bodyDef.type = b2_dynamicBody;
        bodyDef.position.Set(x / SCALE, y / SCALE);
        body = world.CreateBody(&bodyDef);

        b2PolygonShape shape;
        shape.SetAsBox(width / SCALE, height / SCALE);

        b2FixtureDef fixtureDef;
        fixtureDef.shape = &shape;
        fixtureDef.density = 1.0f;
        fixtureDef.friction = 0.3f;
        fixtureDef.restitution = 0.5f;

        body->CreateFixture(&fixtureDef);
    }

    ~DynamicPhysicsObject() {
        // Уничтожаем тело
        body->GetWorld()->DestroyBody(body);
    }

    b2Vec2 getPosition() const {
        auto pos = body->GetPosition();
        pos *= SCALE;
        return pos;
    }

    void setPosition(float x, float y) {
        body->SetTransform(b2Vec2(x, y), body->GetAngle());
    }

    void translatePosition(float x, float y) {
        body->SetTransform(body->GetPosition() + b2Vec2(x / SCALE, y / SCALE), body->GetAngle());
    }

    void applyForce(float x, float y) {
        body->ApplyForceToCenter(b2Vec2(x, y), true);
    }

private:
    b2Body *body;
};

#endif //INC_2DSDL_DYNAMICPHYSICSOBJECT_H
