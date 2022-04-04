-- Wrapper for native component renderer, so it can be used in "json" style and parsed correctly
local NAME="Renderer"

-- table for our functions
local table = { }

function table.GetNew(entity, args) 
    local component = Aegis.NativeComponents.CreateRenderer(entity, args.mesh, args.material);
    print(args.material);

    return component;
end

return table