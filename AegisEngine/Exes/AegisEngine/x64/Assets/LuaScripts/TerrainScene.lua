-- Example of scene, it's just a table with list of entities

local NAME = "TerrainScene";
local scene = {
	{
		type = "MainCamera",
		position = { z = 10, y = 3  },
		rotation = { x = -25},
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
					mesh = "boat.mesh",
					material= "playerMat"
				}
			},
			{
				type = "Rigidbody",
				data = 
				{
					useGravity = false,
					scale = 5
				}
			},
			{
				type = "CharacterMovement",
				data = 
				{
					camera = "@MainCamera",
					bait = "@Anzuelo",
					canya = "@Canya"
				}			
			}
		}
	},
	{
		type = "UI",
		data = 
			{
				type = "Button",
				nombre = "Boton",
				order = 0,
				material = "avestruz",
				x = 1,
				y = 1,
				width = 100,
				height = 50,
				dimensionx=200,
				dimensiony=50,
				callback = function()
					print("Button was clicked in LUA");
				end 
			},
	},
	{
		type = "Entity",
		name = "Anzuelo",
		position = {x = -5, y = -30},
		scale = {x=0.2, y=0.2, z=0.2},
		rotation = {x = 0, y = 45, z =0},
		--scale = {x=2, y=2, z=2},--Meitin necesita ver el anzuelo
		components = {
			{
				type = "Renderer",
				data = {
					mesh = "hook.mesh",
					material= "red"
				}
			},
			{
				type = "Rigidbody",
				data = 
				{
					useGravity = false,
					scale = 2
				}
			},
			{
				type = "Bait",
				data = {
					player = "@Player"
				}					
			}
		}
	},
	{
		type = "Entity",
		name = "Canya",
		position = {x = 0.3, y = -2, z = -2},
		scale = {x=0.1, y=0.1, z=0.1},
		rotation = {x = 0, y = 45, z =0},
		components = {
			{
				type = "Renderer",
				data = {
					mesh = "fishingRod.mesh",
					material= "pez"
				}
				
			},
			{
				type = "Rod"
			},
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
	-- 				mesh = "pez2.mesh",
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
		position = { y = -70, z = 30 },
		scale = { x = 100, y = 50, z = 5},
		components = 
		{
			{
				type = "Rigidbody",
				data = 
				{
					mass = 0;
					isKinematic = true
				}
			}
			--  ,
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
		name = "ParedLateral",
		position = { y = -70, x = 30 },
		scale = { x = 5, y = 50, z = 100},
		components = 
		{
			{
				type = "Rigidbody",
				data = 
				{
					mass = 0;
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
		name = "ParedTrasera",
		position = { y = -70, z = -25 },
		scale = { x = 100, y = 50, z = 5},
		components = 
		{
			{
				type = "Rigidbody",
				data = 
				{
					mass = 0;
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
		name = "ParedIzquierda",
		position = { y = -70, x = -25 },
		scale = { x = 5, y = 50, z = 100},
		components = 
		{
			{
				type = "Rigidbody",
				data = 
				{
					mass = 0;
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
		name = "Columna",
		position = { x = 6, y = -58, z = 19 },
		scale = { x = 3.5, y = 20, z = 3.5},
		components = 
		{
			{
				type = "Rigidbody",
				data = 
				{
					mass = 0;
					--isKinematic = true
					--isStatic = true;
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
		name = "FondoLago",
		position = { y = -63, x = 0 },
		scale = { x = 80, y = 5, z = 80},
		components = 
		{
			{
				type = "Rigidbody",
				data = 
				{
					isKinematic = true
				}
			},
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
						mesh = "pezBetta.mesh",
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
				type = "RandomMovement",
				data =
				{
					bait = "@Anzuelo"
				}
			}
		}
	},
	{
		type = "Entity",
		name = "Spawner",
		components = {	
			{
				type = "Spawner"
			}
		}
	},
};
return scene;
