-- capture the name searched for by require
local NAME="testComponent"

-- table for our functions
local table = { }

function table.GetNew() 
    local component = ECS.CreateComponent();
    
    -- Name of the component used to idenfity at runtime, do not change, don't use same name for various components
    component.name = "testComponent";

    -- Data for your script, you can have here anything, custom methods, int, other tables... Anything, it will
    -- be stored as a LuaRef in C++
    local data = {};
    data.time = 0;
    
    -- callbacks, here you define update, lateUpdate,fixedUpdate, onCollisino and onTrigger
    local funcs = {};
    
    -- Set data to component, otherwise you won't be able to access component data from other scripts
    -- All data is public, optionally I can make a private data that isn't exported to lua as property
    component.data = data;

    -- update definition
    function update(deltaTime) 
        local num = 5;
        local transform = component.entity.transform;
        
        if Input:isKeyPressedThisFrame("a") then
            print("A key was pressed in lua")
            transform.position = ECS.Vector3(-num,0, 0); 
        elseif Input:isKeyPressedThisFrame("w") then
            print("W key was pressed in lua")
            transform.position = ECS.Vector3(0,num, 0); 
        elseif Input:isKeyPressedThisFrame("s") then
            print("S key was pressed in lua")
            transform.position = ECS.Vector3(0,-num, 0); 
        elseif Input:isKeyPressedThisFrame("d") then
            print("D key was pressed in lua")
            transform.position = ECS.Vector3(num,0, 0); 
        end
        
        data.time = data.time + deltaTime;
        --component.entity.transform.position = ECS.Vector3(math.sin(data.time) * 10,0, 0); 
    end;

    function lateUpdate() end;
    function lateUpdate(deltaTime) end;
    function fixedUpdate() end;
    function onCollision(other) end;
    function onTrigger(other) end;

    funcs.update = update;
    funcs.lateUpdate = lateUpdate;
    funcs.fixedUpate = fixedUpdate;
    funcs.onTrigger = onTrigger;

    component:setCallbacks(funcs);
    return component;
end

return table