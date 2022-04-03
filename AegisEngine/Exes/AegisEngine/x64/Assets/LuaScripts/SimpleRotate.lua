-- test component as example

local NAME="SimpleRotate"

local table = { }

-- i dont need arguments here
function table.GetNew() 
    local component = Aegis.CreateComponent(NAME);
    data = component.data;

    -- data is a ref, you can't modify it after setting to component
    data.time = 0;

    function Init() 
        local entName = component.entity:GetName();
        print("Init: " .. component.name .. " from " .. entName);
        local rust = component.external.Rust;
        print("EntityDependency: " .. rust.entity:GetName());
        print("ComponentDependenty: " .. rust.TestComponent.name);
        rust.TestComponent.data.test = 5;
        print("ComponentTest2: " .. rust.TestComponent.data.test2);
    end;

    -- move entity with the keys, press h to print debug info
    function Update(deltaTime) 
        local num = 5;
        local transform = component.entity.transform;
        data.time = data.time + deltaTime;

        -- x pitch
        -- y yaw
        -- z roll
        local zVec = Aegis.Maths.Vector3(0,0,1);
        transform.localEulerAngles = (transform.localEulerAngles) + zVec;
        -- io.write("x: " .. transform.localEulerAngles.x);
        -- io.write(" y: " .. transform.localEulerAngles.y);
        -- print(" z: " .. transform.localEulerAngles.z);

    end;

    function LateUpdate(deltaTime) end;
    function FixedUpdate() end;
    function OnCollision(other) end;
    function OnTrigger(other) end;

    local funcs = {};
    funcs.init = Init;
    funcs.update = Update;

    component:SetCallbacks(funcs);
    return component;
end

return table