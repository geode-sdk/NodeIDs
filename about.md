# Node IDs

Adds node IDs to layers for other mods to base their UI on, for preserving mod compatibility. See the [Github repository](https://github.com/geode-sdk/NodeIDs) for contributing.

## Why is this needed?
Back in the ancient times we had to get objects by their indices - whenever you wanted to get the play button in the main menu, you had to know it was the 3rd button added there.

At first this approach seemed to work well, but then several issues were found - what if a mod adds its own button before all others? What if it removes a button RobTop added? Now the 3rd button might be something completely different!

Geode provides a solution - Node IDs. Now you don't need to bother with numbers at all! Instead you grab "play-button" and you're always guaranteed to get the correct button, even if some other mod completely reorganizes the main menu.