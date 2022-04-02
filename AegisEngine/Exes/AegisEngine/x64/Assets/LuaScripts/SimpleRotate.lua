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

        transform.localEulerAngles = Aegis.Maths.Vector3(0,0, data.time);
        print(transform.localEulerAngles.z);

        data.time = data.time + deltaTime;
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