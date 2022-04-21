-- Wrapper for native component renderer, so it can be used in "json" style and parsed correctly
local NAME="Animation"

-- table for our functions
local table = { }
table.isNative = true

function table.GetNew(entity, args) 
    local component = Aegis.NativeComponents.CreateAnimation(entity, args);
    return component;
end

return table