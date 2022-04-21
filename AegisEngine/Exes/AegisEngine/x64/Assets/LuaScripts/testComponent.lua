-- OUTDATED COMPONENT

local NAME="TestComponent"

local table = { }

-- i dont need arguments here
function table.GetNew(entity, args) 
    local component = Aegis.CreateComponent(NAME, entity);
    local data = component.data;
    local funcs = component.funcs;

    data.time = 0;
    component.data.time = 0;

    -- this data can be overwritten in scene creation even if you
    -- don't put the parameters in the GetNew function
    data.time = 0;
    data.test = 0;
    data.test2 = 0;

    function Init() 
        -- notice how calling component.entity is safe here, but could use
        -- constructor parameters too
        local entName = component.entity:GetName();
        print("Init: " .. component.name .. " from " .. entName);
    end;

    -- move entity with the keys, press h to print debug info
    function Update(deltaTime) 
        local num = 5;
        local transform = component.entity.transform;

        if  Input:AnyKeyWasPressed() then
        
            if Input:KeyWasPressed("h") then
                print("Test value is " .. data.test);
            -- elseif Input:KeyWasPressed("a") then
            --     print("A key was pressed this frame in lua")
            --     transform.position = Aegis.Maths.Vector3(-num,0, 0); 
            -- elseif Input:KeyWasPressed("w") then
            --     print("W key was pressed this frame in lua")
            --     transform.position = Aegis.Maths.Vector3(0,num, 0); 
            -- elseif Input:KeyWasPressed("s") then
            --     print("S key was pressed this frame in lua")
            --     transform.position = Aegis.Maths.Vector3(0,-num, 0); 
            -- elseif Input:KeyWasPressed("d") then
            --     print("D key was pressed this frame in lua")
            --     transform.position = Aegis.Maths.Vector3(num,0, 0); 
            end
        end

        -- timer, be aware that compound operators don't exist in lua
        data.time = data.time + deltaTime;
        
        -- if time is bigger than 0 obtain meshRenderer and setvisible to false
        local meshRenderer = component.entity:GetComponent("Renderer").type;

        -- the code below works, uncomment to see it in action
        -- if math.sin(data.time) > 0 then
        --     meshRenderer.visible = false;
        -- else
        --     meshRenderer.visible = true;
        -- end

        transform.position = Aegis.Maths.Vector3(math.sin(data.time) * 5,0, 0); 
    end;

    funcs.update = Update;

    return component;
end

return table