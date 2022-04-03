#pragma once

class AegisLight {
public:
	AegisLight(Ogre::SceneManager* sceneMng): 
		mngr_(sceneMng) {

	}
	~AegisLight() {
		mNode_->detachObject(mLight_);
	}

	void setLightOn() {
		mNode_->setVisible(true);
	}
	void initLight(Ogre::SceneNode* node) {
		mNode_ = node;
		mLight_ = mngr_->createLight();
		mNode_->attachObject(mLight_);
	}
	void setLightOff() {

		mNode_->setVisible(false);
	}


	

private:
	Ogre::SceneNode* mNode_;
	Ogre::Light* mLight_;
	Ogre::SceneManager* mngr_;
};