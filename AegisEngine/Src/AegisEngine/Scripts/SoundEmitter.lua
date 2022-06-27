local NAME="SoundEmitter"

-- table for our functions
local table = { }
table.isNative = true

function table.GetNew(entity, args) 
    local component = Aegis.NativeComponents.createSoundEmitter(entity,args.sound);
    return component;
end
    
return table;