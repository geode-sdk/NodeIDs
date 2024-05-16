# NodeIDs

Standard node IDs for layers in Geode.

Whenever you hook a layer in Geode and want to add stuff to it, in order to preserve compatability with other mods, you should always use node IDs rather than `objectAtIndex` calls. You need to depend on this mod to add the IDs.

For more information, [read the docs page on IDs & Layouts](https://docs.geode-sdk.org/tutorials/nodetree).

## Using as a dependency

Add the mod to your `mod.json`:

```json
{
    "dependencies": [
        {
            "id": "geode.node-ids",
            "version": "v1.10.0",
            "importance": "required"
        }
    ]
}
```

**All the hooks in this mod have very low priority and as such should always be automatically run before your hooks.** However, if you want to ensure that IDs have been provided for your modified layer, call `NodeIDs::provideFor` (Geode function, not from this mod):

```cpp
#include <Geode/modify/EditorUI.hpp>

using namespace geode::prelude;

class $modify(EditorUI) {
    bool init(LevelEditorLayer* lel) {
        if (!EditorUI::init(lel))
            return false;
        
        NodeIDs::provideFor(this);

        return true;
    }
};
```
