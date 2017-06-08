TODO
====

A node based system for representing things in the game world
- A node can be anything, a place, a house, a player, an arm.
- Clients issue actions that does things to the nodes
- Nodes has properties and rules determening what can be done with those nodes
  and who can do these things with

  client: move self to node 2
  server: check that this action is valid
          notify and run triggers

- Check system...

action open on door
check that the door is open (lua code looking at property)
either accept (door opens) or reject (door is locked)

implicit actions
going to the room behind the door implies opening the door
and fails if the door is impassable

per player storage of properties


Generic actions
- move: use node to move target specified to a location
- create: create node
