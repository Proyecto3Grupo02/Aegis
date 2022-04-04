local NAME="Light"

-- table for our functions
local table = { }

function table.GetNew(entity, args) 
    local component = Aegis.NativeComponents.createLight(entity,args);
    return component;
end
    
return table