local NAME="SoundEmitter"

-- table for our functions
local table = { }
table.isNative = true

function table.GetNew(entity, args) 
    local component = Aegis.NativeComponents.CreateSoundEmitter(entity,args);
    return component;
end
    
return table;