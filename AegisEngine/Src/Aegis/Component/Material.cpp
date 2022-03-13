#include "Material.h"
#include "Entity.h"
#include "Renderer.h"
Material::Material(): AegisComponent(), mMaterialName_("")
{
}

Material::Material(std::string matName): 
	AegisComponent(), mMaterialName_(matName)
{
	ComponentManager::getInstance()->RegisterComponent<Material>("Material");
}

Material::~Material()
{
}

void Material::init()
{
	mRenderer_ = getEntity()->getComponent<Renderer>();
	assert(mRenderer_);
	if (mMaterialName_ != "") {
		mRenderer_->getMesh()->setMaterialName(mMaterialName_);
	}
}

