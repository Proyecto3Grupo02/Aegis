#include "Material.h"
#include "Entity.h"
#include "Renderer.h"
Material::Material(): AegisComponent(), mMaterialName_("")
{
}

Material::Material(std::string matName): 
	AegisComponent(), mMaterialName_(matName)
{
}

Material::~Material()
{
}

void Material::init()
{
	mRenderer_ = getEntity()->getComponent<Renderer>();
	assert(mRenderer_);

	mRenderer_->getMesh()->setMaterialName(mMaterialName_);
}
