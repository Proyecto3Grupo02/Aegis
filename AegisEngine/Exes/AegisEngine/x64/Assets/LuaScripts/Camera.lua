local NAME="Camera"

-- table for our functions
local table = { }

function table.GetNew(entity, args) 
    local component = Aegis.NativeComponents.CreateCamera(entity,args.name, args.main);
    return component;
end
    
return table