-- Example of scene, it's just a table with list of entities

local NAME = "TestScene";
local scene = {
	{
		type = "Entity",
		name = "Fish",
		position = { x = 0, y = 0, z = 0},
		components = {
			{
				type = "SimpleRotate",
				
				dependencies=
				{
					{
						entity = "Rust",
						components = {
								"TestComponent", "NonExistingComponent"
						}
					},
					{
						entity = "TestEntity3",
						components = {
								"TestComponent"
						}
					}
				}
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
		name = "Rust",
		components = {
			{
				type = "TestComponent",
				data = {
					test2 = 1,
					test4 = 3
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
