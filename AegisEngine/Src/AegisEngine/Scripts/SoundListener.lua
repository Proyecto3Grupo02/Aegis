local NAME="SoundListener"

-- table for our functions
local table = { }
table.isNative = true

function table.GetNew(entity) 
    local component = Aegis.NativeComponents.CreateSoundListener(entity);
    return component;
end
    
return table;