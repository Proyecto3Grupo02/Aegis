-- This name is the "type" of your component, you can use it to require it in other scripts
local NAME="YourComponentName"

-- table for storing our component constructor
local table = { }

-- Constructor should receive entity and data as parameters
-- Component can access entity automatically after calling entity.addCompontent(component)
-- But you may need a reference to entity in your component before that
-- Params is the data that parse functions gives you to init your compoennt, it's assumed to be correct
function table.GetNew(entity, params) 
    local component = Aegis.CreateComponent(NAME);
    
    -- Data for your script, you can have here anything, custom methods, int, other tables... Anything, it will
    -- be stored as a LuaRef in C++
    -- All data is public, you can make a subtable for private data
    -- It's recommended to store component.data in a local data variable for ease of use
    local data = component.data;

    -- You have to define in this hable your Update, LateUpdate, FixedUpdate, OnCollision, OnTrigger
    local funcs = component.funcs;

    -- Entity has a direct access from transform
    -- Component have an entity access, component.entity but it's not recommended to use it outside methods
    -- as it could be nil, it's safer to use entity received from constructor
    local transform = entity.transform;

    -- You can edit data after setting it to component.data, as it's a ref value 

    -- You may recive params from the scene file, you can use them to initialize your component
    -- We assume params have the correct data, you can also parse it if you dont trust users of this engine
    -- You can store functions here but you shouldn
    
    -- Params usually are serialized data,
    -- parse method will set data to params (only for key matches), unless you set overrideData to false in scene definition
    -- but this params could be another type of info that the component expects. Be aware that in that case, data will always have the 
    -- same initial values for all of this components instances, unless params contains a subtable with the data, in that case you have to 
    -- parse it manually
    if params ~= nil then
        -- do stuff
    end

    -- This function is called when entity is added to scene, after all dependencies are resolved
    -- Even if the entity is disabled the first frame, Init will be called
    function Init() end;
    function Update(deltaTime) 
        if  Input:anyKeyWasPressed() then
            if Input:keyWasPressed("a") then
                -- You should use component.data instead of data
                print("Test value is " .. component.data.test);
            end
        end
    end;

    function LateUpdate(deltaTime) end;
    function FixedUpdate() end;
    function OnCollision(other) end;
    function OnTrigger(other) end;

    -- Here you asign the functions you create, if you dont need a function
    -- then better dont asign it. In C++ it checks if the function is nil and
    -- if it is not it will call it, so it's better to leave it nil so it won't call an empty function
    -- which incurs a performance penalty. That's why only fuction.update is set

    -- this is an example but you can create and assign the function directly by writing
    -- funcs.update = function(deltaTime) end; 
    funcs.update = Update;
    -- funcs.lateUpdate = lateUpdate;
    -- funcs.fixedUpate = fixedUpdate;
    -- funcs.onTrigger = onTrigger;

    return component;
end

return table