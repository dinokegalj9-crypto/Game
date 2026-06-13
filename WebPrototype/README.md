# The Hollow Crown — Playable Web Slice

A short, atmospheric **2D action prototype** of *The Hollow Crown*, playable in any modern
browser. You are **the Crownless**: walk west through the fog-drowned Weeping Moors, cut
down the corrupted dead, and face the first boss — **the Bell Keeper**. Corruption rises as
you fight.

This is a companion to the Unreal Engine 5.6 project in the repository root — a way to
*feel* the mood and core loop (explore → fight → boss → the world changes) today, while the
full game is built in Unreal.

## How to play it right now

It's a static page — no build step.

```bash
cd WebPrototype/public
python3 -m http.server 8000
# then open http://localhost:8000 in your browser
```

(Opening `index.html` directly via `file://` won't work because it uses ES modules — use the
local server above, or any static host.)

**Controls**

| Action | Keyboard | Gamepad |
|--------|----------|---------|
| Move | `A` / `D` or `← →` | left stick / d-pad |
| Light strike | `J` or Left-Mouse | ✕ |
| Heavy strike (breaks guard) | `K` or Right-Mouse | ◻ |
| Roll (brief i-frames) | `Space` / `Shift` | ◯ |
| Mute / pause | `M` / `P` | start |

On phones, touch zones appear: left side to move, right-side buttons to strike and roll.

**Tips:** heavy strikes break an enemy's poise and open them up; *roll through* the Bell
Keeper's golden shockwaves — blocking won't save you.

## A note on the art assets

The character, enemy, boss, backgrounds, ground, UI emblem, and ambient music were all
generated for this slice and share one "stylized dark realism" art direction (see
[`design/assets.csv`](design/assets.csv)). They are served from a permanent CDN and loaded
at runtime; the magenta-keyed sprites are made transparent in-browser. If a sprite ever
can't be keyed, the game falls back to hand-drawn hooded silhouettes so it always renders.

## Files

```
public/index.html   the whole game (canvas, fixed-timestep loop, combat, boss, HUD)
public/strings.js   all player-visible text (one place to localize)
public/logic.js     solo stub required by the hosting platform
design/assets.csv   the asset manifest + shared style formula
```
