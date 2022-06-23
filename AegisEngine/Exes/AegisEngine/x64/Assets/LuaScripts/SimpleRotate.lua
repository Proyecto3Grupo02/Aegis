-- test component as example

local NAME="SimpleRotate"

local table = { }

-- i dont need arguments here
function table.GetNew(entity, args) 
    local component = Aegis.CreateComponent(NAME, entity);
    local data = component.data;
    local funcs = component.funcs;

    -- data is a ref, you can't modify it after setting to component
    data.time = 0;

    function Init() 
        local entName = component.entity:GetName();
        -- print("Init: " .. component.name .. " from " .. entName);
        -- local rust = component.external.Test;
        -- print("EntityDependency: " .. rust.entity:GetName());
        -- print("ComponentDependenty: " .. rust.TestComponent.name);
        -- rust.TestComponent.data.test = 5;
        -- print("ComponentTest2: " .. rust.TestComponent.data.test2);

        -- -- this will throw a warning through console, you can modify component.data
        -- -- but you can't override it
        -- component.data = {}

        -- -- the code below would work
        -- --component.data.time = 2;

        -- -- notice how it's not the same address
        -- io.write("ComponentData: ") print(component.data)
        -- io.write("Local Data: ") print(data)
    end;

    -- move entity with the keys, press h to print debug info
    function Update(deltaTime) 
        local num = 5;
        local transform = component.entity.transform;
        data.time = data.time + deltaTime;

        -- x pitch
        -- y yaw
        -- z roll
        local zVec = Aegis.Maths.Vector3(0,0,0.5);
        transform.localEulerAngles = (transform.localEulerAngles) + zVec;
        
        -- io.write("x: " .. transform.localEulerAngles.x);
        -- io.write(" y: " .. transform.localEulerAngles.y);
        -- print(" z: " .. transform.localEulerAngles.z);

    end;

    funcs.init = Init;
    funcs.update = Update;
    return component;
end

return table