# Aircraft outline overrides

The pushback planner draws an outline of the aircraft (fuselage, main wing
and horizontal stabilizer). BetterPushback normally gets this from the
loaded aircraft's .acf file.

Some aircraft don't work with that. The Zibo 737 for instance has no
fuselage body, it's built out of wing parts instead. For aircraft like
these, acf_outlines.txt has a pre-computed outline that is used instead of
the .acf.

Please don't add .acf files, or anything else from an aircraft, to this
repository. Those files belong to the aircraft authors. Only the outline
numbers go in acf_outlines.txt.

## How an override is picked

When an aircraft is loaded, BetterPushback looks in acf_outlines.txt for a
section that lists the aircraft's .acf file name (e.g. b738.acf, case
doesn't matter). If it finds one it uses it, otherwise it reads the
aircraft's own .acf like before.

## Coordinates

Everything is in meters, looking down on the aircraft:

```
            nose (negative y)
                 |
                 |
   ------------- + -------------> +x   (right wing)
                 |  (0,0) = CG
                 |
            tail (positive y)
```

x is the distance out from the centerline, y is the distance from the CG
(acf/_cgZ in the .acf). Negative y is towards the nose.

Only describe the right half of the aircraft. The left half is drawn by
mirroring it, so x should never be negative.

## File format

```
[b738.acf b738_4k.acf]
semispan 16.7406
length 39.4106
wingtip 16.7406 5.2317
pt 0.0000 -18.2118
pt 0.3883 -18.0824
...
pt null
...
```

```
[name.acf other.acf]  start of a section, lists all the .acf file names
                      it applies to (e.g. variants of the same aircraft)
semispan <m>          half the wingspan, used for the wingtip markers
length <m>            overall length
wingtip <x> <y>       quarter chord point at the tip of the widest wing,
                      y sets where the wingtip markers are fore/aft
pt <x> <y>            outline point, joined to the previous point
pt null               break in the outline, used between shapes
# ...                 comment
```

semispan, length, wingtip and at least one pt are required. If a section
is missing something or can't be parsed, an error is logged and the .acf is
used instead.

The points go in this order:

1) fuselage, right side, nose (x = 0) to tail
2) pt null
3) main wing, leading edge root to tip, then trailing edge tip to root
4) pt null
5) horizontal stabilizer, same as the main wing

## Generating an override from an .acf

The easiest way is to run BetterPushback's own outline code over the .acf
with the acf_outline_dump tool. It prints a section you can paste straight
into acf_outlines.txt. Use the copy of the aircraft you have installed, and
only commit the numbers it prints.

It builds on Linux, once libacfutils is built (see the main README):

```
$ cmake -S src -B build/lin64
$ cmake --build build/lin64 --target acf_outline_dump
$ dist/tools/acf_outline_dump "/path/to/X-Plane 12/Aircraft/.../b738.acf" b738_4k.acf
```

The section is named after the .acf you pass in. Any other names you add
after it go into the section header too.

You'll probably see a few of these, which is fine. It just means the
aircraft doesn't use that wing segment:

```
INFO: Cannot parse acf file: property _wing/15/_Croot not found, aircraft outline may not well drawn
```

If an aircraft needs an override, its .acf will usually give you an outline
that is only partly right (no fuselage on the Zibo 737 for example). It's
still worth generating it, since the parts that are right (usually the
wings) are already relative to the CG. Then fix the rest by hand as
described below.

## Working it out by hand

If the .acf doesn't give you anything useful, or you need to fix part of a
generated outline, you can work it out from the aircraft's published
dimensions: length, wingspan, fuselage width, wing root and tip chords and
sweep.

First you need to know where the CG is compared to the nose. If you
generated an outline from the .acf, the first point is the nose, e.g.
`pt 0.0000 -18.2118` means the nose is 18.21m in front of the CG.
Otherwise use acf/_cgZ from the .acf (in feet) and the nose position.

Anything measured from the nose then becomes:

```
y = distance from nose - distance from nose to CG
```

x is just the distance from the centerline. If the dimensions are in feet,
multiply by 0.3048.

For the fuselage, go down the right side from the nose (x = 0), out to half
the fuselage width, and back in at the tail. Around 10 to 15 points is
enough.

For the wings, X-Plane positions a wing by its quarter chord line (25% of
the chord back from the leading edge) and the sweep angle is measured along
that line. Work out the quarter chord point at the root and at the tip. The
tip one is the root one moved out by the wing's length and back by
length * tan(sweep). Then the four points are:

```
root leading edge    root x, root y - 0.25 * root chord
tip leading edge     tip x,  tip y  - 0.25 * tip chord
tip trailing edge    tip x,  tip y  + 0.75 * tip chord
root trailing edge   root x, root y + 0.75 * root chord
```

Do the same for the horizontal stabilizer with its own span, chords and
sweep.

Finally set semispan to half the wingspan, length to the overall length and
wingtip to the quarter chord point at the wing tip.

## Testing

Edit acf_outlines.txt in the installed plugin
(Resources/plugins/BetterPushback/objects/override/) and load the aircraft.
Log.txt should have a line like this:

```
INFO: acf outline override for b738.acf found in .../acf_outlines.txt : using it
```

If the section has a problem there will be an ERROR line saying what's
wrong. Then open the planner and check that the outline lines up with the
aircraft and the wingtip markers are on the wingtips.
