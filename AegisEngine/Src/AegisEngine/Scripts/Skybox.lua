local NAME="Skybox"

-- table for our functions
local table = { }
table.isNative = true

function table.GetNew(entity, args) 
    local component = Aegis.NativeComponents.CreateSkybox(entity,args.material);
    return component;
end
    
return table;