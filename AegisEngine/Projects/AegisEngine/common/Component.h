
class Entity;
class Component{
    public:
       Component() {};
       ~Component() {};

       inline Entity* getEntity() { return mEntity_; }

       virtual void init()=0;
       virtual void fixedUpdate() = 0;
       virtual void update()=0;
       virtual void lateUpdate()=0;
       virtual void render() = 0;

       virtual void onCollision(Entity* other)=0;
       virtual void onTrigger(Entity* other)=0;
    private:
        unsigned int mID_;
        Entity* mEntity_;
        
};


