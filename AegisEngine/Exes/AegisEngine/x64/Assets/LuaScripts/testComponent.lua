-- capture the name searched for by require
local NAME="testComponent"

-- table for our functions
local table = { }

function table.GetNew() 
    local component = ECS.CreateComponent();
    
    local data = {};
    data.two = 2;
    data.hola = "hola";
    component:SetData(data);
    component.update = (function(a) print("Update from lua " .. data.two) end);
    component.name = "testComponent";

    return component;
end

return table