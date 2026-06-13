# The Hollow Crown — Art Bible (Visual Identity Master)

> **Status:** Authoritative visual single-source-of-truth. **Engine:** Unreal Engine 5.6.
> **Audience:** Every artist, concept artist, environment/character/VFX/UI artist, animator,
> and **AI generation tool** working on the game.
> **Scope:** *Visual identity only* — no gameplay systems, no programming, no technical
> implementation. The creative *why* lives in [`DesignBible.md`](DesignBible.md); this is
> the *how it looks*.

**The eight feelings.** Every visual decision — a brushstroke, a fog density, a rivet on a
breastplate — must reinforce at least one, ideally several, of these and **never** work
against them:

> **Mystery · Decay · Beauty · Melancholy · Ancient History · Tragedy · Fear · Wonder**

If an asset doesn't make the world feel more *haunted and more believable*, it is wrong,
no matter how technically clean.

**Contents** (the thirteen deliverables):
[Philosophy](#1-core-visual-philosophy) ·
[References](#2-visual-references) ·
[Color](#3-color-language-guide) ·
[Lighting](#4-lighting-guide) ·
[Architecture](#5-architectural-guide) ·
[Environment](#6-environment-guide) ·
[World Storytelling](#7-world-storytelling) ·
[Characters](#8-character-design-guide) ·
[Enemies](#9-enemy-design-guide) ·
[Bosses](#10-boss-design-guide) ·
[Weapons](#11-weapon-design-language) ·
[Armor](#12-armor-design-language) ·
[Materials](#13-material-library) ·
[VFX](#14-vfx-style-guide) ·
[UI](#15-ui-visual-identity) ·
[Typography](#16-typography) ·
[Region Identity + Mood Boards](#17-region-identity--mood-board-package) ·
[Consistency Rules](#18-visual-consistency-rules) ·
[Production Standards](#19-aaa-production-standards)

---

## 1. Core Visual Philosophy

**The style is "Stylized Dark Realism."** Believable proportions, materials, and physics —
but pushed, composed, and lit for mood rather than documentary accuracy. Beautiful *and*
achievable. Not photoreal, not stylized-cartoon; the seam between the two, closer to a
painting that moves.

**The world must feel:** Ancient · Forgotten · Sacred · Dying · Beautiful · Dangerous ·
Timeless.

**The three unbreakable laws:**

1. **Nothing recently built.** Every structure predates the player by lifetimes. There are
   no fresh timbers, no crisp mortar, no new paint. The newest thing in the world is a
   grave.
2. **Nothing modern.** No clean geometry, no machined edges, no symmetry that feels
   manufactured, no contemporary silhouettes. Hand-made, settled, irregular.
3. **Nothing clean.** Every surface carries time: moss, water-staining, soot, rust, wear
   paths, repair over repair. Cleanliness is reserved as a deliberate horror signal (the
   unnaturally spotless Silent Cathedral).

**History has layers.** Every important place shows **at least two eras**: a current,
failing occupation built on top of something far older and grander that no one alive
remembers. The player should constantly read: *a civilization existed here before this
one, and before that, another.* Ruins inside ruins. Foundations of stone the current
kingdom could never cut. This stratification is the single most important environmental
idea in the game.

**Restraint is the aesthetic.** Quiet, composed, sparse. Empty space and silence do the
work. We earn rare moments of awe (a colossus through the fog, a cathedral at dawn) by
surrounding them with stillness. Visual noise is the enemy of dread.

---

## 2. Visual References

Use references for *mood and discipline*, never to copy.

**Primary (the core target):**
- **Bloodborne** — gothic dread, oppressive verticality, restrained palette, the sense the architecture hates you.
- **Elden Ring** — scale, the colossal-through-fog reveal, layered lost history.
- **Lies of P** — believable period craftsmanship, material fidelity, elegant decay.
- **A Plague Tale: Requiem** — grounded medieval misery and beauty, light through grime, painterly naturalism.
- **Kingdom Come: Deliverance** — historical plausibility of clothing, tools, villages, arms and armour.
- **Dark Souls 3** — ash, fading fire, melancholy of an ending world.
- **The Witcher 3** — believable lived-in settlements and folklore weight.

**Secondary (tone & costume):**
- **Berserk** — tragic monstrousness, the beauty of the grotesque, weight of dread.
- **The Name of the Rose** — austere ecclesiastical interiors, candlelight, the menace of the sacred.
- **Brotherhood of the Wolf** — folk-horror beasts, rain-soaked period menace.
- **Sleepy Hollow** — desaturated gothic palette, fog, dead trees, dread of the woods.
- **The Green Knight** — mythic stillness, moss and stone, ancient and uncanny.

**Forbidden — do not borrow from, ever:** high/bright fantasy, anime or cartoon styling,
oversaturated color, sci-fi or steampunk elements, "cool" power-fantasy posing. If a piece
reads as any of these, reject it regardless of quality.

---

## 3. Color Language Guide

Color is **emotion and information**, never decoration. The world is desaturated by
default; saturation is a precious resource spent only with intent.

**Global rule — the 70/25/5 split:** ~70 % near-neutral darks (charcoal/grey/stone),
~25 % muted environmental hues (green/navy/bronze), ~5 % (or less) any true accent
(muted gold, dried blood). A frame that breaks this reads as "too bright" and is wrong.

### Primary palette

| Color | Approx. | Emotional meaning / use |
|-------|---------|--------------------------|
| **Deep Charcoal Black** | `#0E0F11` | The ground of everything — dread, the unknown, the void beneath history. Shadows, deep fog, the Crown's influence. |
| **Cold Grey** | `#3A3F44` | Indifference of a dying world; stone, sky, ash. The neutral the eye rests on. |
| **Weathered Stone** | `#6B6557` | Age and permanence; ancient masonry, monuments. The color of *time itself*. |
| **Dark Forest Green** | `#27332A` | Living decay, the forest's patience, things that grow over the dead. Nature reclaiming. |
| **Desaturated Navy Blue** | `#2A3340` | Cold, water, night, the failing sky; melancholy and distance. |
| **Burnt Bronze** | `#5E4A2E` | Old craft, fallen nobility, tarnished glory; armour, bells, fittings. |
| **Muted Gold** | `#9A7B3F` | **The single sacred/ominous accent.** Faith, royalty, and the Crown's corruption — beauty that is also a warning. Used sparingly; its rarity is its power. |

### Secondary palette (accents, used sparingly)

| Color | Approx. | Meaning |
|-------|---------|---------|
| **Ash White** | `#C9C6BD` | Death, mourning, the suffocating ash of Ashbourne; what's left when fire is done. |
| **Dried Blood Red** | `#5A2320` | Violence already done — never fresh. History of suffering: stained altars, old banners, execution wood. |
| **Moss Green** | `#4A5740` | Damp life on dead things; the only "fresh" green permitted, always on decay. |
| **Faded Ivory** | `#B8AE94` | Bone, parchment, candle wax, relics; the fragile sacred. |

### Forbidden colors

Bright neon · pure white (`#FFFFFF`) · bright/pure red · bright/pure blue · bright/pure
green · anything highly saturated. **Exception, deliberate and rare:** a single saturated
note may appear *as a shock* tied to the supernatural (a Blood-Moon sky, a corruption
glow) — and only because everything around it is starved of color. Saturation = the
unnatural.

**Corruption's color logic:** as corruption rises, muted gold creeps in at the edges
(veins, light), then sickens toward a wrong bruised gold-violet at the highest stages.
Corruption is the only force allowed to introduce an uncanny hue, precisely because it is
*wrong*.

---

## 4. Lighting Guide

**Philosophy:** the sun is sick and the sky is fading. The world is **rarely fully
illuminated.** Light is weak, low-angle, scattered through fog, and almost always *cooler*
than the warm pockets of human fire it contrasts against. Light is hope; there is little
of it, and it is fragile.

**Universal rules:**
- **Fog is the master tool** — volumetric depth, separation of silhouettes, mystery. Almost every exterior has it; density is the dial.
- **Contrast warmth against cold.** The world is cold blue-grey; survival is warm (torch, hearth, candle). The eye is led to safety by warmth and to dread by cold.
- **Light as composition** — a single shaft, a doorway glow, a far window. One light source tells the story; avoid even, flat illumination.
- **Deep, soft shadows** — never crushed to pure black in gameplay-critical areas, but darkness is real and threatening.
- **Readability floor:** the player silhouette and immediate threats must always be legible (cold rim-light on the player; threats catch the key light). Mood never costs clarity in combat.

| Context | Lighting rule |
|---------|---------------|
| **Day (twilight)** | Weak, low, overcast sun; long soft shadows; cool desaturated key, slightly warmer at the horizon. Never bright noon. |
| **Night** | Moonlight as a cold blue key through cloud/fog; warm firelight pools; most of the screen reads in silhouette. |
| **Rain** | Flat diffuse light, lowered contrast, wet speculars catching what little light exists; muffled, grey. |
| **Storms** | Near-dark base punctuated by cold lightning — brief, high-contrast silhouette reveals; dread of the strobe. |
| **Boss arenas** | Bespoke, theatrical, motivated by the boss's identity (the Bell Keeper's swinging firelight; a drowned green-blue gloom). One dominant source; strong key/rim on the boss silhouette. |
| **Cathedrals** | Tall shafts of pale light through high windows; dust motes; candle warmth below cold stone above; sacred and oppressive. |
| **Villages** | Small warm hearth/lantern pools against cold dusk; islands of fragile safety in a dark landscape. |
| **Crypts** | Near-total dark; the player's torch is the only meaningful light; claustrophobic falloff; things at the edge of the light. |
| **Forests** | Dappled weak grey light, heavy canopy occlusion, mist between trunks; light fails fast with depth — the woods swallow it. |

---

## 5. Architectural Guide

Architecture is the game's loudest storyteller. Every structure answers: *who built it,
how long ago, and what failed here.*

**Universal architectural rules**
- **Two-era minimum (layering):** current crude occupation built atop older, finer, larger work. Mismatched stone courses, blocked-up grand arches, huts inside a fallen hall.
- **Hand-made irregularity:** no perfect symmetry or repetition; settling, leaning, sagging ridgelines, off-plumb walls.
- **Honest mass:** thick walls, small windows, heavy timber — defensive, pre-modern, built against a hostile world.
- **Decay as default state:** moss, water-staining, rot, rust, collapse, repair-over-repair. Ageing and weathering are not a pass at the end — they are the design.

| Type | Materials | Shape & scale | Decoration | Ageing / damage |
|------|-----------|---------------|------------|------------------|
| **Kingdom (grand/old)** | Cut ashlar stone, lead, bronze | Monumental, vertical, intimidating; scale beyond current means | Heraldry worn illegible, faded gilding, broken crown motifs | Cracked, scaffolded with later crude repairs, partially collapsed |
| **Village** | Timber frame, wattle-and-daub, thatch, fieldstone footings | Low, huddled, organic clustering around a well/church | Carved lintels, hung charms, drying racks | Sagging thatch, leaning posts, mud, smoke-blackening |
| **Church** | Stone, slate, lead glass, oak | Tall nave, bell tower, pointed arches; aspirational verticality | Saint carvings (weathered faceless), candle niches, iron | Bird-fouled, cracked glass, ivy, a leaning or fallen bell tower |
| **Castle** | Heavy ashlar, iron, timber hoarding | Massive, brutal, functional; few openings, thick curtain walls | Murder holes, machicolations, faded banners | Slighted walls, fire-scorched, breached, rubble-choked baileys |
| **Ruins (ancient)** | Stone too large/fine to be current work | Cyclopean, geometry slightly *wrong*, pre-kingdom | Eroded glyphs, motifs no living culture uses | Half-buried, root-split, swallowed by land — the deepest layer |
| **Crypts** | Stone, bone, iron grilles | Low, tight, oppressive vaults | Effigies, ossuary patterns, name-worn plaques | Damp, collapsed niches, root intrusion, standing water |
| **Watchtowers** | Fieldstone, timber | Slender, isolated, sightline-placed | Beacon basket, faded warning marks | Burned beacons, broken stairs, abandoned mid-watch |
| **Bridges** | Stone arch, timber | Functional, often the only crossing; ancient piers reused | Wayshrines at the ends, toll posts | Missing spans, flood-scoured, patched with planks |
| **Roads** | Packed earth, worn ancient paving beneath | Meandering, following old routes | Milestones, wayshrines, hanged-man gibbets | Sunken paving, washed-out, reclaimed by moor/forest |
| **Monuments** | Stone, bronze | Colossal, humbling, often toppled | Kings/saints whose faces time erased | Fallen, defaced, used as landmarks by the living |

---

## 6. Environment Guide

Each biome has a non-negotiable identity. Distinct silhouette, palette skew, fog behavior,
and "signature read" so a single screenshot names the place.

| Environment | Signature read | Palette skew | Key elements |
|-------------|----------------|--------------|--------------|
| **Forests** | Light dies with depth; canopy as a ceiling | Dark forest green + charcoal | Towering trunks, mist between, fallen giants, fungus on the dead |
| **Swamps** | Still black water, gas, the smell of rot made visual | Green-black + sick bronze | Sunken structures, reeds, drowned trees, bubbling pools |
| **Wetlands / Moors** | Horizonless fog, flooded ground, isolation | Cold grey + navy | Peat, standing water, causeways, dead trees, distant spire |
| **Mountains** | Cruel scale, thin sick light, wind | Cold grey + ash white | Bare rock, scree, exposed shrines, frozen wind-scour |
| **Ruins** | Wrong-scale ancient stone, history in strata | Weathered stone + black | Cyclopean blocks, buried halls, eroded glyphs |
| **Graveyards** | Density of the dead, leaning order decaying to chaos | Stone + moss green | Tilted markers, mass graves, lych-gates, settling earth |
| **Cathedrals** | Vertical awe under a dead faith | Stone + faded ivory + muted gold | Naves, shattered glass, candle seas, fallen bells |
| **Villages** | Fragile warm life clustered in the cold | Timber brown + hearth warmth | Huddled houses, well, church, drying racks, mud |
| **Road networks** | The thread between dread, never safe | Earth + grey | Wayshrines, milestones, gibbets, abandoned carts |
| **Caves** | The light fails entirely; pressure | Black + faint mineral | Wet rock, narrow throats, old mine works, bones |
| **Dungeons** | Made by hands, for cruelty | Stone + iron + dried blood | Cells, chains, oubliettes, water, scratched tallies |
| **Rivers** | Movement in a still world; boundary | Navy + grey | Fords, broken bridges, mills, flotsam, drowned offerings |
| **Coastal** | Vast cold indifference; the drowned | Navy + slate + bronze | Cliffs, wrecks, tide-line bones, half-sunk structures |

---

## 7. World Storytelling

**Doctrine: nothing is randomly placed.** Every prop cluster is a sentence; every location
is a paragraph the player reads without words. The player should constantly ask *"what
happened here?"* and be able to answer it by looking. Composition implies cause.

Rules for the standard storytelling set-pieces:

| Set-piece | Read it must produce | Construction notes |
|-----------|----------------------|--------------------|
| **Abandoned camps** | "They left in a hurry — or never left." | Cold fire, a single boot, food gone to rot, drag marks leading away |
| **Battlefields** | "Two sides, long ago, and no victor that mattered." | Rusted arms half-buried, two heraldries, scavenger paths, a lone marker |
| **Execution sites** | "Authority was cruel and afraid." | Gibbets, scaffold, dried-blood wood, crows, a list of names |
| **Destroyed villages** | "Something came through, and the land took the rest." | Burned frames, household goods abandoned, a defended last house |
| **Mass graves** | "Too many to bury with rite." | Settled disturbed earth, a hasty cross, lime, scattered effects |
| **Ancient temples** | "Older than the kingdom, worshipping something else." | Wrong-scale stone, unfamiliar motifs, an offering still tended by *someone* |
| **Fallen statues** | "A name and a power, both forgotten." | Toppled colossus, defaced face, the living camped in its shadow |
| **Lost caravans** | "The road is not safe and never was." | Overturned cart, scattered trade goods (taken or not?), draught animal bones |
| **Forgotten shrines** | "Someone still believes, or did until recently." | Wayside niche, fresh-ish offering vs. ancient ones, a worn path to it |

**Composition principles:** stage with a focal object and supporting evidence; leave a
*gap* the player's mind fills (the most powerful detail is the one implied); place from the
player's likely sightline; let nature's reclamation date the event. Reward the curious with
a deeper read (a letter, a second body, a hidden cause) but never require it.

---

## 8. Character Design Guide

Characters are read as **silhouette first, material second, color last.** A villager and a
cultist must be distinguishable as black shapes at 40 m.

**Universal character rules**
- **Silhouette:** each archetype owns a distinct profile (headwear, stance, load, hem line). Tier by class via silhouette complexity — peasants simple, nobles/clergy ornate.
- **Clothing:** historically plausible layered medieval dress; function before fashion; everything mended, dirtied, weathered. Status = quality and intactness of the same forms, not different forms.
- **Color:** all within the world palette; commoners in undyed wool/leather/earth; status adds *muted* dyes (navy, ox-blood, bronze trim); muted gold only for the highest clergy/nobility and always tarnished.
- **Material:** wool, linen, leather, fur, iron — used, never new. Cloth hangs with real weight.
- **Status / class / occupation indicators** (read at a glance): cut and cleanliness of cloth, presence of metal/dye, tools-as-costume (a hunter's bow and pelts, a smith's apron and burns, a priest's stole and keys), and **bearing** (the beaten stoop of the poor vs. the upright cruelty of authority).

| Archetype | Silhouette | Palette | Material / tells |
|-----------|-----------|---------|------------------|
| **Villagers** | Simple, stooped, layered rags | Earth, undyed wool | Patched linen, clogs, mud; tools of labor |
| **Merchants** | Bundled, laden, a little richer | Earth + a muted dye | Better wool, a purse, a ledger, travel wear |
| **Hunters** | Lean, hooded, asymmetric load | Forest green, brown, fur | Leather, pelts, bow/traps, blood-stained |
| **Guards** | Bulked by mail/gambeson, upright | Grey, ox-blood livery | Iron, faded heraldry, spear; worn but kept |
| **Priests** | Tall, robed, vertical | Faded ivory, black, muted gold trim | Stole, keys, censer; clean as a warning |
| **Nobles** | Ornate, upright, impractical | Navy, ox-blood, tarnished gold | Fine but faded velvet, fur, signet; decadent decay |
| **Cultists** | Hooded, uniform, wrong | Ash, black, a single gold mark | Ritual scars/masks, mismatched stolen finery |
| **Outcasts** | Broken, wrapped, hidden | Grey, ash, dried blood | Bandage, brand, hidden mutation; shame made visible |
| **Travelers** | Cloaked, road-worn, self-reliant | Muted, dust over any base | Pack, staff, layered for weather; mystery preserved |

### 8b. Player Design — The Crownless

The Crownless must feel **human, fragile, capable, lonely, determined** — and **never**
heroic, flashy, or chosen. No glowing armor, no hero cape, no idealized physique. A person
who has survived, not a champion who was sent.

- **Base read:** a hooded, layered wanderer in muted ash-grey; a strong, simple, slightly
  hunched silhouette; a faint **cold rim-light** that separates them from the fog (the only
  concession to "main character" — it is cold, not golden; survival, not glory).
- **Believable kit:** practical layered cloth and leather, a single honest weapon, visible
  wear and repair. Equipment changes are real and grounded (see §11–12).
- **Visual progression** (mirrors the corruption stages — beauty curdling into monstrosity):

| Stage | Read |
|-------|------|
| 1 — **Unknown Wanderer** | Anonymous, hooded, road-worn; could be anyone; entirely human. |
| 2 — **Survivor** | Hardened, scarred, better-kept kit earned from the world; resolve in the stance. |
| 3 — **Leader** | Marked by others' trust — a token, a better cloak, a bearing; still human, now seen. |
| 4 — **Corrupted Legend** | Muted-gold veins, darkened eyes, an unnatural stillness; awe and unease; beauty going wrong. |
| 5 — **Possible Monster** | Silhouette itself altered, barely human, the Crown's gold sickened to a bruise; tragic, not cool. |

Progression is **earned and ambivalent** — every gain in power is a visible loss of
humanity. The player should feel the trade in the mirror.

---

## 9. Enemy Design Guide

**Three laws of enemy design:**
1. **Readability** — instantly distinguishable from allies and from each other.
2. **Strong silhouette** — recognizable as a black shape; threat encoded in profile (mass, reach, posture).
3. **Visual storytelling** — every enemy *was* something; its design tells you what, and what was done to it.

**No generic monsters.** Every creature is **biologically and historically plausible
within the world**: wildlife is real fauna pushed; the corrupted are recognizably the
people/animals they were, deformed by a comprehensible logic; nothing is a random
fantasy beast. Telegraphs (wind-ups, tells) are part of the silhouette language and must
read before they hit.

| Category | Identity | Visual logic |
|----------|----------|--------------|
| **Wildlife** | Desperate, starving, territorial real fauna | Mangy wolves, boar, carrion birds; pushed gaunt and aggressive, not monstrous |
| **Corrupted Humans** | The kingdom's people, undone | Still wear their old roles (a corrupted guard, miller, child) twisted by sickness — tragic recognition |
| **Cultists** | Devotees of the Crown/old powers | Uniform ritual dress, masks, self-mutilation, a single gold mark; human and worse for it |
| **Undead** | The dead that won't rest | Period dress and arms decayed onto bone; not zombies-as-spectacle but *unquiet graves* |
| **Ancient Creatures** | Older than the kingdom | Forms that echo the cyclopean ruins; uncanny anatomy that still obeys an internal logic |
| **Crown-Touched Beasts** | Animals warped by a fragment | A real animal as armature, mutated toward the boss-tier — muted-gold growths, wrong symmetry |

Threat tiering by silhouette mass and the amount of "wrongness": fodder reads almost human;
elites carry visible corruption or finer arms; mini-bosses approach the language of the
majors. The closer to the Crown, the more the gold and the wrongness show.

---

## 10. Boss Design Guide

> The six-axis framework below is *realized* for the full roster — the Twelve Lords — in the
> [**Boss Bible**](BossBible.md), including each Lord's silhouette, color, and arena identity.

The player must **remember every boss** and never confuse two. Enforce variety with a
**six-axis identity framework** — each major boss must be deliberately differentiated on
all six, and no two bosses may share the same dominant choice on more than two axes.

| Axis | Question | Why it prevents sameness |
|------|----------|---------------------------|
| **Visual Identity** | One unforgettable silhouette/motif (the bell, the stag's antlers, the choir's thorns) | The thing you'd draw from memory |
| **Color Identity** | A single owned accent within the palette (gold bell-glow, drowned green, ash white) | Each boss "tints" its fight |
| **Movement Identity** | A signature rhythm/locomotion (ponderous toll-and-slam vs. darting hunt) | Felt in the hands, not just seen |
| **Arena Identity** | A space that is the boss's character (flooded nave, shifting wood, ash square) | The place is the boss |
| **Narrative Identity** | The tragedy of who they *were* (Design Bible's fallen legends) | Emotion, not just challenge |
| **Emotional Identity** | The single dominant feeling (dread, pity, awe, sorrow) | Each fight owns one of the eight feelings |

**Shared boss-tier visual language** (so they feel like one game): all are *fallen
legends* — recognizably once-human or once-noble, now grand and ruined; corruption shows as
muted-gold growth/light; scale and stillness used for awe; the kill should feel **tragic,
not triumphant**. Telegraphs are large, readable, and in-character. Arenas reveal the boss
through fog/dark in a single staged moment.

(Specific bosses are content and live in the Design Bible / per-boss folders; this is the
framework that guarantees their distinctiveness.)

---

## 11. Weapon Design Language

Weapons must feel **used, heavy, forged, historical, and practical.** They are tools that
have killed and been repaired, not trophies.

**Universal rules:** real medieval proportions and weight; **no oversized anime weapons**,
no fantasy excess, no glowing edges (except deliberate legendary/corrupted cases); visible
forging, sharpening, notches, rust-bloom, re-wrapped grips, field repairs; ownership tells
(a peasant's reforged tool vs. a knight's heirloom).

| Class | Read | Notes |
|-------|------|-------|
| **Swords** | Personal, valued, status-bearing | Arming/longswords; worn edges, wrapped grips, a family mark |
| **Axes** | Brutal, practical, of the people | Bearded/wood axes pressed to war; haft splits, repaired |
| **Spears** | Common, poor-man's reach, militia | Simple heads, ash hafts, the weapon of the desperate many |
| **Greatswords** | Two-handed weight and commitment | Heavy but real (not cartoon slabs); a soldier's, not a giant's |
| **Hammers / maces** | Crushing, often clerical/judicial | Iron heads, oak hafts; the weapon of zealots and executioners |
| **Shields** | Battered protection, identity | Splintered, repainted-over heraldry, arrow-scarred |
| **Torches** | Light, fear, fragile defense | Pitch and rag; warmth as a weapon; the most human "weapon" |
| **Legendary** | Restrained myth | History made physical (a relic blade, a saint's hammer); power shown through *craft and age and a single muted-gold note*, never through size or neon |

Corrupted weapons: the muted gold appears as growth fused into the metal — beautiful,
wrong, and clearly diseased.

---

## 12. Armor Design Language

Armor tells a story before a word is spoken: **who they are, what they've survived, and
what it cost.** Wear and status are mandatory.

| Tier | Read | Materials / tells |
|------|------|--------------------|
| **Peasant clothing** | Vulnerable, layered against weather and want | Wool, linen, leather scraps; patched, mismatched, mud |
| **Hunter gear** | Mobile, practical, of the wild | Boiled leather, fur, hoods; trophies, blood, asymmetry |
| **Guard equipment** | Issued, kept, expendable | Gambeson + mail, kettle helm, faded livery; dents and rust |
| **Knight armor** | Status and the weight of duty | Plate over mail, heraldry worn faint; heirloom repairs, honest scars |
| **Church equipment** | Sacred authority, unsettling cleanliness | Robes + ceremonial plate, stoles, muted-gold trim; ornate, oppressive |
| **Cultist clothing** | Belonging to something wrong | Ritual robes, masks, stolen finery mismatched; a single gold mark, scarification |
| **Legendary armor** | Restrained myth made wearable | A famed suit, history in every dent; one muted-gold relic detail, never gaudy |
| **Corrupted armor** | The Crown wearing a person | Plate fused with muted-gold growth, organic intrusion, beauty curdled into disease |

**Rules:** silhouettes stay believable (no spikes-for-spikes' sake); status is the *quality
and completeness* of the same medieval forms; everything weathered; corruption is the only
source of the "unnatural," always as muted-gold organic growth.

---

## 13. Material Library

Materials are where "Stylized Dark Realism" is won or lost. Every material is **aged by
default** — pristine is a special state, not the baseline. Master materials drive
consistent weathering (moss, water-staining, dust, edge-wear) via shared parameters.

| Material | Visual standard |
|----------|------------------|
| **Stone** | Matte, porous, water-stained; moss/lichen in crevices; chipped edges, soot at hearths; ancient stone finer and wrong-scaled vs. current crude work |
| **Wood** | Grey-weathered, split, wormed; black at joints and ground-contact; thatch sagged and mossed |
| **Iron** | Dark, rust-bloomed, pitted; never chrome; bleeding rust stains onto stone/cloth |
| **Steel** | Slightly finer than iron, still matte and scratched; honed edges catch the cold key light; status, not shine |
| **Bronze** | Tarnished brown-green patina; the metal of bells, fittings, old glory; muted, never bright |
| **Leather** | Cracked, darkened with use and oil, scuffed; stiff where dried, worn supple where handled |
| **Cloth** | Real weight and drape; faded dyes, dirt gradient from the hem up, mends and stains |
| **Bone** | Faded ivory to grey-brown; porous, cracked, earth-stained; ossuary and relic use |
| **Corrupted Flesh** | The one "organic horror" material — translucent, veined with muted gold, wrong sheen; beautiful and diseased; used only for corruption and Crown-touched subjects |
| **Ancient Crown Material** | The artifact's substance — not metal, not stone; impossibly smooth, faintly luminous muted gold under a dark patina, subtly *wrong* to the eye; the visual source from which all corruption-gold derives |

---

## 14. VFX Style Guide

**Grounded over flashy.** Effects obey real physics (gravity, drift, dissipation) and serve
readability, never spectacle for its own sake. **Avoid visual noise** — fewer, heavier,
more meaningful effects. The default register is *atmosphere* (fog, embers, dust), not
*fireworks*.

| Effect | Rule |
|--------|------|
| **Combat** | Weighty, brief, physical: sparks on steel, a gout of dust, a spray of old blood; minimal "energy"; the hit is felt via impact, shake, and pause, not glow |
| **Weather** | Volumetric and continuous: drifting fog banks, rain sheets, wind-driven debris, the dread strobe of storms; the world's primary VFX |
| **"Magic"** | There is no bright magic — only the Crown's corruption: slow, organic, muted-gold light bleeding/creeping, never bolts or sparkles |
| **Boss abilities** | Large, readable, in-character telegraphs (a bell's shock-ring, a stag's spectral antlers); one signature effect per boss, color-keyed to its identity |
| **Corruption** | Creeping muted-gold veins, motes, and heat-haze distortion; escalates with stage toward a bruised gold-violet wrongness |
| **Fire** | Warm, hungry, smoky; the rare source of warm light; embers and heat-haze; precious and dangerous |
| **Fog** | The signature effect — layered, drifting, light-scattering; depth and mystery; never a flat overlay |
| **Blood** | Dark, viscous, sparing; stains and pools that persist as story, rarely fresh sprays; never bright red |
| **Death effects** | Quiet and physical — a body falls and *stays*; for the corrupted, a slow exhale of muted-gold motes returning to the world; no flashy dissolves |

---

## 15. UI Visual Identity

The UI is a **diegetic artifact of this world**, not a modern overlay. Its language is
drawn from **ancient manuscripts, church records, old maps, and royal decrees** — ink and
gold-leaf on aged parchment and vellum, hand-ruled lines, wax seals, illuminated capitals.

**Principles**
- **No modern UI aesthetics:** no flat neon panels, no thin sans dashboards, no glossy
  cards. Everything reads as drawn, stamped, or scribed by hand.
- **Materials of the UI:** aged parchment/vellum, dark ink, tarnished muted-gold leaf,
  wax-red seals, weathered leather frames. Worn, stained, authoritative.
- **Restraint and emptiness:** sparse, calm, lots of negative space; the manuscript breathes.
  The HUD nearly vanishes in calm and surfaces only when needed.
- **Iconography:** woodcut/engraving and heraldic style — high-contrast linework, not
  filled modern glyphs. The broken **Hollow Crown** is the master motif.

| Screen | Identity |
|--------|----------|
| **HUD** | Minimal, diegetic: vigour/breath as worn painted bars or carved gauges; corruption as a slowly-illuminating crown sigil. Fades in calm. |
| **Menus** | A scribe's table — parchment leaves, illuminated headers, seal-stamped selections |
| **Inventory** | An itemized ledger / reliquary; items as inked engravings on parchment slots |
| **Dialogue** | Decree/letter framing; choices as inked lines; speaker as a heraldic seal |
| **Map** | A hand-drawn old map — incomplete, annotated, blank where unexplored ("here be nothing yet"); discovered, not given |
| **Quest log** | A traveler's journal / book of accounts in a scribe's hand |
| **Settlement mgmt** | A steward's ledger and estate plan — tallies, seals, a drawn survey of holdings |

**Input parity is visual too:** layouts and focus states designed for controller, mouse,
and keyboard equally (clear focus highlights as illuminated/seal states), with no
hover-only information.

---

## 16. Typography

Type carries the manuscript identity while staying legible on screens and at distance.

| Role | Influence | Use | Rules |
|------|-----------|-----|-------|
| **Display / decorative** | Blackletter / Lombardic capitals (illuminated) | Game title, region names, boss titles, chapter cards | Sparingly; never for body; treated with gold-leaf/ink texture |
| **Headings (primary)** | Humanist incised serif / Trajan-like Roman capitals | Menu headers, screen titles, UI section labels | High legibility, weathered-ink finish; the workhorse of "official" voice |
| **Body / secondary** | Clean old-style **serif** (Garamond/Jenson lineage) | All readable text: dialogue, descriptions, journal, tooltips | **Legibility first** — generous size/leading, high contrast on parchment, never decorative for long text |
| **Hand / annotation** | Period chancery/secretary cursive | Map annotations, marginalia, hand-written notes (flavor) | Used as *texture/flavor*, kept short; never load-bearing for critical info |

**Readability rules (non-negotiable):** body copy is a clean serif at comfortable size with
strong parchment-vs-ink contrast; decorative/blackletter and cursive are flavor only and
never used for information the player must reliably read; full localization support
(extended Latin and beyond) is required, so display faces have fallbacks and all text is
externally sourced. Beauty never costs the player a re-read.

---

## 17. Region Identity & Mood Board Package

Each region must be **recognizable from a single frame.** For each: a keyword line, then
visual / lighting / color / architectural / narrative / environmental themes, and a
reference mood board (concept key art establishing the target — *mood, not literal layout*).

> The boards below are generated reference art in the project's style. They define
> *atmosphere, palette, and silhouette language* for each region — not final layouts.

### The Weeping Moors
![The Weeping Moors — mood board](https://d8j0ntlcm91z4.cloudfront.net/user_3EivvHArDH20rZJATcln7fZ2Olf/hf_20260613_134405_ecfda6f3-19fe-499d-bf96-01634bd4a200.jpeg)
- **Keywords:** drowned, mournful, fog-blind, rotting, the first grief.
- **Visual:** endless flat wetland swallowed by fog; a rotting half-sunken village; an abandoned church with a leaning bell tower; flooded causeways; dead trees and tilted graves.
- **Lighting:** weak horizonless dusk, heavy ground fog, almost no shadow; the world dissolves at 30 m.
- **Color:** cold grey + desaturated navy + black water, moss-green decay, a single far muted-gold window.
- **Architecture:** poor timber village over older drowned stone; the church as the lone vertical.
- **Narrative:** the kingdom's edge where the dying began; grief made landscape.
- **Environmental:** standing black water, peat, reeds, causeways, the toll of a far bell.

### Blackwood
![Blackwood — mood board](https://d8j0ntlcm91z4.cloudfront.net/user_3EivvHArDH20rZJATcln7fZ2Olf/hf_20260613_134408_f12eb18b-3e37-488a-83b2-9e5cdaeaa1c4.jpeg)
- **Keywords:** living, shifting, predatory, ancient, watchful.
- **Visual:** impossibly tall black-barked trees; paths that seem to move; mist between trunks; great antlered shapes half-seen.
- **Lighting:** weak grey dapple choked by canopy; light fails fast with depth; the dark is alive.
- **Color:** dark forest green + charcoal, moss and pale fungus, a faint gold gleam of watching eyes.
- **Architecture:** almost none — only swallowed shrines and the bones of those who entered.
- **Narrative:** a forest older than the kingdom that does not want to be walked.
- **Environmental:** shifting trails, root tangles, fungus on the dead, hanging moss.

### Ashbourne
![Ashbourne — mood board](https://d8j0ntlcm91z4.cloudfront.net/user_3EivvHArDH20rZJATcln7fZ2Olf/hf_20260613_134411_622e533f-d7b1-4372-a0c1-dca3cb3101d7.jpeg)
- **Keywords:** smothered, grieving, masked, soft-falling, forgotten cause.
- **Visual:** a city under endless ash like grey snow; soot-blanketed roofs and statues; masked citizens; lantern haze.
- **Lighting:** flat, diffuse, choked; lanterns as soft muted-gold orbs in grey murk.
- **Color:** near-monochrome ash white + charcoal + faded ivory, one muted-gold lantern note.
- **Architecture:** grand townhouses and squares decaying under soot; a city pretending at normalcy.
- **Narrative:** a catastrophe no one remembers, mourned by people who've forgotten why.
- **Environmental:** drifting ash, soot dunes, muffled sound, ash-choked fountains.

### The Drowned Kingdom
![The Drowned Kingdom — mood board](https://d8j0ntlcm91z4.cloudfront.net/user_3EivvHArDH20rZJATcln7fZ2Olf/hf_20260613_134414_09960695-0217-4d8f-8e9f-f95b853aae4e.jpeg)
- **Keywords:** sunken, vast, lonely, cold, majestic ruin.
- **Visual:** flooded gothic cathedrals and castle towers rising from still grey sea; broken bridges; a colossal sunken statue.
- **Lighting:** cold flat sea-light through mist; green-blue gloom below the waterline.
- **Color:** desaturated navy + slate blue + weathered stone, burnt bronze fittings, faint gold.
- **Architecture:** a great drowned civilization — gothic spires and halls half-claimed by the sea.
- **Narrative:** glory swallowed whole; a kingdom that chose the water or was taken by it.
- **Environmental:** still water, kelp and barnacle on spires, tide-lines, drowned bells.

### The Silent Cathedral
![The Silent Cathedral — mood board](https://d8j0ntlcm91z4.cloudfront.net/user_3EivvHArDH20rZJATcln7fZ2Olf/hf_20260613_134416_b098a25b-989f-4235-9e68-771aef07e179.jpeg)
- **Keywords:** sacred, hushed, beautiful, dreadful, wrong-clean.
- **Visual:** a vast pale-stone holy city of immense cathedrals; empty plazas; seas of unlit candles; frozen banners.
- **Lighting:** soft holy shafts through high windows; deep soft shadow; dust in the light; unnervingly *still*.
- **Color:** faded ivory + ash white + cold stone, restrained muted-gold leaf; the cleanest region, as a warning.
- **Architecture:** the kingdom's grandest, most vertical ecclesiastical work, eerily intact.
- **Narrative:** silence became law; sound brings horror; faith turned to dread.
- **Environmental:** unlit candle fields, motionless banners, oppressive quiet, dust.

### The Hollow Capital
![The Hollow Capital — mood board](https://d8j0ntlcm91z4.cloudfront.net/user_3EivvHArDH20rZJATcln7fZ2Olf/hf_20260613_134420_cb064c37-2533-4409-a2b4-6260b281c78d.jpeg)
- **Keywords:** colossal, unraveling, ominous, the source, awe and dread.
- **Visual:** a colossal ruined capital around a black palace; fractured leaning towers; reality subtly wrong; muted-gold corruption bleeding from a central spire.
- **Lighting:** eclipse-dim, oppressive haze, the wrong gold glow as the dominant motivated light.
- **Color:** charcoal + cold grey + burnt bronze, dried-blood accents, ominous muted gold.
- **Architecture:** the deepest layered history — the ancient, the kingdom's peak, and corruption fused; the broken-crown motif everywhere.
- **Narrative:** the birthplace of the corruption and the seat of the final king.
- **Environmental:** unraveling space, falling stone, gold-veined corruption, monumental scale.

### Master Visual Identity Board
![The Hollow Crown — master visual identity](https://d8j0ntlcm91z4.cloudfront.net/user_3EivvHArDH20rZJATcln7fZ2Olf/hf_20260613_134423_0aab96db-174f-4e68-ac66-0c4c0a9c8969.jpeg)
The one image that should sell the whole game in a glance: the lone Crownless, small and
cold-lit, before an immense ruined cathedral in the fog, under a faint broken-crown glow.
All regions, characters, and assets are checked against this for tone.

---

## 18. Visual Consistency Rules

The checklist every asset and every AI generation must pass before approval:

1. **Reinforces the eight feelings** — and works against none of them.
2. **Obeys the three laws** — nothing recently built, modern, or clean (unless clean is the deliberate Silent-Cathedral horror).
3. **Within the palette** — 70/25/5 split honored; saturation only as deliberate wrongness; no forbidden colors.
4. **Lit, not flat** — motivated single-source light, fog for depth, cold-vs-warm contrast, readable silhouettes.
5. **Aged by default** — weathering, layering of eras, history visible in the materials.
6. **Silhouette reads first** — characters, enemies, bosses, and key props are identifiable as black shapes.
7. **Grounded** — believable proportion, weight, and physics; no fantasy/anime excess; VFX restrained.
8. **Tells a story** — nothing randomly placed; the asset implies cause and history.
9. **Corruption is the only "unnatural"** — and always reads as muted-gold organic wrongness.
10. **Region-true** — matches its region's mood board on palette skew, fog behavior, and signature read.

**For AI-generated assets specifically:** use the project style descriptor verbatim across
prompts for cohesion (the palette, "painterly gothic dark realism," fog, permanent
twilight, strong silhouettes); reject outputs that drift bright, modern, clean, saturated,
or anime; verify the 70/25/5 color split and the silhouette read on every output.

---

## 19. AAA Production Standards

1. **This bible is law and is enforced at review.** Every asset is checked against §18 before it enters the project; tone is a gate, not an opinion.
2. **One palette, one style, one world.** Master materials and a shared palette/LUT enforce cohesion; no asset ships outside the palette.
3. **Concept before production.** Key locations, characters, and bosses are concepted and tone-approved before full production; greybox + mood pass precedes detail.
4. **Mood boards are binding per region.** Region teams work to their board (§17); cross-region tone drift is a defect.
5. **Silhouette and readability pass** on every character/enemy/boss/weapon before detailing.
6. **Weathering is a first-class authored stage,** not an afterthought — driven by shared material parameters for consistency.
7. **Lighting is authored per scene to the §4 rules,** by lighting artists, motivated and composed — never left to default.
8. **Restraint is reviewed for** — over-decoration, visual noise, and "too bright/too clean" are rejected as readily as low quality.
9. **Reference, don't copy.** The reference films/games set *mood*; final work is original and world-true.
10. **The bible is living** — updated as the world deepens; every change is reviewed by the art director and propagated to the boards.

---

*Every location tells a story. Every boss is a fallen legend. Every choice leaves a scar.
If a frame is beautiful but not haunted, or haunted but not believable, it is not yet The
Hollow Crown.*
