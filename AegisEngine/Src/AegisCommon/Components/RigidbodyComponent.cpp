#include "RigidbodyComponent.h"

#include "Entity.h"
#include "GameLoopData.h"
#include "MathUtils.h"

#include <Scene.h>

RigidbodyComponent::RigidbodyComponent(Entity* ent, std::string bodyMeshName, float m, bool useG, bool isK, bool isT, float scale)
	: AegisComponent("Rigidbody", ent)
{
	transform = ent->getTransform();
	initialPos = transform->getPosition();

	auto rot = transform->getRotation();
	Vector4 rotVec(rot.x, rot.y, rot.z, rot.w);
	rigidbody = new RigidBody(bodyMeshName, transform->getPosition(), transform->getScale() * scale, rotVec, this, m, useG, isK, isT);
	mEntity_->getScene()->addPhysicsEntity(this);
	setDataAsInnerType(this);
}

RigidbodyComponent::~RigidbodyComponent()
{
	if (rigidbody)
		delete rigidbody;
	mEntity_->getScene()->removePhysicsEntity(this->physicsEntityIt);
	rigidbody = nullptr;
};

void RigidbodyComponent::lateUpdate(float deltaTime) {}

void RigidbodyComponent::fixedUpdate() {

}

void RigidbodyComponent::syncTransformToRigidbody()
{
	Vector3 updatedPos = rigidbody->getRbPosition();
	auto quat = rigidbody->getRotation();
	Ogre::Quaternion ogreQuat(quat.w, quat.x, quat.y, quat.z);
	TransformComponent* t = transform;

	// Si el transform tiene padre debe tenerse en cuenta, ya que sus coordenadas son locales (relativas a las del padre) mientras que las del rigidBody son globales
	while (t->hasParent())
	{
		updatedPos = updatedPos - t->getParent()->getTransform()->getPosition();
		t = t->getParent()->getTransform();
	}
	transform->setPosition(updatedPos);
	transform->setRotation(ogreQuat);
}

// Syncs rigidbody to match transform but only for position
void RigidbodyComponent::syncRigidbodyToTransform()
{
	Vector3 rbPos = rigidbody->getRbPosition();
	Vector3 tPos = transform->getPosition();

	if ((rbPos - tPos).magnitudeSquared() >= 0.01f)
		rigidbody->setRbPosition(tPos);


}

void RigidbodyComponent::setIterator(std::list<RigidbodyComponent*>::iterator physicsEntityIt)
{
	this->physicsEntityIt = physicsEntityIt;
}

bool RigidbodyComponent::isActive() const
{
	return rigidbody->isActive();
}

void RigidbodyComponent::addForce(Vector3 force) {
	rigidbody->addForce(force);
}

Vector3 RigidbodyComponent::accelerateTo(Vector3 targetVelocity, float maxAcceleration)
{
	return rigidbody->accelerateTo(targetVelocity, GameLoopData::getInstance()->getDeltaTime(), maxAcceleration);
}

Vector3 RigidbodyComponent::accelerateToRand()
{
	Vector3 vec(rand() % 10, 0, rand() % 10);
	return rigidbody->accelerateTo(vec, GameLoopData::getInstance()->getDeltaTime(), 100000000000);
	rigidbody->setLinearVelocity();
}

void RigidbodyComponent::addForceForward(float force) {
	Vector3 rot = transform->getForward();
	addForce(rot * force);
}

void RigidbodyComponent::resetForce()
{
	rigidbody->clearForces();
}

void RigidbodyComponent::addTorque(Vector3 torque) {
	rigidbody->addTorque(torque);
}

Vector3 RigidbodyComponent::getForce() const {
	return rigidbody->getTotalForce();
}

Vector3 RigidbodyComponent::getPosition() const {
	return rigidbody->getRbPosition();
}

void RigidbodyComponent::setPosition(Vector3 pos) {
	rigidbody->setRbPosition(pos);
}

void RigidbodyComponent::setRotationEuler(Vector3 rot) {
	Vector4 eulerRot = MathUtils::EulerToVec4(rot);
	rigidbody->setRbRotation(eulerRot);
}

//FREEZE ROT------------------------------------------------------------------------------------------------
void RigidbodyComponent::freezeRot(bool _x, bool _y, bool _z) {
	rigidbody->setFreezeRotation(_x, _y, _z);
}

//GRAVITY----------------------------------------------------------------------------------------------------
bool RigidbodyComponent::getUsingGravity()const {
	return rigidbody->getUseGravity();
}

void RigidbodyComponent::setUsingGravity(bool g_) {
	rigidbody->setUsingGravity(g_);
}

//LUA-------------------------------------------------------------------------------------------------------
RigidbodyComponent* CreateRigidbody(Entity* ent, LuaRef args) //Doesn't belong to this class
{
	std::string bodyName = ent->getName();
	float mass = LuaMngr->parseFloat(args["mass"], 1);
	bool useGravity = LuaMngr->parseBool(args["useGravity"], true);
	bool isKinematic = LuaMngr->parseBool(args["isKinematic"], false);
	bool isTrigger = LuaMngr->parseBool(args["isTrigger"], false);
	float scale = LuaMngr->parseFloat(args["scale"], 1);
	return new RigidbodyComponent(ent, bodyName, mass, useGravity, isKinematic, isTrigger, scale);
}

void RigidbodyComponent::enableCollision(bool enable_) {
	if (enable_)
	{
		rigidbody->enableCol();
	}
	else rigidbody->disableCol();
}

void RigidbodyComponent::ConvertToLua(lua_State* state)
{
	getGlobalNamespace(state).
		beginNamespace("Aegis").
		beginNamespace("NativeComponents").
		addFunction("CreateRigidbody", CreateRigidbody).
		deriveClass<RigidbodyComponent, AegisComponent>("Rigidbody").
		addProperty("position", &RigidbodyComponent::getPosition, &RigidbodyComponent::setPosition).
		addProperty("useGravity", &RigidbodyComponent::getUsingGravity, &RigidbodyComponent::setUsingGravity).
		addFunction("AddForce", &RigidbodyComponent::addForce).
		addFunction("GetForce", &RigidbodyComponent::getForce).
		addFunction("ClearForce", &RigidbodyComponent::resetForce).
		addFunction("AccelerateTo", &RigidbodyComponent::accelerateTo).
		addFunction("AccelerateToRand", &RigidbodyComponent::accelerateToRand).
		addFunction("AddTorque", &RigidbodyComponent::addTorque).
		addFunction("AddForceForward", &RigidbodyComponent::addForceForward).
		addFunction("ChangeGravity", &RigidbodyComponent::changeGravity).
		addFunction("RayCastWorld", &RigidbodyComponent::raycast).
		addFunction("SetRotationEuler", &RigidbodyComponent::setRotationEuler).
		addFunction("SetPosition", &RigidbodyComponent::setPosition).
		addFunction("SetAngular", &RigidbodyComponent::setAngular).
		addFunction("FreezeRot", &RigidbodyComponent::freezeRot).
		addProperty("isActive", &RigidbodyComponent::isActive).
		addFunction("EnableCol", &RigidbodyComponent::enableCollision).

		endClass().
		endNamespace().
		endNamespace();
}

void RigidbodyComponent::changeGravity(Vector3 acc)
{
	rigidbody->changeGravity(acc);
}

int RigidbodyComponent::raycast(Vector3 origin, Vector3& dir, float distance)
{
	dir = origin + dir.getNormalized() * distance;
	return rigidbody->rayCast(origin, dir);
}
