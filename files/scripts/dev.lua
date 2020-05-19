godMode = [[
	game.game:GetActivePlayer():SetDemigod(true)
	game.game:GetActivePlayer():EnableInjury(false)
	game.game:GetActivePlayer().invulnerability = true
]]


allWeapons = [[
	game.game:GetActivePlayer():InventoryAddWeapon(2,42)
	game.game:GetActivePlayer():InventoryAddWeapon(3,60)
	game.game:GetActivePlayer():InventoryAddWeapon(4,56)
	game.game:GetActivePlayer():InventoryAddWeapon(5,96)
	game.game:GetActivePlayer():InventoryAddWeapon(6,42)
	game.game:GetActivePlayer():InventoryAddWeapon(8,56)
	game.game:GetActivePlayer():InventoryAddWeapon(9,120)
	game.game:GetActivePlayer():InventoryAddWeapon(10,128)
	game.game:GetActivePlayer():InventoryAddWeapon(11,150)
	game.game:GetActivePlayer():InventoryAddWeapon(12,120)
	game.game:GetActivePlayer():InventoryAddWeapon(13,120)
	game.game:GetActivePlayer():InventoryAddWeapon(15,40)
	game.game:GetActivePlayer():InventoryAddWeapon(17,35)
	game.game:GetActivePlayer():InventoryAddWeapon(20,6)
	game.game:GetActivePlayer():InventoryAddWeapon(21,6)
]]

addMoney = [[
	game.game:GetActivePlayer():InventoryAddMoney(100*1000000)
]]

-- More scripting funcs can be found here: https://www.nexusmods.com/mafia2/mods/130

unbindKey("p")
unbindKey("o")

bindKey("p", printPlayerPosition)
bindKey("o", enableSnow)