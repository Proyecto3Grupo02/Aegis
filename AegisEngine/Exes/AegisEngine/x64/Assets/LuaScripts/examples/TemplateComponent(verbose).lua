-- This name is the "type" of your component, you can use it to require it in other scripts
local NAME="YourComponentName"

-- table for storing our component constructor
local table = { }

-- Constructor should receive entity and data as parameters
-- Component can access entity automatically after calling entity.addCompontent(component)
-- But you may need a reference to entity in your component before that
-- Params is the data that parse functions gives you to init your compoennt, it's assumed to be correct
function table.GetNew(entity, params) 
    local component = Aegis.CreateComponent();
    
    -- Name of the component used to idenfity at runtime, do not change, don't use same name for various components
    component.name = NAME;

    -- Data for your script, you can have here anything, custom methods, int, other tables... Anything, it will
    -- be stored as a LuaRef in C++
    local data = {};
    -- Set data to component, otherwise you won't be able to access component data from other scripts
    -- All data is public
    component.data = data;

    -- You can edit data after setting it to component.data, as it's a ref value 

    -- You may recive params from the scene file, you can use them to initialize your component
    -- We assume params have the correct data, you can also parse it if you dont trust users of this engine
    -- You can store functions here but you shouldn
    -- parse method will set data to params anyway, unless you set overrideData to false in scene definition
    if params ~= nil then
        data = params;
    else
        -- These are your custom variables, params shuould have the same amount of variables with the sanme
        -- name as in this section
        data.thing = "this is a string";
        data.test = 1;
    end



    function update(deltaTime) 
        if  Input:anyKeyWasPressed() then
            if Input:keyWasPressed("a") then
                -- You should use component.data instead of data
                print("Test value is " .. component.data.test);
            end
        end
    end;

    function lateUpdate() end;
    function lateUpdate(deltaTime) end;
    function fixedUpdate() end;
    function onCollision(other) end;
    function onTrigger(other) end;

    -- callbacks, here you define update, lateUpdate,fixedUpdate, onCollisino and onTrigger
    -- you should define here too custom functions, helper functions and any kind of function, data
    -- can also store functions but you should keep that for... data, you know
    local funcs = {};
    

    -- Here you asign the functions you create, if you dont need a function
    -- then better dont asign it. In C++ it checks if the function is nil and
    -- if it is not it will call it, so it's better to leave it nil so it won't call an empty function
    -- which incurs a performance penalty. That's why only fuction.update is set
    funcs.update = update;
    -- funcs.lateUpdate = lateUpdate;
    -- funcs.fixedUpate = fixedUpdate;
    -- funcs.onTrigger = onTrigger;

    -- Set the functions to the component, if you dont do this
    -- your component will not have any functions, only data (which you may want in some case)
    component:setCallbacks(funcs);
    return component;
end

return table