-- Example of scene, it's just a table with list of entities

local NAME = "CopiedScene";
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
				},
				dependencies=
				{
					{
						entity = "TestEntity",
						components = {
								"TestComponent"
						}
					}
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
