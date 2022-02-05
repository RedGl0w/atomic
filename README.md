### atomic
An improved version of [nw-atom](https://github.com/M4xi1m3/nw-atom), but escher compliant.

This is a Mendeleiev table for Epsilon ([numworks'](https://numworks.com) firmware). This app isn't an official one (but it still works well :p )

#### Install

You can either install ~~[Omega](https://getomega.dev)~~ (deprecated) or [Upsilon](https://lolocomotive.github.io/Upsilon-website/), which comes with the app pre-installed, or manually install it :
At the root folder of the firmware you want the app to be into, you can do :
```
git clone https://github.com/RedGl0w/atomic.git apps/atomic
```
You'll have then to update the `apps/home/apps_layout.csv` to add atomic at the position you want in the menu (for version above 15), and then you can edit the `buid/config.mak` to add the application to the `EPSILON_APPS` list (exemple : `EPSILON_APPS ?= calculation rpn graph code statistics probability solver atomic sequence regression settings`), and follow the steps to compile the firmware itself.
