#include <vector>
#include <list>
#include <string>

class Component;
class Scene;
class Entity{
    public:
        Entity();
        ~Entity();

        //when a entity is created is called
        void init();
       
        
        void fixedUpdate();
        void update();
        void lateUpdate();

        void render();

        inline bool isActive(){return active_;}
        inline void setActive(bool act){active_=act;}

        
        inline std::string getName(){return mName_;}
        inline void setName(std::string name){}

        //handle the components
        void addComponent(Component* component);
        void removeComponent(Component* component);
        Component* getComponent(unsigned int cmpID);

        inline Scene* getScene(){return mScene_;}
        inline void setScene(Scene* scene){mScene_= scene;}
        //doubt
        void receiveEvent(Entity* receive);
        bool hasComponent(unsigned int cmpID);
        void onCollision(Entity* other); 
        void onTrigger(Entity* other);

    protected:
        Scene* mScene_; //scene pointer 

        std::vector<Component*> mComponents_; //list of all the components in scene
        std::list<int> numOfActiveComponents_; //list of the index of their active component 
        bool active_; //bool to check if the entity is active or not
    private:
        std::string mName_; //name of the entity, works like a tag, useful to debug


};