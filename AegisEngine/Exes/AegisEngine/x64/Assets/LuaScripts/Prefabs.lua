-- Example of scene, it's just a table with list of entities

local NAME = "Prefabs";
local scene = 
{
    {
        type = "Entity",
		name = "PrefabFish0",
		scale = {x = 0.5, y = 0.5, z =0.5},
		components = {
			{
				type = "Renderer",
				data = {
						mesh = "pez1.mesh",
						material= "yellow"
					}
			},
			{
				type = "Rigidbody",
				data= {
					scale = 3
				}
			},
			{
				type = "RandomMovement"
			}
		}
    },
    {
        type = "Entity",
		name = "PrefabFish1",
		scale = {x = 0.5, y = 0.5, z =0.5},
		components = {
			{
				type = "Renderer",
				data = {
						mesh = "pez2.mesh",
						material= "yellow"
					}
			},
			{
				type = "Rigidbody",
				data= {
					scale = 3
				}
			},
			{
				type = "RandomMovement"
			}
		}
    },
    {
        type = "Entity",
		name = "PrefabFish2",
		scale = {x = 0.5, y = 0.5, z =0.5},
		components = {
			{
				type = "Renderer",
				data = {
						mesh = "pez3.mesh",
						material= "yellow"
					}
			},
			{
				type = "Rigidbody",
				data= {
					scale = 3
				}
			},
			{
				type = "RandomMovement"
			}
		}
    },
    {
        type = "Entity",
		name = "PrefabPezBetta",
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
				data= {
					scale = 3
				}
			},
			{
				type = "RandomMovement"
			}
		}
    },
    {
        type = "Entity",
		name = "PrefabPezCirujano",
		scale = {x = 0.5, y = 0.5, z =0.5},
		components = {
			{
				type = "Renderer",
				data = {
						mesh = "pezCirujano.mesh",
						material= "yellow"
					}
			},
			{
				type = "Rigidbody",
				data= {
					scale = 3
				}
			},
			{
				type = "RandomMovement"
			}
		}
    },
    {
        type = "Entity",
		name = "PrefabPezPayaso",
		scale = {x = 0.5, y = 0.5, z =0.5},
		components = {
			{
				type = "Renderer",
				data = {
						mesh = "pezPayaso.mesh",
						material= "yellow"
					}
			},
			{
				type = "Rigidbody",
				data= {
					scale = 3
				}
			},
			{
				type = "RandomMovement"
			}
		}
    },
    {
        type = "Entity",
		name = "PrefabPezArowana",
		scale = {x = 0.5, y = 0.5, z =0.5},
		components = {
			{
				type = "Renderer",
				data = {
						mesh = "pezArowana.mesh",
						material= "yellow"
					}
			},
			{
				type = "Rigidbody",
				data = {
					scale = 3
				}
			},
			{
				type = "RandomMovement"
			}
		},
	}
};
return scene;
