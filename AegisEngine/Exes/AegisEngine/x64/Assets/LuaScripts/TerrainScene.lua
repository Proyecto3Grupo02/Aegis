-- Example of scene, it's just a table with list of entities

local NAME = "TerrainScene";
local scene = {
	{
		type = "MainCamera",
		position = { z = 10, y = 3  },
		components = {
			{
				type = "CameraTest"
			}
		}
	},
	{
		type = "Entity",
		name = "Player",
		position = {x = -5, y = -50},
		components = {
			{
				type = "Renderer",
				data = {
					mesh = "Cube.mesh",
					material= "playerMat"
				}
			},
			{
				type = "Rigidbody",
				data = 
				{
					useGravity = false,
				}
			},
			{
				type = "CharacterMovement",
				data = 
				{
					camera = "@MainCamera",
					bait = "@Anzuelo"
				}			
			}
		}
	},
	{
		type = "Entity",
		name = "Anzuelo",
		position = {x = -5, y = -30},
		scale = {x=0.2, y=0.2, z=0.2},
		components = {
			{
				type = "Renderer",
				data = {
					mesh = "Cube.mesh",
					material= "green"
				}
			},
			-- {
			-- 	type = "Rigidbody",
			-- 	data = 
			-- 	{
			-- 		useGravity = false,
			-- 	}
			-- },
			{
				type = "Bait",
				data={
					player = "@Player"
				}					
			}
		}
	},
	-- {
	-- 	type = "Entity",
	-- 	name = "Cubo2",
	-- 	position = { y = 2, x = 2},
	-- 	scale = { x = 0.5, y = 0.5, z = 0.5 },
	-- 	components = {
	-- 		{
	-- 			type = "Renderer",
	-- 			data = {
	-- 				mesh = "fish.mesh",
	-- 				material= "pez"
	-- 			}
	-- 		},
	-- 		{
	-- 			type = "Rigidbody",
	-- 		},
	-- 	}
	-- },
	{
		type = "Entity",
		name = "Suelo",
		position = { y = -50 },
		scale = { x = 50, y = 50, z = 50},
		components = {
			{
				type = "Renderer",
				data = {
					mesh = "Lago.mesh",
					material= "mountain"
				}
			},
			{
				type = "DestroyTest",
				data =
				{
					child = "@Player"
				}
			}
		}
	},
	{
		type = "Entity",
		name = "Agua",
		position = { y = -50 },
		scale = { x = 50, y = 50, z = 50},
		components = {
			{
				type = "Renderer",
				data = {
					mesh = "Agua.mesh",
					material= "blue"
				}
			},
		}
	},
	{
		type = "Entity",
		name = "ParedFrontal",
		position = { y = -50, z = 30 },
		scale = { x = 100, y = 50, z = 5},
		components = 
		{
			{
				type = "Rigidbody",
				data = 
				{
					isKinematic = true
				}
			}
		}
	},
	{
		type = "Entity",
		name = "ParedLateral",
		position = { y = -50, x = 30 },
		scale = { x = 5, y = 50, z = 100},
		components = 
		{
			{
				type = "Rigidbody",
				data = 
				{
					isKinematic = true
				}
			}
		}
	},
	{
		type = "Entity",
		name = "ParedTrasera",
		position = { y = -50, z = -30 },
		scale = { x = 100, y = 50, z = 5},
		components = 
		{
			{
				type = "Rigidbody",
				data = 
				{
					isKinematic = true
				}
			}
		}
	},
	{
		type = "Entity",
		name = "ParedIzquierda",
		position = { y = -50, x = -30 },
		scale = { x = 5, y = 50, z = 100},
		components = 
		{
			{
				type = "Rigidbody",
				data = 
				{
					isKinematic = true
				}
			}
		}
	},
	{
		type = "Entity",
		name = "Columna",
		position = { x = 6, y = -55, z = 19 },
		scale = { x = 3.5, y = 20, z = 3.5},
		components = 
		{
			{
				type = "Rigidbody",
				data = 
				{
					isKinematic = true
				}
			}
			-- ,
			-- {
			-- 	type = "Renderer",
			-- 	data = {
			-- 			mesh = "Cube.mesh",
			-- 			material= "yellow"
			-- 		}
			-- }
		}
	},
	{
		type = "Entity",
		name = "light",
		position = { x = 0, y = 4, z = 0},
		components = {
			{
				type = "Light",
				data = {
					lightType = "DirLight",
					color = { r = 0.8, g = 0.8, b = 0.8  },
					spec = { r = 0.8, g = 0.8, b = 0.8 },
					direction = { x = 0, y = -0.5, z = -0.75 }
				}
			}
		}
		
	},
	{
		type = "Entity",
		name = "RandomFish",
		position = { y = -55, z =1.01 },
		scale = {x = 0.5, y = 0.5, z =0.5},
		components = {
			{
				type = "Renderer",
				data = {
						mesh = "fish.mesh",
						material= "yellow"
					}
			},
			{
				type = "Rigidbody",
				data = 
				{
					useGravity = false,
				}
			},
			{
				type = "RandomMovement"
			}
		}
	}
};
return scene;
