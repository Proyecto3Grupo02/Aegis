-- test component as example

local NAME="TestComponent"

local table = { }

-- i dont need arguments here
function table.GetNew() 
    local component = Aegis.CreateComponent(NAME);

    local data = {};
    component.data = data;

    -- data is a ref, you can't modify it after setting to component
    data.time = 0;
    data.test = 1;

    -- move entity with the keys, press h to print debug info
    function Update(deltaTime) 
        local num = 5;
        local transform = component.entity.transform;

        if  Input:AnyKeyWasPressed() then
        
            if Input:KeyWasPressed("h") then
                print("Test value is " .. component.data.test);
            elseif Input:KeyWasPressed("a") then
                print("A key was pressed this frame in lua")
                transform.position = Aegis.Maths.Vector3(-num,0, 0); 
            elseif Input:KeyWasPressed("w") then
                print("W key was pressed this frame in lua")
                transform.position = Aegis.Maths.Vector3(0,num, 0); 
            elseif Input:KeyWasPressed("s") then
                print("S key was pressed this frame in lua")
                transform.position = Aegis.Maths.Vector3(0,-num, 0); 
            elseif Input:KeyWasPressed("d") then
                print("D key was pressed this frame in lua")
                transform.position = Aegis.Maths.Vector3(num,0, 0); 
            end
        end

        data.time = data.time + deltaTime;
        
        -- if time is bigger than 0 obtain meshRenderer and setvisible to false
        local meshRenderer = component.entity:GetComponent("Renderer").type;

        if math.sin(data.time) > 0 then
            meshRenderer.visible = false;
        else
            meshRenderer.visible = true;
        end

        -- Quit comment below to see the entity position changing
        transform.position = Aegis.Maths.Vector3(math.sin(data.time) * 10,0, 0); 
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