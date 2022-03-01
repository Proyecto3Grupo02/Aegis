#include <vector>
#include <list>
#include <string>

class Component;
class Scene;
class Entity{
    public:
        Entity();
        ~Entity();

        void init();
        void fixedUpdate();
        void update();
        void lateUpdate();

        void render();

        inline bool isActive(){return active_;}
        inline void setActive(bool act){active_=act;}

        inline std::string getName(){return mName_;}
        inline void setName(std::string name){}

        inline Scene* getScene(){return mScene_;}
        inline void setScene(Scene* scene){mScene_= scene;}
        //handle the components
        void addComponent(Component* component);
        void removeComponent(Component* component);
        Component* getComponent(unsigned int cmpID);

        //doubt
        void receiveEvent();
        bool hasComponent(unsigned int cmpID);
        void onCollision(Entity* other); 
        void onTrigger(Entity* other);

    protected:
        Scene* mScene_;
        std::vector<Component*> mComponents_;
        int numOfActiveComponents_;
        bool active_;
    private:
        std::string mName_;


};