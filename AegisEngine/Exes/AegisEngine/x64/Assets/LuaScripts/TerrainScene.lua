--Example of scene, it's just a table with list of entities

local NAME = "TerrainScene";
local scene = {
-- camera and light
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
-- Player
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
					scale = 5,
					useGravity = false
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
		type = "Entity",
		name = "Anzuelo",
		position = {x = -5, y = -30},
		scale = {x=0.2, y=0.2, z=0.2},
		rotation = {x = 0, y = 45, z =0},
		components = {
			{
				type = "Renderer",
				data = {
					mesh = "hook.mesh",
					material= "blue"
				}
			},
			{
				type = "Rigidbody",
				data = 
				{
					useGravity = false,
					scale = 20
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

-- spawner
	{
		type = "Entity",
		name = "Spawner",
		components = {	
			{
				type = "Spawner",
				data = 
				{
					bait = "@Anzuelo",
					score = "@ScoreManager.UIScoreManager"
				}
			}
		}
	},
-- terrain
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
					}
				}
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
			}
		},
-- UI
	{
		type = "UI",
		data = 
			{
				type = "Button",--Button/Image
				nombre = "HomeButton",
				material = "home_button_material",
				order = 0,
				x = 1,
				y = 0,
				width = 0.1,
				height = 0.1,
				visible = false
			},
	},
	{
		type = "UI",
		data = 
			{
				type = "Text",
				nombre = "scoreText",
				order = 0,
				x = 0.025,
				y = 0.025,
				charheight = 0.1,
				visible = true,
				text = "10",
			},
	},
	{
		type = "Entity",
		name = "ScoreManager",
		components = {
			{
				type = "UIScoreManager",
				data = {
					text = "@scoreText"
				}
			},
		}
	},
};
return scene;
