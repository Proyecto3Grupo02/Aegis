-- test component as example

local NAME="SimpleRotate"

local table = { }

-- i dont need arguments here
function table.GetNew() 
    local component = Aegis.CreateComponent(NAME);

    local data = {};
    component.data = data;

    -- data is a ref, you can't modify it after setting to component
    data.time = 0;

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
        io.write("x: " .. transform.localEulerAngles.x);
        io.write(" y: " .. transform.localEulerAngles.y);
        print(" z: " .. transform.localEulerAngles.z);

    end;

    function LateUpdate(deltaTime) end;
    function FixedUpdate() end;
    function OnCollision(other) end;
    function OnTrigger(other) end;

    local funcs = {};
    funcs.update = Update;

    component:SetCallbacks(funcs);
    return component;
end

return table