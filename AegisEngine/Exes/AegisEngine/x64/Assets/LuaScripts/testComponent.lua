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
    data.time = 13;
    
    -- Set data to component, otherwise you won't be able to access component data from other scripts
    -- All data is public, optionally I can make a private data that isn't exported to lua as property
    component.data = data;

    -- update definition
    function update(a) 
        data.time = data.time + a;
        component.entity.transform.position = ECS.Vector3(math.sin(data.time) * 10,0, 0); 
    end;

    component:setUpdate(update);
    data.update = update;

    return component;
end

return table