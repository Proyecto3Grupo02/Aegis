-- Wrapper for native component renderer, so it can be used in "json" style and parsed correctly
local NAME="Renderer"

-- table for our functions
local table = { }

function table.GetNew(entity, data) 
    local component = Aegis.NativeComponents.CreateRenderer();
    component:init(entity, data.mesh);

    return component;
end

return table