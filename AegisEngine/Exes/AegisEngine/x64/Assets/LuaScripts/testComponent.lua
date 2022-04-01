-- capture the name searched for by require
local NAME="testComponent"

-- table for our functions
local table = { }

function table.GetNew() 
    local component = ECS.CreateComponent();
    
    -- Name of the component used to idenfity at runtime, do not change, don't use same name for various components
    component.name = "TestComponent";

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
        local transform = component.entity:getComponent("Transform");
        --local transform = component.entity.transform;

        if  Input:anyKeyWasPressed() then
        
            if Input:keyWasPressed("a") then
                print("A key was pressed this frame in lua")
                transform.position = ECS.Vector3(-num,0, 0); 
            elseif Input:keyWasPressed("w") then
                print("W key was pressed this frame in lua")
                transform.position = ECS.Vector3(0,num, 0); 
            elseif Input:keyWasPressed("s") then
                print("S key was pressed this frame in lua")
                transform.position = ECS.Vector3(0,-num, 0); 
            elseif Input:keyWasPressed("d") then
                print("D key was pressed this frame in lua")
                transform.position = ECS.Vector3(num,0, 0); 
            end
        end
        
        if  Input:anyKeyIsDown() then
        
            if Input:isKeyDown("a") then
                print("A key was down in lua")
                transform.position = ECS.Vector3(-num,0, 0); 
            elseif Input:isKeyDown("w") then
                print("W key was down in lua")
                transform.position = ECS.Vector3(0,num, 0); 
            elseif Input:isKeyDown("s") then
                print("S key was down in lua")
                transform.position = ECS.Vector3(0,-num, 0); 
            elseif Input:isKeyDown("d") then
                print("D key was down in lua")
                transform.position = ECS.Vector3(num,0, 0); 
            end
        end

        if  Input:anyKeyWasReleased() then
        
            if Input:keyWasReleased("a") then
                print("A key was released in lua")
                transform.position = ECS.Vector3(-num,0, 0); 
            elseif Input:keyWasReleased("w") then
                print("W key was released in lua")
                transform.position = ECS.Vector3(0,num, 0); 
            elseif Input:keyWasReleased("s") then
                print("S key was released in lua")
                transform.position = ECS.Vector3(0,-num, 0); 
            elseif Input:keyWasReleased("d") then
                print("D key was released in lua")
                transform.position = ECS.Vector3(num,0, 0); 
            end
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