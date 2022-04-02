-- Example of scene, it's just a table with list of entities

local NAME = "TestScene";
local scene = {
	{
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
					mesh = "Rust.mesh"
				}
			}
		}
	}
};
return scene;
