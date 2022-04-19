-- Wrapper for native component renderer, so it can be used in "json" style and parsed correctly
local NAME="Rigidbody"

-- table for our functions
local table = { }

function table.GetNew(entity, args) 
    local component = Aegis.NativeComponents.CreateRigidbody(entity, args);
    return component;
end

return table