-- Example of scene, it's just a table with list of entities

local NAME = "TestScene";
local scene = {
	{
		type = "Entity",
		name = "Fish",
		position = { x = 0, y = 0, z = 0},
		scale = { x = 0.5 },
		components = {
			{
				type = "SimpleRotate",
				dependencies=
				{
					{
						entity = "Rust",
						name = "Test",
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
					mesh = "fish.mesh",
					material= "red"
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
					mesh = "Rust.mesh",
					material="red"
				}
			}
		}
	},

	{
		type = "Entity",
		name = "light",
		position = { x = 0, y = 0, z = 0},
		components = {
			{
				type = "Light",
				data = {
					color_r=0.1,
					color_g=0.1,
					color_b=0.1,

					spec_r=0.1,
					spec_g=0.1,
					spec_b=0.1
				}
			}
		}
	}
};
return scene;
