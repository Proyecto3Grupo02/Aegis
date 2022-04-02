-- Example of scene, it's just a table with list of entities

local NAME = "TestScene";
local scene = {
	{
		type = "Entity",
		name = "TestEntity",
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
	},
	{
		type = "Entity",
		name = "TestEntity2",
		components = {
			{
				type = "TestComponent"
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
