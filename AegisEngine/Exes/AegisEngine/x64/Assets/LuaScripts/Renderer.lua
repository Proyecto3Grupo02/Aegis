-- capture the name searched for by require
local NAME="Renderer"

-- table for our functions
local table = { }

function table.GetNew(entity, data) 
    local component = ECS.CreateRenderer();
    component:init(entity, data.mesh);

    return component;
end

return table