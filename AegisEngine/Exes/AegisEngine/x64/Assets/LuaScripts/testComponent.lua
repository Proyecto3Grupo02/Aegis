-- capture the name searched for by require
local NAME="testComponent"

-- table for our functions
local table = { }

function table.GetNew() 
    local component = ECS.CreateComponent();
    
    print(component)

    local data = {};
    data.two = 2;
    data.hola = "hola";
    data.time = 0;
   
    --local entity = component:getEntity().transform;
    component.data = data;
    local updateLocal = 
    function(a) 
        data.time = data.time + a;
        --component:getEntity().transform.position = ECS.Vector3(0,0,0);
        --print("Update from lua " .. data.time .. "  :" .. math.sin(data.time)); 
         --print("Update from lua " .. entity:getName()); 
         print("Update from lua ");
         --print(component.entity.transform.position.x) 
         print(component.entity.transform.position.y) 
         component.entity.transform.position = ECS.Vector3(0,math.sin(data.time) * 10,0); 
    end;
    component.update = updateLocal;
    component.name = "testComponent";
    data.update = updateLocal;

    return component;
end

return table