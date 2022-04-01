local NAME="TestScene"

--create local scene2 that contains testEnt

local scene =
{
testEnt = {
    type = "Entity",
    name = "TestEntity",
    components = {
    {
        type = "TestComponent",
        data = {
            test = 10,
            time = 0
        }
    }, 
    {
        type = "Renderer",
        data = {
            mesh = "fish.mesh"
        }
    }}
    }
}

return scene;