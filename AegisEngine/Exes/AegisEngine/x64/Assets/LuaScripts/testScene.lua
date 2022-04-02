-- Example of scene, it's just a table with list of entities

local NAME = "TestScene";
local scene = {
	{
		type = "Entity",
		name = "TestEntity",
		position = { x = 0, y = 0, z = 0},
		components = {
			{
				type = "SimpleRotate"
			},
			{
				type = "Renderer",
				data = {
					mesh = "fish.mesh"
				}
			}
		}
	}
};
return scene;
