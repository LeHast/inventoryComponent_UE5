# inventoryComponent_UE5

The code represents an inventory component for a game. It is designed to manage the player's inventory, including resources and weapons.
The inventory component allows picking up items, adding them to the inventory, and removing weapons.
It also provides functionality for selecting the current weapon and handling input mapping.

# Inventory Component

The Inventory Component is a C++ implementation for managing the inventory of a game character. It allows players to pick up items, add them to the inventory, remove weapons, and select the current weapon.

## Features

- Resources Inventory: Stores resources using a map where each resource is associated with a quantity.
- Weapons Inventory: Stores weapons using a map where each weapon is associated with an index.
- Max Inventory Spaces: Defines the maximum number of weapons and resources that can be stored in the inventory.
- Item Queue: A queue that holds items picked up by the player.
- Current Weapon: Tracks the currently equipped weapon.
- Input Mapping: Defines input actions for picking up items and selecting weapons.

## Usage

To use the Inventory Component in your game:

1. Add the `UInventoryComponent` class to your game project.
2. Include the necessary header files in your project.
3. Create an instance of the `UInventoryComponent` in your character or actor class.
4. Call the appropriate functions to add items to the inventory, remove weapons, and select the current weapon.
5. Implement the `IInventoryInterface` to interact with the inventory.
