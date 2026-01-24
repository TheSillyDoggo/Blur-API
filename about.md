# Blur API

This mod adds an API for mod developers to add a blur behind any node they want.

This mod does **nothing** on its own.

## For Developers

To use blur in your mod, simply copy the `src/BlurAPI.hpp` file into your mods code.

Then, to apply a blur to a node, simply run:
```
BlurAPI::addBlur(node);
```

And then, if you want to remove blur from a node at any point:

```
BlurAPI::removeBlur(node);
```

To set a custom blur pass count (you probably don't need to do this):

```
BlurAPI::getOptions(node)->forcePasses = true;
BlurAPI::getOptions(node)->passes = 5;
```

You do not need to add blur api as a dependency if you include the header, the mod will work just fine if the user doesn't have Blur API installed