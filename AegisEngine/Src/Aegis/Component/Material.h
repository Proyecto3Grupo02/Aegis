
#pragma once
#ifndef MATERIAL_CMP
#define MATERIAL_CMP
#include "AegisComponent.h"

namespace AegisEngine {
	class Renderer;

	class Material : public AegisComponent {
	public:
		Material();
		Material(std::string matName);
		virtual ~Material();

		virtual void init();

	private:
		Renderer* mRenderer_;
		std::string mMaterialName_;
	};
}
#endif